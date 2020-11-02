/*
* Copyright (c) Huawei Technologies Co., Ltd. 2019-2029. All rights reserved.
* Description: The name of the huawei libteec so of android Q has changed,
* from libteec.so to libteec.huawei.so.
* In order to make the APK adapt to libteec of android O/P/Q, etc
* apk should dlopen libteec according to the interfaces in this file.
* Create: 2019.4.30
*/

#include <dlfcn.h>
#include <pthread.h>

#include "inc/tee_client_api.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "libteec_adaptor"

#if defined(__LP64__)
/* for 64bit APK */
#define ANDROID_O_P_VENDOR_LIBTEEC_PATH  "/vendor/lib64/libteec.so"
#define ANDROID_O_P_SYSTEM_LIBTEEC_PATH  "/system/lib64/libteec.so"
#define ANDROID_Q_LIBTEEC_PATH    "/system/lib64/libteec.huawei.so"
#else
/* for 32bit APK */
#define ANDROID_O_P_VENDOR_LIBTEEC_PATH  "/vendor/lib/libteec.so"
#define ANDROID_O_P_SYSTEM_LIBTEEC_PATH  "/system/lib/libteec.so"
#define ANDROID_Q_LIBTEEC_PATH    "/system/lib/libteec.huawei.so"
#endif

/* these Function pointers are consistent with those defined in "tee_client_api.h"
 * if you want to call the new interface in "tee_client_api.h",
 * you should add a new definition here
 */
typedef TEEC_Result (*initializeContext_f)(const char *name, TEEC_Context *context);
typedef void (*finalizeContext_f)(TEEC_Context *context);
typedef TEEC_Result (*openSession_f)(TEEC_Context *context, TEEC_Session *session,
    const TEEC_UUID *destination, uint32_t connectionMethod, const void *connectionData,
    TEEC_Operation *operation, uint32_t *returnOrigin);
typedef void (*closeSession_f)(TEEC_Session *session);
typedef TEEC_Result (*invokeCommand_f)(TEEC_Session *session, uint32_t commandID,
    TEEC_Operation *operation, uint32_t *returnOrigin);
typedef TEEC_Result (*registerSharedMemory_f)(TEEC_Context *context,
    TEEC_SharedMemory *sharedMem);
typedef TEEC_Result (*allocateSharedMemory_f)(TEEC_Context *context,
    TEEC_SharedMemory *sharedMem);
typedef void (*releaseSharedMemory_f)(TEEC_SharedMemory *sharedMem);
typedef void (*requestCancellation_f)(TEEC_Operation *operation);
typedef uint32_t (*getTEEVersion_f)();
typedef TEEC_Result (*sendSecfile_f)(const char *path, TEEC_Session *session);

/* As above, if you want to call the new interface in "tee_client_api.h",
 * you should add a new member to TeecApiTable
 */
typedef struct {
    initializeContext_f     initializeContextFn;
    finalizeContext_f       finalizeContextFn;
    openSession_f           openSessionFn;
    closeSession_f          closeSessionFn;
    invokeCommand_f         invokeCommandFn;
    registerSharedMemory_f  registerSharedMemoryFn;
    allocateSharedMemory_f  allocateSharedMemoryFn;
    releaseSharedMemory_f   releaseSharedMemoryFn;
    requestCancellation_f   requestCancellationFn;
    getTEEVersion_f         getTEEVersionFn;
    sendSecfile_f           sendSecfileFn;
} TeecApiTable;

static TeecApiTable g_teecApiTable;
static void *g_libTeecHandle = NULL;
static pthread_mutex_t g_libTeecHandleLock = PTHREAD_MUTEX_INITIALIZER;

/* APK should dlopen so lib in the order shown by this function,
 * make sure the APK is compatible with all versions.
 */
