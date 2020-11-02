#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <tee_client_type.h>
#include <bitset>
#include "inc/tee_client_api.h"


//static const TEEC_UUID Hello_World_uuid = { 0x98263abc, 0x4138, 0x4b59, { 0x9f, 0xe9, 0x3c, 0x26, 0x3c, 0x6e, 0x4e, 0x8b}};

//tam message
#define CMD_TAM_OTRP      0x00c30000

//client message
#define CMD_CLIENT_TMF     0x00c20000
static const TEEC_UUID Hello_World_uuid = {0x2c0af0e7, 0xeda6, 0x4839,
                                           {0xbf, 0xee, 0xc9, 0x16, 0x7d, 0xd5, 0x8a, 0x1b}};
enum {
    CMD_GET_TA_VERSION = 1,
    CMD_GET_CLIENT_ALLPROPERTY,
    CMD_GET_TA_ALLPROPERTY,
    CMD_GET_TEE_ALLPROPERTY,
    CMD_GPTEE_SD_INSTALL,
    CMD_SEC_DATA_STORE,
    CMD_SEC_KEY_STORE,
    CMD_CREATE_SEC_DATAOBJ,
    CMD_READ_SEC_DATAOBJ,
    CMD_WRITE_SEC_DATAOBJ,
    CMD_DEL_SEC_DATAOBJ,
};
uint32_t timeCount=0;



extern "C"
JNIEXPORT jstring JNICALL
Java_com_huawei_ide_Tee_stringFromJNI(JNIEnv *env,
                                      jobject instance,
                                      jstring param,
                                      jbyteArray wasm,
                                      jbyteArray bytesCommond){

    // TODO
    //   std::string hello = "Hello from C++";
//    return env->NewStringUTF(hello.c_str());
    const char *ptr = NULL;
    char test_buf[256] = {0};
    unsigned int buf_len = 256;
    char test_buf1[256] = {0};
    unsigned int buf_len1 = 256;
    char test_buf3[256] = {0};
    unsigned int buf_len3 = 256;
    char test_buf2[2048] = {0};
    unsigned int buf_len2 = 2048;

    if (param)
        ptr = (env)->GetStringUTFChars(param, false);


    TEEC_Context context;
    TEEC_Session session;
    TEEC_Result result;
    TEEC_Operation operation;
    uint32_t cmd = 1;
    uint32_t origin;



    result = TEEC_InitializeContext(NULL, &context);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    memset(&operation, 0, sizeof(TEEC_Operation));
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_NONE,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_MEMREF_TEMP_INPUT);
    context.ta_path = (uint8_t *) ptr;
    //memcpy(test_buf2, bytesCommond, ta_len);
    memcpy(test_buf2,env->GetByteArrayElements(wasm, 0),env->GetArrayLength(wasm));
    operation.params[0].tmpref.buffer = test_buf2;
    operation.params[0].tmpref.size = env->GetArrayLength(wasm);
    //TEEC_Error("teec open ta_path is %s\n", context.ta_path);
    //TEEC_Error("teec open ta_path is %p\n", operation.params[3].tmpref.buffer);
    result = TEEC_OpenSession(&context, &session, &Hello_World_uuid,
                              TEEC_LOGIN_IDENTIFY, NULL, &operation, NULL);




    if (result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed, ret is 0x%x\n", result);
        goto cleanup_2;
    }
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_MEMREF_TEMP_OUTPUT,
            TEEC_NONE,
            TEEC_MEMREF_TEMP_OUTPUT
    );
    operation.params[3].tmpref.buffer = test_buf;
    operation.params[3].tmpref.size = buf_len;

    //cmd=CMD_GPTEE_SD_INSTALL;
//   cmd = CMD_GET_TA_ALLPROPERTY;
    //cmd=CMD_SEC_DATA_STORE;
    //cmd=CMD_SEC_KEY_STORE;
    //cmd = CMD_CREATE_SEC_DATAOBJ;
   // cmd = CMD_READ_SEC_DATAOBJ;
//    cmd = CMD_WRITE_SEC_DATAOBJ;
    // cmd = CMD_DEL_SEC_DATAOBJ;
    cmd = CMD_TAM_OTRP;

    memcpy(test_buf2,env->GetByteArrayElements(bytesCommond, 0),env->GetArrayLength(bytesCommond));
    operation.params[0].tmpref.buffer = test_buf2;
    operation.params[0].tmpref.size = env->GetArrayLength(bytesCommond);
    operation.params[1].tmpref.buffer = test_buf1;
    operation.params[1].tmpref.size = buf_len1;

    result = TEEC_InvokeCommand(&session, cmd, &operation, &origin);
//    result3 = TEEC_InvokeCommand(&session3, cmd, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    } else {
        TEEC_Error("Succeed to load and excute dynamic TA!\n");
        TEEC_CloseSession(&session);
        TEEC_FinalizeContext(&context);
        uint32_t count;
        for(count=0; count < operation.params[1].tmpref.size; count++)
        {
            TEEC_Error("count= %d,v=%02X",count,*((unsigned char *)(operation.params[1].tmpref.buffer)+count));
            snprintf(test_buf3+count*2, 0x100, "%02X", *((unsigned char *)(operation.params[1].tmpref.buffer)+count));
        }
        test_buf3[operation.params[1].tmpref.size*2]=0x00;
        TEEC_Error("test_buf1=%s!\n",test_buf3);
        return env->NewStringUTF(test_buf3);
    }
    TEEC_CloseSession(&session);
    cleanup_2:
    TEEC_FinalizeContext(&context);
    cleanup_1:
    return env->NewStringUTF("TestFailed");
}

