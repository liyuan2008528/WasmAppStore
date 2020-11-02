/**
* @file tee_time_api.h
*
* Copyright(C), 2008-2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.\n
*
* 描述：安全时间相关API\n
*/

/**
* @defgroup  TEE_EXT_TIMER_API  安全时间
* @ingroup TEE_API
*/
#ifndef __TEE_TIME_API_H
#define __TEE_TIME_API_H

#include "tee_internal_api.h"

#define TEE_TIMEOUT_INFINITE (0xFFFFFFFF)

/**
* @ingroup  TEE_EXT_TIMER_API
* TEE时间数据结构
*/
typedef struct {
	uint32_t seconds;
	uint32_t millis;
} TEE_Time;

/**
* @ingroup  TEE_EXT_TIMER_API
* TEE侧系统时间
*/
typedef struct {
	int32_t seconds;
	int32_t millis;
	int32_t min;
	int32_t hour;
	int32_t day;
	int32_t month;
	int32_t year;
} TEE_Date_Time;

/**
* @ingroup  TEE_EXT_TIMER_API
* TEE计时器属性
*/
typedef struct {
	uint32_t type;
	uint32_t timer_id;
	uint32_t timer_class;
	uint32_t reserved2;
} TEE_timer_property;

/**
* @ingroup  TEE_EXT_TIMER_API
* 计时器类型
*/
typedef enum {
	ANTI_ROOT_TIMER = 1,
} TEE_Anti_Root_Timer_Type;

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief 获取系统RTC时间
*
* @par 描述: 
* 获取系统RTC时间
*
* @attention 无
* @param time [OUT] 时间buffer
*
* @retval 无
*
* @par 依赖:
* @li tee_time_api.h：该接口声明所在的头文件
* @see 无
* @since TrustedCore V100R008C00
*/
void get_sys_rtc_time(TEE_Time *time);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief 获取TEE系统时间
*
* @par 描述:
* 获取TEE系统时间
*
* @attention 时间起点为TEE开始运行
* @param time [OUT] 当前TEE系统时间
*
* @retval 无
*
* @par 依赖:
* @li tee_time_api.h：该接口声明所在的头文件
* @see 无
* @since TrustedCore V100R008C00
*/
void TEE_GetSystemTime(TEE_Time *time);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief 当前线程等待time时长
*
* @par 描述:
* 如果超时等于TEE_TIMEOUT_INFINITE（0xFFFFFFFF），TEE_Wait
* 函数将等待指定的毫秒数或永远等待。
*
* @attention 无
* @param time [IN] 需要等待的时长
*
* @retval #TEE_SUCCESS      执行成功
* @retval #TEE_ERROR_CANCEL 等待被取消
*
* @par 依赖:
* @li tee_time_api.h：该接口声明所在的头文件
* @see 无
* @since TrustedCore V100R008C00
*/
TEE_Result TEE_Wait(uint32_t timeout);

