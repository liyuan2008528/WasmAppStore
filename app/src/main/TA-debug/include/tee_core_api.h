/**
 * @file tee_core_api.h
 *
 * Copyright(C), 2008-2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 * 
 * ��������ȫ����TA��TA����API  \n
 */

/**
 * @defgroup TEE_TA2TA_FUNC  TA��TA����
 * @ingroup TEE_API
 */


#ifndef __TEE_CORE_API_H
#define __TEE_CORE_API_H

#include "tee_internal_api.h"
#ifndef _TEE_TASessionHandle
#define _TEE_TASessionHandle
typedef uint32_t TEE_TASessionHandle;
#endif

#define SESSION_FROM_CA             0
#define SESSION_FROM_TA             1
#define SESSION_FROM_UNKNOWN       (0xFF)
 /**
 * @ingroup  TEE_TA2TA_FUNC
 * @brief �Ự��������ӡ������Ϣ
 *
 * @par ����:
 * ��TA�����޷�����������ȥ�Ĺ���ʱ�����������ú����ᵼ��TA��ֹ��������Դ�����ջ�
 * ����ִ��ʱ��CA���յ�һ��TEE_ERROR_TARGET_DEAD������
 * ϵͳ������ʾ��ش�����Ϣ����ӡ����ջ
 *
 * @attention ��
 *
 * @param destination [OUT] ��TA����Ĵ����룬�����ڵ���ջ�д�ӡ����
 *
 * @retval ��
 *
 * @par ����:
 * @li tee_core_api.h���ýӿ���������ͷ�ļ�
 * @see ��
 * @since V100R002C00
 */
void TEE_Panic(TEE_Result panicCode);
 /**
 * @ingroup  TEE_TA2TA_FUNC
 * @brief �򿪻Ự
 *
 * @par ����:
 * Ϊ�ͻ���Ӧ�û�ȫ���� ��UUIDΪdestination�İ�ȫ������һ�����ӣ����ݵ����ݰ�����params��
 * �򿪻Ự�ɹ����������session�ǶԸ����ӵ�һ��������
 * ����򿪻Ựʧ�ܣ��������returnOriginΪ������Դ��
 *
 * @attention ��
 *
 * @param destination                [IN]     ��ȫ�����UUID��һ����ȫ����ӵ��Ψһ��UUID
 * @param cancellationRequestTimeout [IN]     δʹ�ò���������ʹ��
 * @param paramTypes                 [IN]     ��Ҫ���ݸ�Ŀ��TA�Ĳ���������
 * @param params[4]                  [IN]     ��Ҫ���ݸ�Ŀ��TA�Ĳ�����
 * @param session                    [OUT]    ����򿪵�TA��Ӧsession
 * @param returnOrigin               [IN/OUT] ������Դ��ȡֵ��ΧΪ#TEE_ReturnCodeOrigin
 *
 * @retval #TEE_SUCCESS              �򿪻Ự�ɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS ��������ȷ������destinationΪ�ջ�sessionΪ��
 * @retval #TEE_ERROR_OUT_OF_MEMORY  ϵͳ������Դ����
 * @retval #TEE_ERROR_ITEM_NOT_FOUND ���������δ�ҵ�
 * @retval ��������ֵ�ο� #TEEC_ReturnCode
 *
 * @par ����:
 * @li tee_core_api.h���ýӿ���������ͷ�ļ�
 * @see TEE_CloseTASession
 * @since V100R002C00
 */
TEE_Result TEE_OpenTASession(TEE_UUID *destination, uint32_t cancellationRequestTimeout,
			     uint32_t paramTypes, TEE_Param params[4],
			     TEE_TASessionHandle *session, uint32_t *returnOrigin);