static TEEC_Result GetTeecApiSymbol()
{
    (void)pthread_mutex_lock(&g_libTeecHandleLock);

    if (g_libTeecHandle != NULL) {
        (void)pthread_mutex_unlock(&g_libTeecHandleLock);
        return TEEC_SUCCESS;
    }

    /* for Andorid Q */
    g_libTeecHandle = dlopen(ANDROID_Q_LIBTEEC_PATH, RTLD_LAZY);
    if (g_libTeecHandle == NULL) {
        /* for Andorid O&P, system APK */
        g_libTeecHandle = dlopen(ANDROID_O_P_SYSTEM_LIBTEEC_PATH, RTLD_LAZY);
        if (g_libTeecHandle == NULL) {
            /* for Andorid O&P, third party APK */
            g_libTeecHandle = dlopen(ANDROID_O_P_VENDOR_LIBTEEC_PATH, RTLD_LAZY);
            if (g_libTeecHandle == NULL) {
                TEEC_Error("dlopen libteec failed\n");
                (void)pthread_mutex_unlock(&g_libTeecHandleLock);
                return TEEC_ERROR_GENERIC;
            }
        }
    }

    g_teecApiTable.initializeContextFn =
        (initializeContext_f)(dlsym(g_libTeecHandle, "TEEC_InitializeContext"));
    if (g_teecApiTable.initializeContextFn == NULL) {
        TEEC_Error("get symbol TEEC_InitializeContext failed\n");
        goto ERROR;
    }

    g_teecApiTable.finalizeContextFn =
        (finalizeContext_f)(dlsym(g_libTeecHandle, "TEEC_FinalizeContext"));
    if (g_teecApiTable.finalizeContextFn == NULL) {
        TEEC_Error("get symbol TEEC_FinalizeContext failed\n");
        goto ERROR;
    }

    g_teecApiTable.openSessionFn =
        (openSession_f)(dlsym(g_libTeecHandle, "TEEC_OpenSession"));
    if (g_teecApiTable.openSessionFn == NULL) {
        TEEC_Error("get symbol TEEC_OpenSession failed\n");
        goto ERROR;
    }

    g_teecApiTable.closeSessionFn =
        (closeSession_f)(dlsym(g_libTeecHandle, "TEEC_CloseSession"));
    if (g_teecApiTable.closeSessionFn == NULL) {
        TEEC_Error("get symbol TEEC_CloseSession failed\n");
        goto ERROR;
    }

    g_teecApiTable.invokeCommandFn =
        (invokeCommand_f)(dlsym(g_libTeecHandle, "TEEC_InvokeCommand"));
    if (g_teecApiTable.invokeCommandFn == NULL) {
        TEEC_Error("get symbol TEEC_InvokeCommand failed\n");
        goto ERROR;
    }

    g_teecApiTable.registerSharedMemoryFn =
        (registerSharedMemory_f)(dlsym(g_libTeecHandle, "TEEC_RegisterSharedMemory"));
    if (g_teecApiTable.registerSharedMemoryFn == NULL) {
        TEEC_Error("get symbol TEEC_RegisterSharedMemory failed\n");
        goto ERROR;
    }

    g_teecApiTable.allocateSharedMemoryFn =
        (allocateSharedMemory_f)(dlsym(g_libTeecHandle, "TEEC_AllocateSharedMemory"));
    if (g_teecApiTable.allocateSharedMemoryFn == NULL) {
        TEEC_Error("get symbol TEEC_AllocateSharedMemory failed\n");
        goto ERROR;
    }

    g_teecApiTable.releaseSharedMemoryFn =
        (releaseSharedMemory_f)(dlsym(g_libTeecHandle, "TEEC_ReleaseSharedMemory"));
    if (g_teecApiTable.releaseSharedMemoryFn == NULL) {
        TEEC_Error("get symbol TEEC_ReleaseSharedMemory failed\n");
        goto ERROR;
    }

    g_teecApiTable.requestCancellationFn =
        (requestCancellation_f)(dlsym(g_libTeecHandle, "TEEC_RequestCancellation"));
    if (g_teecApiTable.requestCancellationFn == NULL) {
        TEEC_Error("get symbol TEEC_RequestCancellation failed\n");
        goto ERROR;
    }

    /* the following interfaces are not defined by GP,
     * they are not included in old libteec so version.
     * we may get null ptr from the old so version, it's ok, do not return error.
     */
    g_teecApiTable.getTEEVersionFn =
        (getTEEVersion_f)(dlsym(g_libTeecHandle, "TEEC_GetTEEVersion"));
    g_teecApiTable.sendSecfileFn =
        (sendSecfile_f)(dlsym(g_libTeecHandle, "TEEC_SendSecfile"));

    (void)pthread_mutex_unlock(&g_libTeecHandleLock);
    return TEEC_SUCCESS;

ERROR:
    dlclose(g_libTeecHandle);
    g_libTeecHandle = NULL;
    (void)memset(&g_teecApiTable, 0, sizeof(g_teecApiTable));
    (void)pthread_mutex_unlock(&g_libTeecHandleLock);
    return TEEC_ERROR_GENERIC;
}