/**
* @inroup  TEE_EXT_TIMER_API
* @brief 获取距离上次Set操作的时间间隔
*
* @par 描述:
* 在TEE_SetTAPersistentTime之后，该函数获取此段时间间隔
*
* @attention 关机或重启后不影响，保证之前有Set操作
* @param time [OUT] 时间间隔
*
* @retval #TEE_SUCCESS                执行成功
* @retval #TEE_ERROR_BAD_PARAMETERS   传入参数错误
* @retval #TEE_ERROR_TIME_NOT_SET RTC 时间未设定
* @retval #TEE_ERROR_TIME_NEEDS_RESET 时钟未重置
* @retval #TEE_ERROR_OVERFLOW         时钟发生溢出
* 
* @par 依赖:
* @li tee_time_api.h：该接口声明所在的头文件
* @see 无
* @since TrustedCore V100R008C00
*/
TEE_Result TEE_GetTAPersistentTime(TEE_Time *time);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief 设置基准时间
*
* @par 描述:
* 设置基准时间
*
* @attention 无
* @param time [IN] 写入的时间
*
* @retval #TEE_SUCCESS                执行成功
* @retval #TEE_ERROR_BAD_PARAMETERS   传入参数错误
* @retval #TEE_ERROR_TIME_NEEDS_RESET RTC时间未设定
*
* @par 依赖:
* @li tee_time_api.h：该接口声明所在的头文件
* @see 无
* @since TrustedCore V100R008C00
*/
TEE_Result TEE_SetTAPersistentTime(TEE_Time *time);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief 获取REE侧时间
*
* @par 描述:
* 获取REE侧时间
*
* @attention 无
* @param time [OUT] REE侧时间
*
* @retval 无
*
* @par 依赖:
* @li tee_time_api.h：该接口声明所在的头文件
* @see 无
* @since TrustedCore V100R008C00
*/
void TEE_GetREETime(TEE_Time *time);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief 获取REE侧时间字符串
*
* @par 描述:
* 获取REE侧时间字符串
*
* @attention 无
* @param time_str     [OUT] 时间字符串buffer
* @param time_str_len [IN]  时间字符串buffer长度
*
* @retval 无
*
* @par 依赖:
* @li tee_time_api.h：该接口声明所在的头文件
* @see 无
* @since TrustedCore V100R008C00
*/
void TEE_GetREETimeStr(char *time_str, uint32_t time_str_len);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief 创建一个安全时钟
*
* @par 描述:
* 创建一个安全时钟
*
* @attention 无
* @param time_seconds   [IN]  安全时间时长
* @param timer_property [IN]  安全时间类型type
*
* @retval #TEE_SUCCESS                         执行成功
* @retval #TEE_ERROR_BAD_PARAMETERS            入参错误
* @retval #TEE_ERROR_OUT_OF_MEMORY             内存不足
* @retval #TEE_ERROR_TIMER_CREATE_FAILED timer 创建失败
*
* @par 依赖:
* @li tee_time_api.h：该接口声明所在的头文件。
* @see 无
* @since TrustedCore V100R005C00
*/
TEE_Result  TEE_EXT_CreateTimer(uint32_t time_seconds,   TEE_timer_property *timer_property);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief 销毁一个安全时钟
*
* @par 描述:
* 销毁一个安全时钟
*
* @attention 无
* @param timer_property   [IN] 安全时间类型type
*
* @retval #TEE_SUCCESS                    执行成功
* @retval #TEE_ERROR_TIMER_NOT_FOUND:     timer不存在
* @retval #TEE_ERROR_TIMER_DESTORY_FAILED timer销毁失败
*
* @par 依赖:
* @li tee_time_api.h：该接口声明所在的头文件。
* @see 无
* @since TrustedCore V100R005C00
*/
TEE_Result  TEE_EXT_DestoryTimer(TEE_timer_property *timer_property);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief 获取timer定时时间
*
* @par 描述:
* 获取timer定时时间
*
* @attention 无
* @param timer_property [IN]  安全时间类型type
* @param time_seconds   [OUT] 安全时间
*
* @retval #TEE_SUCCESS                执行成功
* @retval #TEE_ERROR_TIMER_NOT_FOUND  timer不存在
*
* @par 依赖:
* @li tee_time_api.h：该接口声明所在的头文件。
* @see 无
* @since TrustedCore V100R005C00
*/
TEE_Result  TEE_EXT_GetTimerExpire(TEE_timer_property *timer_property, uint32_t *time_seconds);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief 获取timer定时剩余时间
*
* @par 描述:
* 获取timer定时剩余时间
*
* @attention 无
* @param timer_property   [IN]  安全时间类型type
* @param time_seconds     [OUT] 安全时间
*
* @retval #TEE_SUCCESS                 执行成功
* @retval #TEE_ERROR_TIMER_NOT_FOUND   timer不存在
*
* @par 依赖:
* @li tee_time_api.h：该接口声明所在的头文件。
* @see 无
* @since TrustedCore V100R005C00
*/
TEE_Result  TEE_EXT_GetTimerRemain(TEE_timer_property *timer_property, uint32_t *time_seconds);

TEE_Result  TEE_ANTI_ROOT_CreateTimer(uint32_t time_seconds);

TEE_Result  TEE_ANTI_ROOT_DestoryTimer();
#endif
