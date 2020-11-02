/**
* @file tee_log.h
*
* Copyright(C), 2008-2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
*
* 描述：安全服务调试log函数定义
*/

/**
* @defgroup grp_log_api 安全服务调试
* @ingroup TEE_API
*/

#ifndef __TEE_LOG_H
#define __TEE_LOG_H

#include "tee_internal_api.h"

#define DEBUG_TAG	    "[debug]"
#define INFO_TAG	    "[info]"
#define WARNING_TAG	    "[warning]"
#define ERROR_TAG	    "[error]"

#define LEVEL_DEBUG   2
#define LEVEL_WARNING   1
#define LEVEL_ERROR    0

#define TAG_VERB	    "[verb]"
#define TAG_DEBUG	    "[debug]"
#define TAG_INFO	    "[info]"
#define TAG_WARN	    "[warn]"
#define TAG_ERROR	    "[error]"

typedef enum {
	LOG_LEVEL_ERROR = 0,
	LOG_LEVEL_WARN = 1,
	LOG_LEVEL_INFO = 2,
	LOG_LEVEL_DEBUG = 3,
	LOG_LEVEL_VERBO = 4,
	LOG_LEVEL_ON = 5,
} LOG_LEVEL;

void uart_cprintf(const char *fmt, ...);
void hex_dump(const char *des, const char *start, unsigned length);
void uart_printf_func(const char *fmt, ...);

void tee_print(LOG_LEVEL log_level, const char *fmt, ...);
int printf(const char *__restrict, ...);
extern const char *debug_prefix;

#ifdef LOG_ON
#define tlogv(fmt, args...) tee_print(LOG_LEVEL_VERBO, "%s %d:%s:" fmt "", TAG_VERB, __LINE__, __func__, ## args)
#define tlogd(fmt, args...) tee_print(LOG_LEVEL_DEBUG, "%s %d:%s:" fmt "", TAG_DEBUG, __LINE__, __func__, ## args)
#define tlogi(fmt, args...) tee_print(LOG_LEVEL_INFO, "%s %d:%s:" fmt "", TAG_INFO, __LINE__, __func__, ## args)
#define tlogw(fmt, args...) tee_print(LOG_LEVEL_WARN, "%s %d:%s:" fmt "", TAG_WARN, __LINE__, __func__, ## args)
#else
#define tlogv(fmt, args...) do {} while(0)
#define tlogd(fmt, args...) do {} while(0)
#define tlogi(fmt, args...) do {} while(0)
#define tlogw(fmt, args...) do {} while(0)
#endif /* ENG_VERSION */

#ifndef TLOGE_NO_TIMESTAMP
#define tloge(fmt, args...) tee_print(LOG_LEVEL_ERROR, "%s %d:" fmt " ", TAG_ERROR,__LINE__, ## args)
#else
#define tloge(fmt, args...) printf("[%s] %s %d:" fmt " ", debug_prefix, TAG_ERROR,__LINE__, ## args)
#endif

void ta_print(LOG_LEVEL log_level,const char *fmt, ...);

#ifdef LOG_ON
#define ta_logv(fmt, args...) ta_print(LOG_LEVEL_VERBO, "%s %d: " fmt "\n", TAG_VERB, __LINE__, ## args)
#define ta_logd(fmt, args...) ta_print(LOG_LEVEL_DEBUG, "%s %d: " fmt "\n", TAG_DEBUG, __LINE__, ## args)
#define ta_logi(fmt, args...) ta_print(LOG_LEVEL_INFO, "%s %d: " fmt "\n", TAG_INFO, __LINE__, ## args)
#define ta_logw(fmt, args...) ta_print(LOG_LEVEL_WARN, "%s %d: " fmt "\n", TAG_WARN, __LINE__, ## args)
#else
#define ta_logv(fmt, args...) do {} while(0)
#define ta_logd(fmt, args...) do {} while(0)
#define ta_logi(fmt, args...) do {} while(0)
#define ta_logw(fmt, args...) do {} while(0)
#endif
#define ta_loge(fmt, args...) ta_print(LOG_LEVEL_ERROR, "%s %d: " fmt "\n", TAG_ERROR, __LINE__, ## args)


/* in debug version users can dynamically modify the loglevel ,in release version, users have to modify the level by compile */
#ifndef DEBUG_VERSION

//#define TA_DEBUG
#ifdef TA_DEBUG
#define ta_debug(fmt, args...) uart_printf_func("%s %s: " fmt "", DEBUG_TAG,__FUNCTION__, ## args)
#else
#define ta_debug(fmt, args...)
#endif

#else

#define ta_debug(fmt, args...) \
    do {\
        uint32_t level;\
        level = get_value();\
        if(level>=LEVEL_DEBUG){\
           uart_printf_func("%s %s: " fmt "", DEBUG_TAG,__FUNCTION__, ## args); \
        }\
    } while (0)

#define ta_warning(fmt, args...)\
    do {\
        uint32_t level;\
        level = get_value();\
        if(level>=LEVEL_WARNING){\
            uart_printf_func("%s %s: " fmt "", DEBUG_TAG,__FUNCTION__, ## args); \
        }\
    } while (0)

#endif

#define ta_info(fmt, args...) uart_printf_func("%s %s: " fmt "", INFO_TAG,__FUNCTION__, ## args)
#define ta_error(fmt, args...) uart_printf_func("%s %s: " fmt " ", ERROR_TAG,__FUNCTION__, ## args)
#define TA_LOG
#ifdef TA_LOG
/**
 * @ingroup grp_log_api
 * 日志的级别Trace
 */
#define TRACE "[Trace]"
/**
 * @ingroup grp_log_api
 * 日志的级别Warning
 */
#define WARNING "[Warning]"
/**
 * @ingroup grp_log_api
 * 日志的级别Error
 */
#define ERROR "[Error]"

/**
 * @ingroup grp_log_api
 * 打印Trace日志的接口
 */
#define SLogTrace(fmt, args...) SLog("%s %s: " fmt "\n", TRACE, __FUNCTION__, ## args)
/**
 * @ingroup grp_log_api
 * 打印Warning日志的接口
 */
#define SLogWarning(fmt, args...) SLog("%s %s: " fmt "\n", WARNING, __FUNCTION__, ## args)
/**
 * @ingroup grp_log_api
 * 打印Error日志的接口
 */
#define SLogError(fmt, args...) SLog("%s %s: " fmt "\n", ERROR, __FUNCTION__, ## args)

//TODO: SHOULD call Panic to deal, here just return
/**
 * @ingroup grp_log_api
 * 断言接口
 */
#define SAssert(exp) \
    do {    \
        if (!(exp)) {   \
            SLog("Assertion [ %s ] Failed: File %s, Line %d, Function %s\n",   \
            #exp, "__FILE__", __LINE__, __FUNCTION__);    \
            return 0xFFFF0001;    \
        }   \
    } while(0);
#else
#define SLogTrace(fmt, args...) ((void)0)
#define SLogWarning(fmt, args...) ((void)0)
#define SLogError(fmt, args...) ((void)0)
#define SAssert(exp)  ((void)0)
#endif

/**
* @ingroup  grp_log_api
* @brief 将日志输出至文件
*
* @par 描述:
* 日志输出至文件
*
* @attention 无
*
* @param fmt [IN] 日志的格式化内容
*
* @retval 无
*
* @par 依赖:
* @li tee_log.h：内部数据类型定义
* @see 无
* @since
**/
void SLog(const char *fmt, ...);

uint32_t get_value();

#endif
