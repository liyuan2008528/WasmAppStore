/**
* @file tee_time_api.h
*
* Copyright(C), 2008-2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.\n
*
* ��������ȫʱ�����API\n
*/

/**
* @defgroup  TEE_EXT_TIMER_API  ��ȫʱ��
* @ingroup TEE_API
*/
#ifndef __TEE_TIME_API_H
#define __TEE_TIME_API_H

#include "tee_internal_api.h"

#define TEE_TIMEOUT_INFINITE (0xFFFFFFFF)

/**
* @ingroup  TEE_EXT_TIMER_API
* TEEʱ�����ݽṹ
*/
typedef struct {
	uint32_t seconds;
	uint32_t millis;
} TEE_Time;

/**
* @ingroup  TEE_EXT_TIMER_API
* TEE��ϵͳʱ��
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
* TEE��ʱ������
*/
typedef struct {
	uint32_t type;
	uint32_t timer_id;
	uint32_t timer_class;
	uint32_t reserved2;
} TEE_timer_property;

/**
* @ingroup  TEE_EXT_TIMER_API
* ��ʱ������
*/
typedef enum {
	ANTI_ROOT_TIMER = 1,
} TEE_Anti_Root_Timer_Type;

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief ��ȡϵͳRTCʱ��
*
* @par ����: 
* ��ȡϵͳRTCʱ��
*
* @attention ��
* @param time [OUT] ʱ��buffer
*
* @retval ��
*
* @par ����:
* @li tee_time_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since TrustedCore V100R008C00
*/
void get_sys_rtc_time(TEE_Time *time);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief ��ȡTEEϵͳʱ��
*
* @par ����:
* ��ȡTEEϵͳʱ��
*
* @attention ʱ�����ΪTEE��ʼ����
* @param time [OUT] ��ǰTEEϵͳʱ��
*
* @retval ��
*
* @par ����:
* @li tee_time_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since TrustedCore V100R008C00
*/
void TEE_GetSystemTime(TEE_Time *time);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief ��ǰ�̵߳ȴ�timeʱ��
*
* @par ����:
* �����ʱ����TEE_TIMEOUT_INFINITE��0xFFFFFFFF����TEE_Wait
* �������ȴ�ָ���ĺ���������Զ�ȴ���
*
* @attention ��
* @param time [IN] ��Ҫ�ȴ���ʱ��
*
* @retval #TEE_SUCCESS      ִ�гɹ�
* @retval #TEE_ERROR_CANCEL �ȴ���ȡ��
*
* @par ����:
* @li tee_time_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since TrustedCore V100R008C00
*/
TEE_Result TEE_Wait(uint32_t timeout);