/**
 * @ingroup  TEE_TA2TA_FUNC 
 * @brief �رջỰ
 *
 * @par ����:
 * �ر�ָ��session�ỰTA���Ͽ�Դ��ȫ������Ŀ�갲ȫ���������
 *
 * @attention ��
 *
 * @param session [IN/OUT] ��Ҫ�ر�TA��Ӧsession
 *
 * @retval ��
 *
 * @par ����:
 * @li tee_core_api.h���ýӿ���������ͷ�ļ�
 * @see TEE_OpenTASession
 * @since V100R002C00
 */
void TEE_CloseTASession(TEE_TASessionHandle session);

/**
 * @ingroup  TEE_TA2TA_FUNC
 * @brief ��������
 *
 * @par ����:
 * ��ָ���ĻỰsession��ɿͻ���Ӧ����ȫ����������commandID�����͵�����Ϊparams��
 * �����������ʧ�ܣ��������returnOriginΪ������Դ
 *
 * @attention ��
 *
 * @param session                    [IN/OUT] ָ���Ѵ򿪳ɹ��ĻỰ
 * @param cancellationRequestTimeout [IN]     δʹ�ò���������ʹ��
 * @param commandID                  [IN]     ��ȫ����֧�ֵ�����ID���ɰ�ȫ������
 * @param paramTypes                 [IN]     ��Ҫ���ݸ�Ŀ��TA�Ĳ���������
 * @param params[4]                  [IN]     ��Ҫ���ݸ�Ŀ��TA�Ĳ�����
 * @param returnOrigin               [IN/OUT] ������Դ��ȡֵ��ΧΪ#TEE_ReturnCodeOrigin
 *
 * @retval #TEE_SUCCESS              ��������ɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS ��������ȷ������destinationΪ�ջ�sessionΪ��
 * @retval #TEE_ERROR_OUT_OF_MEMORY  ϵͳ������Դ����
 * @retval #TEE_ERROR_ITEM_NOT_FOUND ���������δ�ҵ�
 * @retval ��������ֵ�ο� #TEEC_ReturnCode
 *
 * @par ����:
 * @li tee_client_api.h���ýӿ���������ͷ�ļ�
 * @see ��
 * @since V100R002C00
 */
TEE_Result TEE_InvokeTACommand(TEE_TASessionHandle session, uint32_t cancellationRequestTimeout,
			       uint32_t commandID, uint32_t paramTypes,
			       TEE_Param params[4], uint32_t *returnOrigin);

/**
 * @ingroup  TEE_TA2TA_FUNC 
 * @brief ȡ����ǵ�ǰ�����ȡ��״̬
 *
 * @par ����:
 * ��
 *
 * @attention ��
 *
 * @param ��
 *
 * @retval #true  ���ô˺���ǰ�Ѿ������ȡ��
 * @retval #false �������
 *
 * @par ����:
 * @li tee_core_api.h���ýӿ���������ͷ�ļ�
 * @see ��
 * @since V100R002C00
 */
bool TEE_UnmaskCancellation(void);

/**
 * @ingroup  TEE_TA2TA_FUNC 
 * @brief ��ǵ�ǰ�����ȡ��״̬ 
 *
 * @par ����:
 * ��
 * 
 * @attention ��
 *
 * @param ��
 *
 * @retval #true  ���ô˺���ǰ�Ѿ������ȡ��
 * @retval #false �������
 *
 * @par ����:
 * @li tee_core_api.h���ýӿ���������ͷ�ļ�
 * @see 
 * @since V100R002C00
 */
bool TEE_MaskCancellation(void);

/**
 * @ingroup  TEE_TA2TA_FUNC 
 * @brief ��ȡsession����
 *
 * @par ����:��ȡ��ǰsession������
 *
 * @attention ��
 *
 * @param ��
 *
 * @retval ��ǰ��������
 *
 * @par ����:
 * @li tee_core_api.h���ýӿ���������ͷ�ļ�
 * @see 
 * @since V100R002C00
 */
uint32_t TEE_GetSessionType(void);
#endif