/* The following are Interfaces for APK,
 * in these interfaces, you should make sure the function pointer in g_teecApiTable is not NULL
 */
TEEC_Result TEEC_InitializeContext(const char *name, TEEC_Context *context)
{
    TEEC_Result ret = GetTeecApiSymbol();
    if (ret != TEEC_SUCCESS) {
        TEEC_Error("get teec api symbol failed!\n");
        return TEEC_ERROR_GENERIC;
    }

    return g_teecApiTable.initializeContextFn(name, context);
}

void TEEC_FinalizeContext(TEEC_Context *context)
{
    if (g_teecApiTable.finalizeContextFn == NULL) {
        TEEC_Error("finalizeContextFn is null!\n");
        return;
    }

    g_teecApiTable.finalizeContextFn(context);
}

TEEC_Result TEEC_OpenSession(TEEC_Context *context, TEEC_Session *session,
    const TEEC_UUID *destination, uint32_t connectionMethod,
    const void *connectionData, TEEC_Operation *operation,
    uint32_t *returnOrigin)
{
    if (g_teecApiTable.openSessionFn == NULL) {
        TEEC_Error("openSessionFn is null!\n");
        return TEEC_ERROR_GENERIC;
    }

    return g_teecApiTable.openSessionFn(context, session, destination,
        connectionMethod, connectionData, operation, returnOrigin);
}

void TEEC_CloseSession(TEEC_Session *session)
{
    if (g_teecApiTable.closeSessionFn == NULL) {
        TEEC_Error("closeSessionFn is null!\n");
        return;
    }

    g_teecApiTable.closeSessionFn(session);
}

TEEC_Result TEEC_InvokeCommand(TEEC_Session *session, uint32_t commandID,
    TEEC_Operation *operation, uint32_t *returnOrigin)
{
    if (g_teecApiTable.invokeCommandFn == NULL) {
        TEEC_Error("invokeCommandFn is null!\n");
        return TEEC_ERROR_GENERIC;
    }

    return g_teecApiTable.invokeCommandFn(session, commandID, operation, returnOrigin);
}

TEEC_Result TEEC_RegisterSharedMemory(TEEC_Context *context,
    TEEC_SharedMemory *sharedMem)
{
    if (g_teecApiTable.registerSharedMemoryFn == NULL) {
        TEEC_Error("registerSharedMemoryFn is null!\n");
        return TEEC_ERROR_GENERIC;
    }

    return g_teecApiTable.registerSharedMemoryFn(context, sharedMem);
}

TEEC_Result TEEC_AllocateSharedMemory(TEEC_Context *context,
    TEEC_SharedMemory *sharedMem)
{
    if (g_teecApiTable.allocateSharedMemoryFn == NULL) {
        TEEC_Error("allocateSharedMemoryFn is null!\n");
        return TEEC_ERROR_GENERIC;
    }

    return g_teecApiTable.allocateSharedMemoryFn(context, sharedMem);
}

void TEEC_ReleaseSharedMemory(TEEC_SharedMemory *sharedMem)
{
    if (g_teecApiTable.releaseSharedMemoryFn == NULL) {
        TEEC_Error("releaseSharedMemoryFn is null!\n");
        return;
    }

    g_teecApiTable.releaseSharedMemoryFn(sharedMem);
}

void TEEC_RequestCancellation(TEEC_Operation *operation)
{
    if (g_teecApiTable.requestCancellationFn == NULL) {
        TEEC_Error("requestCancellationFn is null!\n");
        return;
    }

    g_teecApiTable.requestCancellationFn(operation);
}

uint32_t TEEC_GetTEEVersion()
{
    TEEC_Result ret = GetTeecApiSymbol();
    if (ret != TEEC_SUCCESS) {
        TEEC_Error("get teec api symbol failed!\n");
        return 0;
    }

    if (g_teecApiTable.getTEEVersionFn == NULL) {
        TEEC_Error("getTEEVersionFn is null!\n");
        return 0;
    }

    return g_teecApiTable.getTEEVersionFn();
}

TEEC_Result TEEC_SendSecfile(const char *path, TEEC_Session *session)
{
    if (g_teecApiTable.sendSecfileFn == NULL) {
        TEEC_Error("sendSecfileFn is null!\n");
        return TEEC_ERROR_GENERIC;
    }

    return g_teecApiTable.sendSecfileFn(path, session);
}