/**
* @inroup  TEE_EXT_TIMER_API
* @brief ��ȡ�����ϴ�Set������ʱ����
*
* @par ����:
* ��TEE_SetTAPersistentTime֮�󣬸ú�����ȡ�˶�ʱ����
*
* @attention �ػ���������Ӱ�죬��֤֮ǰ��Set����
* @param time [OUT] ʱ����
*
* @retval #TEE_SUCCESS                ִ�гɹ�
* @retval #TEE_ERROR_BAD_PARAMETERS   �����������
* @retval #TEE_ERROR_TIME_NOT_SET RTC ʱ��δ�趨
* @retval #TEE_ERROR_TIME_NEEDS_RESET ʱ��δ����
* @retval #TEE_ERROR_OVERFLOW         ʱ�ӷ������
* 
* @par ����:
* @li tee_time_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since TrustedCore V100R008C00
*/
TEE_Result TEE_GetTAPersistentTime(TEE_Time *time);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief ���û�׼ʱ��
*
* @par ����:
* ���û�׼ʱ��
*
* @attention ��
* @param time [IN] д���ʱ��
*
* @retval #TEE_SUCCESS                ִ�гɹ�
* @retval #TEE_ERROR_BAD_PARAMETERS   �����������
* @retval #TEE_ERROR_TIME_NEEDS_RESET RTCʱ��δ�趨
*
* @par ����:
* @li tee_time_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since TrustedCore V100R008C00
*/
TEE_Result TEE_SetTAPersistentTime(TEE_Time *time);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief ��ȡREE��ʱ��
*
* @par ����:
* ��ȡREE��ʱ��
*
* @attention ��
* @param time [OUT] REE��ʱ��
*
* @retval ��
*
* @par ����:
* @li tee_time_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since TrustedCore V100R008C00
*/
void TEE_GetREETime(TEE_Time *time);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief ��ȡREE��ʱ���ַ���
*
* @par ����:
* ��ȡREE��ʱ���ַ���
*
* @attention ��
* @param time_str     [OUT] ʱ���ַ���buffer
* @param time_str_len [IN]  ʱ���ַ���buffer����
*
* @retval ��
*
* @par ����:
* @li tee_time_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since TrustedCore V100R008C00
*/
void TEE_GetREETimeStr(char *time_str, uint32_t time_str_len);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief ����һ����ȫʱ��
*
* @par ����:
* ����һ����ȫʱ��
*
* @attention ��
* @param time_seconds   [IN]  ��ȫʱ��ʱ��
* @param timer_property [IN]  ��ȫʱ������type
*
* @retval #TEE_SUCCESS                         ִ�гɹ�
* @retval #TEE_ERROR_BAD_PARAMETERS            ��δ���
* @retval #TEE_ERROR_OUT_OF_MEMORY             �ڴ治��
* @retval #TEE_ERROR_TIMER_CREATE_FAILED timer ����ʧ��
*
* @par ����:
* @li tee_time_api.h���ýӿ��������ڵ�ͷ�ļ���
* @see ��
* @since TrustedCore V100R005C00
*/
TEE_Result  TEE_EXT_CreateTimer(uint32_t time_seconds,   TEE_timer_property *timer_property);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief ����һ����ȫʱ��
*
* @par ����:
* ����һ����ȫʱ��
*
* @attention ��
* @param timer_property   [IN] ��ȫʱ������type
*
* @retval #TEE_SUCCESS                    ִ�гɹ�
* @retval #TEE_ERROR_TIMER_NOT_FOUND:     timer������
* @retval #TEE_ERROR_TIMER_DESTORY_FAILED timer����ʧ��
*
* @par ����:
* @li tee_time_api.h���ýӿ��������ڵ�ͷ�ļ���
* @see ��
* @since TrustedCore V100R005C00
*/
TEE_Result  TEE_EXT_DestoryTimer(TEE_timer_property *timer_property);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief ��ȡtimer��ʱʱ��
*
* @par ����:
* ��ȡtimer��ʱʱ��
*
* @attention ��
* @param timer_property [IN]  ��ȫʱ������type
* @param time_seconds   [OUT] ��ȫʱ��
*
* @retval #TEE_SUCCESS                ִ�гɹ�
* @retval #TEE_ERROR_TIMER_NOT_FOUND  timer������
*
* @par ����:
* @li tee_time_api.h���ýӿ��������ڵ�ͷ�ļ���
* @see ��
* @since TrustedCore V100R005C00
*/
TEE_Result  TEE_EXT_GetTimerExpire(TEE_timer_property *timer_property, uint32_t *time_seconds);

/**
* @ingroup  TEE_EXT_TIMER_API
* @brief ��ȡtimer��ʱʣ��ʱ��
*
* @par ����:
* ��ȡtimer��ʱʣ��ʱ��
*
* @attention ��
* @param timer_property   [IN]  ��ȫʱ������type
* @param time_seconds     [OUT] ��ȫʱ��
*
* @retval #TEE_SUCCESS                 ִ�гɹ�
* @retval #TEE_ERROR_TIMER_NOT_FOUND   timer������
*
* @par ����:
* @li tee_time_api.h���ýӿ��������ڵ�ͷ�ļ���
* @see ��
* @since TrustedCore V100R005C00
*/
TEE_Result  TEE_EXT_GetTimerRemain(TEE_timer_property *timer_property, uint32_t *time_seconds);

TEE_Result  TEE_ANTI_ROOT_CreateTimer(uint32_t time_seconds);

TEE_Result  TEE_ANTI_ROOT_DestoryTimer();
#endif
