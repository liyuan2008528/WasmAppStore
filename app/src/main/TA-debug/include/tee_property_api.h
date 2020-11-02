/**
* @file tee_property_api.h
*
* Copyright(C), 2008-2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.\n
*
* ��������ȫ���簲ȫ�������API\n
*/

/**
* @defgroup TEE_PROPERTY_API  TEE��ȫ����
* @ingroup TEE_API
*/

#ifndef __TEE_PROPERTY_API_H
#define __TEE_PROPERTY_API_H

#include "tee_internal_api.h"

/**
* @ingroup TEE_PROPERTY_API
*/
typedef enum {
	TEE_PROPSET_UNKNOW = 0,
	TEE_PROPSET_TEE_IMPLEMENTATION = 0xFFFFFFFD,
	TEE_PROPSET_CURRENT_CLIENT = 0xFFFFFFFE,
	TEE_PROPSET_CURRENT_TA = 0xFFFFFFFF,
} Pseudo_PropSetHandle;

/**
 * @ingroup TEE_PROPERTY_API
 */
typedef uint32_t TEE_PropSetHandle;

/**
* @ingroup TEE_PROPERTY_API
* @brief ����Property����String��ʽ����
*
* @par ����:
* TEE_GetPropertyAsString���������Լ���ִ�в����Լ����������Բ�����ֵת��Ϊ�ɴ�
* ӡ�ַ����� �����ҳɹ�ʱ��ʵ�ֱ��뽫����ת��Ϊ�ɴ�ӡ���ַ���������������Ƶ�
* valueBuffer��valueBufferLen�����Ļ������С�
*
* @attention ��
*
* @param propsetOrEnumerator [IN]  ����ö�پ��
* @param name                [IN]  ��ѯ����
* @param valueBuffer         [OUT] ��������buffer
* @param valueBufferLen      [OUT] �������ݳ���
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_ITEM_NOT_FOUND �Ҳ��������ԣ��������Ʋ�����Ч��UTF-8����
* @retval #TEE_ERROR_BAD_FORMAT     ����ֵ�޷�ת��Ϊ��ʶ
*
* @par ����:
* @li tee_property_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_GetPropertyAsString(TEE_PropSetHandle propsetOrEnumerator,
				   char *name, char *valueBuffer, size_t *valueBufferLen);

/**
* @ingroup TEE_PROPERTY_API
* @brief ����Property����bool��ʽ����
*
* @par ����:
* TEE_GetPropertyAsBool�����������Լ��еĵ������ԣ�������ֵת��Ϊ����ֵ�� ���
* ���Բ��ܱ���Ϊ����ֵ����˺������뷵��TEE_ERROR_BAD_FORMAT��
*
* @attention ��
*
* @param propsetOrEnumerator [IN]  ����ö�پ��
* @param name                [IN]  ��ѯ����
* @param value               [OUT] �������ݿռ�
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_ITEM_NOT_FOUND �Ҳ��������ԣ��������Ʋ�����Ч��UTF-8����
* @retval #TEE_ERROR_BAD_FORMAT     ����ֵ�޷�ת��Ϊ��ʶ
*
* @par ����:
* @li tee_property_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_GetPropertyAsBool(TEE_PropSetHandle propsetOrEnumerator,
				 char *name, bool *value);

/**
* @ingroup TEE_PROPERTY_API
* @brief ����Property����32λ������ʽ����
*
* @par ����:
* TEE_GetPropertyAsU32�����������Լ��еĵ������ԣ�������ֵת��Ϊ32λ�޷��������� 
* ������Բ��ܱ���Ϊ32λ�޷�����������˺������뷵��TEE_ERROR_BAD_FORMAT��
*
* @attention ��
*
* @param propsetOrEnumerator [IN]  ����ö�پ��
* @param name                [IN]  ��ѯ����
* @param value               [OUT] �������ݿռ�
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_ITEM_NOT_FOUND �Ҳ��������ԣ��������Ʋ�����Ч��UTF-8����
* @retval #TEE_ERROR_BAD_FORMAT     ����ֵ�޷�ת��Ϊ��ʶ
*
* @par ����:
* @li tee_property_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_GetPropertyAsU32(TEE_PropSetHandle propsetOrEnumerator,
				char *name, uint32_t *value);

/**
* @ingroup TEE_PROPERTY_API
* @brief ����Property���Զ�������ʽ����
*
* @par ����:
* ����TEE_GetPropertyAsBinaryBlock�����������Բ�����ֵת��Ϊ�����ƿ顣 ���
* ���Բ��ܱ���Ϊ�����ƿ飬��˺������뷵��TEE_ERROR_BAD_FORMAT��
*
* @attention ��
*
* @param propsetOrEnumerator  [IN]  ����ö�پ��
* @param name                 [IN]  ��ѯ����
* @param valueBuffer          [OUT] ��������buffer
* @param valueBufferLen       [OUT] �������ݳ���
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_ITEM_NOT_FOUND �Ҳ��������ԣ��������Ʋ�����Ч��UTF-8����
* @retval #TEE_ERROR_BAD_FORMAT     ����ֵ�޷�ת��Ϊ��ʶ
* @retval #TEE_ERROR_SHORT_BUFFER   ���buffer��С
*
* @par ����:
* @li tee_property_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_GetPropertyAsBinaryBlock(TEE_PropSetHandle propsetOrEnumerator,
					char *name, void *valueBuffer, size_t *valueBufferLen);

/**
* @ingroup TEE_PROPERTY_API
* @brief ����Property����UUID��ʽ����
*
* @par ����:
* ����TEE_GetPropertyAsUUID�����������Բ�����ֵת��ΪUUID�� ������Բ��ܱ���ΪUUID��
* ��˺������뷵��TEE_ERROR_BAD_FORMAT��
*
* @attention ��
*
* @param propsetOrEnumerator  [IN]  ����ö�پ��
* @param name                 [IN]  ��ѯ����
* @param value                [OUT] �������ݿռ�
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_ITEM_NOT_FOUND �Ҳ��������ԣ��������Ʋ�����Ч��UTF-8����
* @retval #TEE_ERROR_BAD_FORMAT     ����ֵ�޷�ת��Ϊ��ʶ
*
* @par ����:
* @li tee_property_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_GetPropertyAsUUID(TEE_PropSetHandle propsetOrEnumerator,
				 char *name, TEE_UUID *value);

/**
* @ingroup TEE_PROPERTY_API
* @brief ����Property����TEE_Identity��ʽ����
*
* @par ����:
* ����TEE_GetPropertyAsIdentity�����������Բ�����ֵת��ΪTEE_Identity��
*
* @attention ��
*
* @param propsetOrEnumerator  [IN]  ����ö�پ��
* @param name                 [IN]  ��ѯ����
* @param value                [OUT] ��������buffer
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_ITEM_NOT_FOUND �Ҳ��������ԣ��������Ʋ�����Ч��UTF-8����
* @retval #TEE_ERROR_BAD_FORMAT     ����ֵ�޷�ת��Ϊ��ʶ
*
* @par ����:
* @li tee_property_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_GetPropertyAsIdentity(TEE_PropSetHandle propsetOrEnumerator,
				     char *name, TEE_Identity *value);

/**
* @ingroup TEE_PROPERTY_API
* @brief ����Property Enumerator
*
* @par ����:
* ����TEE_AllocatePropertyEnumerator��������ö�������� һ������������ö�����ľ�
* �����Ϳ���ʹ������ʹ�ú���TEE_StartPropertyEnumeratorö�����Լ��е����ԡ�
*
* @attention ��
*
* @param enumerator [OUT] ö�پ��
*
* @retval #TEE_SUCCESS             ִ�гɹ�
* @retval #TEE_ERROR_OUT_OF_MEMORY ��Դ����
*
* @par ����:
* @li tee_property_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_AllocatePropertyEnumerator(TEE_PropSetHandle *enumerator);

/**
* @ingroup TEE_PROPERTY_API
* @brief �ͷ�Property Enumerator
*
* @par ����:
* ����TEE_FreePropertyEnumerator�ͷ�����ö��������
*
* @attention ��
*
* @param enumerator [IN] ���
*
* @par ����:
* @li tee_property_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
void TEE_FreePropertyEnumerator(TEE_PropSetHandle enumerator);

/**
* @ingroup TEE_PROPERTY_API
* @brief ��ʼPropertyö��
*
* @par ����:
* ����TEE_StartPropertyEnumerator��ʼö��ö�����е����ԡ� ��ö�������ӵ����Լ���
* @li ����ʹ��TEE_GetPropertyAsXXX����֮һ�������ԣ���ö���������Ϊ���Լ�����NULL��Ϊ���ƴ��ݡ�
* @li ����TEE_GetPropertyName�����ڼ���ö�����е�ǰ���Ե����ơ�
* @li ����TEE_GetNextProperty�����ڽ�ö���ƽ������Լ��е���һ�����ԡ�
*
* @attention ��
*
* @param enumerator [IN] ö�پ��
* @param propSet    [IN] ���Լ�
*
* @retval ��
*
* @par ����: ��
* @li tee_property_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
void TEE_StartPropertyEnumerator(TEE_PropSetHandle enumerator, TEE_PropSetHandle propSet);

/**
* @ingroup TEE_PROPERTY_API
* @brief ����Property Enumerator
*
* @par ����:
* ����TEE_ResetPropertyEnumerator��ִ�к�������Propertyö������Ϊ��ʼ״̬�� 
* �����ǰ����ö�٣����������
*
* @attention ��
*
* @param enumerator [IN] ���
*
* @retval ��
*
* @par ����:
* @li tee_property_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
void TEE_ResetPropertyEnumerator(TEE_PropSetHandle enumerator);

/**
* @ingroup TEE_PROPERTY_API
* @brief ����Property����
*
* @par ����:
* ����TEE_GetPropertyName��ȡö�����е�ǰ���Ե����ơ�
*
* @attention �������Ʊ����ǲ�����U + 0000������Unicode�ַ�������ЧUTF-8���롣
*
* @param enumerator    [IN]  ���
* @param nameBuffer    [OUT] ����buffer
* @param nameBufferLen [OUT] ���ش�С
*
* @retval #TEE_SUCCESS               ִ�гɹ�
* @retval #TEE_ERROR_ITEM_NOT_FOUND  ö��δ��ʼ���������һ��
* @retval #TEE_ERROR_SHORT_BUFFER    buffer��С
*
* @par ����:
* @li tee_property_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_GetPropertyName(TEE_PropSetHandle enumerator, void *nameBuffer, size_t *nameBufferLen);

/**
* @ingroup TEE_PROPERTY_API
* @brief ����һ��ö��
*
* @par ����:
* ����TEE_GetNextProperty��ö�ٽ��е���һ�����ԡ�
*
* @attention ��
*
* @param enumerator [IN] ���
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_ITEM_NOT_FOUND ö��δ��ʼ���������һ��
*
* @par ����:
* @li tee_property_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_GetNextProperty(TEE_PropSetHandle enumerator);

#endif
