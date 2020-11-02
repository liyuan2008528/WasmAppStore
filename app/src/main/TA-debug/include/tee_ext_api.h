/**
 * @file tee_ext_api.h
 *
 * Copyright(C), 2008-2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * �����������GP��׼�İ�ȫ����ӿ�\n
 */

/**
 * @defgroup TEE_TA_CALLER_INDENTIFY  ��ȫ��TA��ȨCA�ӿ�
 * @defgroup TEE_EXT_API  TEE��EXT�ӿ�
 * @ingroup TEE_API
 */ 
#ifndef __TEE_EXT_API_H
#define __TEE_EXT_API_H
#include "tee_internal_api.h"

#define TEE_INFO_RESERVED (0xFFFFFFFF)
#define TEE_RETURN_AGENT_BUFFER  0x99
#define TEE_INVALID_AGENT        0x66
#define TEE_AGENT_LOCK           0x33
#define TEE_GET_REEINFO_SUCCESS 0
#define TEE_GET_REEINFO_FAILED 1

/**
 * @ingroup TEE_TA_CALLER_INDENTIFY
 *
 * REE����Ϣ�ṹ��
*/
struct __ree_info {
	uint32_t userid;
	uint32_t appid;
	uint32_t reserve;
};

typedef struct __ree_info ree_info;

/**
 * @ingroup  TEE_EXT_API
 * @brief ��ȡREE����Ϣ
 *
 * @par ����:
 * ��global�������󣬻�ȡREE����Ϣ������userid�Լ�appid
 *
 * @attention ��
 *
 * @param ree_info_data     [OUT]       �������
 * @param length            [OUT]       ������ݳ���
 *
 * @retval #TEE_SUCCESS                 ��ȡ�ɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_OUT_OF_MEMORY     �����ڴ�ʧ��
 *
 * @par ����:
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see ��
 * @since V100R005C00
*/
TEE_Result TEE_EXT_GetREEInfo(ree_info *ree_info_data,  uint32_t *length);

#define TEE_EXT_GET_REE_USERID ({ \
    ree_info ree_info_data = {0}; \
    uint32_t length = sizeof(ree_info); \
    uint32_t userid; \
    if (TEE_SUCCESS == TEE_EXT_GetREEInfo(&ree_info_data, &length)) \
        userid = ree_info_data.userid; \
    else \
        userid = 0; \
    userid;})

#define RESERVED_BUF_SIZE   (32)

/**
 * @ingroup TEE_TA_CALLER_INDENTIFY
 *
 * ��������Ϣ�ṹ��
*/
typedef struct __caller_info {
	uint32_t session_type;
	union {
		TEE_UUID caller_uuid;
		uint8_t ca_info[RESERVED_BUF_SIZE]; //reserved
	} caller_identity;
	uint8_t reserved[RESERVED_BUF_SIZE]; //reserved
} caller_info;
#define OTHER_DIE_ID_SIZE	(5*4)
#define MTK_DIE_ID_SIZE (8*4)

/**
 * @ingroup  TEE_EXT_API
 * @brief ��ȡ�豸ΨһID
 *
 * @par ����:
 * ��ȡ�豸ΨһID��Ϣ
 *
 * @attention ��
 *
 * @param DevUniqueID       [OUT]       �������
 * @param length            [OUT]       ������ݳ���
 *
 * @retval #TEE_SUCCESS                 ��ȡ�ɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_OUT_OF_MEMORY     �����ڴ�ʧ��
 *
 * @par ����:
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see ��
 * @since V100R005C00
*/
TEE_Result TEE_EXT_GetDeviceUniqueId(uint8_t *DevUniqueID,  uint32_t *length);

/**
 * @ingroup  TEE_EXT_API
 * @brief ��ȡAgent��Ϣ
 *
 * @par ����:
 * ����agent_id��ȡsession_context��Ϣ������������Ϣ
 *
 * @attention ��
 *
 * @param agent_id     [IN]        ��������
 * @param buffer       [OUT]       �������
 * @param length       [OUT]       ������ݳ���
 *
 * @retval #TEE_SUCCESS                 ��ȡ�ɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_GENERIC     ����ʧ��
 *
 * @par ����:
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see ��
 * @since V100R005C00
*/
TEE_Result TEE_EXT_GetAgentBuffer(uint32_t agent_id, void **buffer, uint32_t *length);

/**
 * @ingroup  TEE_EXT_API
 * @brief ��ȡ�Ự��������Ϣ
 *
 * @par ����:
 * ��ȡ���Լ���TA�ĳ����session����
 * �����TA2TA����ͬʱ��ȡ�Ự�����ߵ�UUID
 *
 * @attention ��
 *
 * @param caller_info_data    [OUT]       �������
 * @param length              [OUT]       ������ݳ���
 *
 * @retval #TEE_SUCCESS                 �ӽ��ܳɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_SECURITY          ��ȫ����ִ��ʧ��
 *
 * @par ����:
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see ��
 * @since V100R005C00
*/
TEE_Result TEE_EXT_GetCallerInfo(caller_info *caller_info_data, uint32_t length);

/**
 * @ingroup  crypto
 * @brief AES�ӽ��ܼ���ģʽ
 *
 * @par ����:
 * AES���ɼӽ��ܣ�Ŀǰ֧��AES_CBC_NOPAD,AES_ECB_PKCS5������ͨ��rootkey������Կ
 *
 * @attention 
 * Ŀǰֻ֧��ECB��CBC
 *
 * @param DB        [IN]        �Ƿ��ô����key��rootkey������Կ
 * @param IV        [IN]        ��ʼ������ָ��
 * @param mode      [IN]        0:����;1:����
 * @param algothem  [IN]        AES�㷨 #TEE_CRYPTO_ALGORITHM_ID
 * @param key       [IN]        ��Կָ��
 * @param key_len   [IN]        ָ�볤��
 * @param cyp_src   [IN]        ��������
 * @param dst       [OUT]       �������
 * @param srclen    [IN]        �������ݳ���
 * @param dstlen    [OUT]       ������ݳ���
 *
 * @retval #TEE_SUCCESS                 �ӽ��ܳɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_OUT_OF_MEMORY     �����ڴ�ʧ��
 *
 * @par ����:
 * @li crypto �ӽ���ģ��
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see TEE_CipherInit | TEE_CipherUpdate | TEE_CipherDoFinal
 * @since V100R005C00
*/
TEE_Result TEE_EXT_AES_CRYPTO(bool DB, const uint8_t *IV, bool mode, uint32_t algothem, const uint8_t *key, uint32_t key_len,
			      const uint8_t *cyp_src, uint8_t *dst, uint32_t srclen, uint32_t *dstlen);

/**
 * @ingroup  crypto
 * @brief ����ժҪ
 *
 * @par ����:
 * ����ժҪ
 *
 * @attention ��
 *
 * @param algorithm     [IN]            ժҪ�㷨����SHA1,SHA256
 * @param DataIn_ptr    [IN]            ��������
 * @param DataSize      [IN]            �������ݳ���
 * @param hash_result   [OUT]           ժҪ��� SHA1 20bytes;SHA256 32bytes
 *
 * @retval #TEE_SUCCESS                 ժҪ�ɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_GENERIC           ժҪʧ��
 *
 * @par ����:
 * @li crypto �ӽ���ģ��
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @since V100R005C00
*/
TEE_Result TEE_EXT_HASH(TEE_CRYPTO_ALGORITHM_ID algorithm, const uint8_t *DataIn_ptr, uint32_t DataSize, uint8_t *hash_result);

/**
 * @ingroup  crypto
 * @brief ����RSA��Կ��
 *
 * @par ����:
 * RSA��Կ�����ɣ����Ϊ���ܺ���Կ�����ݽṹ
 *
 * @attention 
 * �����Կ�����ݽṹֻ�����ڱ�ģ�������Կ
 *
 * @param pubExp        [IN]        ��Կ��exponent ����0x10001
 * @param key_size      [IN]        ��Կ���� һ��Ϊ2048bit
 * @param key_blob      [OUT]       ���ܺ����Կ�����ݽṹ
 * @param key_blob_size [OUT]       key_blob����
 *
 * @retval #TEE_SUCCESS                 �ӽ��ܳɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_OUT_OF_MEMORY     �����ڴ�ʧ��
 *
 * @par ����:
 * @li crypto �ӽ���ģ��
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see ��
 * @since V100R005C00
*/
TEE_Result TEE_EXT_generate_keypair(uint32_t pubExp, uint32_t key_size, uint8_t *key_blob, uint32_t *key_blob_size);

/**
 * @ingroup  crypto
 * @brief ��ȡ��Կ
 *
 * @par ����:
 * RSA��Կ��ȡ
 *
 * @attention ��
 *
 * @param key_blob      [IN]        ��Կ�����ݽṹ
 * @param exopnent      [OUT]       ��Կ��exponent
 * @param modulus       [OUT]       ��Կ��modulus
 * @param exponentSize  [OUT]       exponent����
 * @param modulusSize   [OUT]       modulus����
 *
 * @retval #TEE_SUCCESS                 ��ȡ��Կ�ɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_GENERIC           ��ȡ��Կʧ��
 *
 * @par ����:
 * @li crypto �ӽ���ģ��
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see ��
 * @since V100R005C00
*/
TEE_Result TEE_EXT_get_keypair_public(uint8_t *key_blob, uint8_t *exopnent, uint8_t *modulus,
				      uint32_t *exponentSize, uint32_t *modulusSize);

/**
 * @ingroup  crypto
 * @brief ������ǩ��
 *
 * @par ����:
 * ������ǩ�����㷨�����ƣ�Ŀǰ֧��pkcs1v15��pkcs1v21�Լ�nopad
 *
 * @attention ��
 *
 * @param algorithm     [IN]        RSA�㷨
 * @param key_blob      [IN]        ��Կ�����ݽṹ
 * @param datain        [IN]        ��Ҫǩ��������
 * @param inSize        [IN]        ��Ҫǩ�����ݳ���
 * @param dataout       [OUT]       ǩ���������
 * @param outSize       [OUT]       ǩ��������ݳ���
 *
 * @retval #TEE_SUCCESS                 ��ȡ��Կ�ɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_GENERIC           ��ȡ��Կʧ��
 * @retval #TEE_ERROR_OUT_OF_MEMORY     �����ڴ�ʧ��
 * @retval #TEE_ERROR_NOT_SUPPORTED     �㷨��֧��
 *
 * @par ����:
 * @li crypto �ӽ���ģ��
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see ��
 * @since V100R005C00
*/
TEE_Result TEE_EXT_sign_data(TEE_CRYPTO_ALGORITHM_ID algorithm, uint8_t *key_blob, uint8_t *datain,
			     uint32_t inSize, uint8_t *dataout, uint32_t *outSize);

/**
 * @ingroup  crypto
 * @brief ������ǩ��
 *
 * @par ����:
 * ������ǩ�����㷨�����ƣ�Ŀǰ֧��pkcs1v15��pkcs1v21�Լ�nopad
 *
 * @attention ��
 *
 * @param algorithm     [IN]        RSA�㷨
 * @param key_blob      [IN]        ��Կ�����ݽṹ
 * @param srcData       [IN]        ��Ҫ���ܵ�����
 * @param srcLen        [IN]        ��Ҫ�������ݳ���
 * @param destData      [OUT]       ���ܺ������
 * @param destLen       [OUT]       ���ܺ�����ݳ���
 *
 * @retval #TEE_SUCCESS                 ��ȡ��Կ�ɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_GENERIC           ��ȡ��Կʧ��
 * @retval #TEE_ERROR_OUT_OF_MEMORY     �����ڴ�ʧ��
 * @retval #TEE_ERROR_NOT_SUPPORTED     �㷨��֧��
 *
 * @par ����:
 * @li crypto �ӽ���ģ��
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see ��
 * @since V100R005C00
*/
TEE_Result TEE_EXT_RSA_decrypt(TEE_CRYPTO_ALGORITHM_ID algorithm, uint8_t *key_blob,
			       uint8_t *srcData, uint32_t srcLen, uint8_t *destData, uint32_t *destLen);

/**
 * @ingroup  TEE_EXT_API
 * @brief ��ȡ�豸�Ƿ�root
 *
 * @par ����:
 * ��ȡ�豸root��Ϣ�����豸�Ѿ���root������1��û�б�root����0
 *
 * @attention ��
 *
 * @param ��
 *
 * @retval #true    �豸�Ѿ�root
 * @retval #false   �豸û��root
 *
 * @par ����:
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see ��
 * @since V100R005C00
*/
bool TEE_EXT_IsDeviceRooted(void);

/**
 * @ingroup  TEE_EXT_API
 * @brief ����豸��root״̬
 *
 * @par ����:
 * ���豸��root״̬�����λ��ʾ����״̬
 *
 * @attention ��
 *
 * @param ��
 *
 * @retval #state    �豸root״̬
 *
 * @par ����:
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see ��
 * @since V100R005C00
 */
uint32_t TEE_EXT_DeviceRootStatus(void);

/**
 * @ingroup TEE_EXT_API
 * @brief ��ȡvsim�����ڴ� 
 * 
 * @par ����:
 * ��ȡvsim�����ڴ� �ɹ�����success��ʧ�ܷ��ش�����
 *
 * @attention ��
 *
 * @param addr      [OUT]       �����ڴ��ַ
 * @param size      [OUT]        �����ڴ��С
 *
 * @retval #TEE_SUCCESS                 �ɹ���ȡ�����ڴ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    ��������
 * @retval #TEE_ERROR_GENERIC           �ڴ�ӳ��ʧ��
 *
 * @par ����:
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see ��
 * @since V100R005C00
*/
TEE_Result TEE_EXT_GetVsimShareMem(uint32_t *addr, uint32_t *size);

/**
 * @ingroup  TEE_TA_CALLER_INDENTIFY
 * @brief  ����������TA��CA�����Ϣ
 *
 * @par ����:
 * TA����ͨ��������������������������ش�TA��CA����Ϣ,
 * ��APIֻ�����ڶ�������ʽ���е�CA
 *
 * @attention ��
 *
 * @param ca_name     [IN]		CA�İ���
 * @param ca_uid      [IN]		CA��uid
 *
 * @retval #TEE_SUCCESS               ���CA��Ϣ�ɹ�.
 * @retval #TEE_ERROR_BAD_PARAMETERS  �����������.
 * @retval #TEE_ERROR_OUT_OF_MEMORY   ϵͳ�ڴ治��.
 * @retval #TEE_ERROR_GENERIC         ��������.
 * *
 * @par ����:
 * @li tee_ext_api.h
 * @see ��
 * @since V100R007C00
*/
TEE_Result AddCaller_CA_exec(char *ca_name, uint32_t ca_uid);

/**
 * @ingroup  TEE_TA_CALLER_INDENTIFY
 * @brief  ����������TA��CA�����Ϣ
 *
 * @par ������  
 * TA����ͨ��������������������������ش�TA��CA����Ϣ,
 * ��APIֻ��������APK��ʽ���е�CA.
 
 * @attention ��
 *
 * @param ca_name       [IN]		APK�İ���
 * @param modulus       [IN]		APK֤���modulus
 * @param pub_exponent  [IN]		APK֤���pub_exponent
 *
 * @retval #TEE_SUCCESS               ���CA��Ϣ�ɹ�.
 * @retval #TEE_ERROR_BAD_PARAMETERS  �����������.
 * @retval #TEE_ERROR_OUT_OF_MEMORY   ϵͳ�ڴ治��.
 * @retval #TEE_ERROR_GENERIC         ��������.
 *
 * @par ����:
 * @li tee_ext_api.h
 * @see ��
 * @since V100R007C00
*/
TEE_Result AddCaller_CA_apk(char *ca_name, char *modulus, char *pub_exponent);

/**
 * @ingroup  TEE_TA_CALLER_INDENTIFY
 * @brief  ����������TA��TA�����Ϣ
 *
 * @par ����:
 * TA����ͨ��������������������������ش�TA��TA����Ϣ,
 * ���������TA��UUID.
 *
 * @attention ��
 *
 * @retval #TEE_SUCCESS               �ɹ����TA.
 * @retval #TEE_ERROR_BAD_PARAMETERS  �����������.
 * @retval #TEE_ERROR_OUT_OF_MEMORY   ϵͳ�ڴ治��.
 * @retval #TEE_ERROR_GENERIC         ��������.
 *
 * @par ����:
 * @li tee_ext_api.h
 * @see ��
 * @since V100R007C00
*/
TEE_Result AddCaller_TA_all(void);

/**
 * @ingroup crypto
 * @brief  ������Կderive key from device rootkey and UUID of the current task
 *
 * @par ����:
 * �����豸����Կ�Լ�TA��UUID������Կ
 *
 * @attention ��
 *
 * @param salt          [IN]            ��ֵ
 * @param size          [IN]            ��ֵ����
 * @param key           [OUT]           ָ��������Կ��ָ��
 * @param key_size      [OUT]           ������Կ��С
 *
 * @retval #TEE_SUCCESS                 �����ɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �Ƿ����
 * @retval #TEE_ERROR_GENERIC           ��������
 *
 * @par ����:
 * @li tee_ext_api.h
 * @see ��
 * @since V100R007C00
*/
TEE_Result TEE_EXT_ROOT_UuidDeriveKey(const uint8_t *salt, uint32_t size, uint8_t *key, uint32_t *key_size);

/**
 * @ingroup TEE_EXT_API
 * @brief  ֤��У��
 *
 * @par ����:
 * �����ϼ�֤��Ĺ�Կ��֤�����У��
 *
 * @attention ��
 *
 * @param cert           [IN]            ��У���֤��
 * @param cert_len       [IN]            ֤�鳤��
 * @param parent_key     [IN]            ��֤֤����Կ
 * @param parent_key_len [IN]            ��Կ����
 *
 * @retval #TEE_SUCCESS                 ִ�гɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �Ƿ����
 * @retval #TEE_ERROR_GENERIC           ��������
 *
 * @par ����:
 * @li tee_ext_api.h
 * @see ��
 * @since V100R007C00
*/
TEE_Result TEE_EXT_verify_dev_cert(const uint8_t *cert, uint32_t cert_len, const uint8_t *parent_key, uint32_t parent_key_len);

/**
 * @ingroup TEE_EXT_API
 * @brief  ����֤��
 *
 * @par ����:
 * ������Կ�������ɶ�Ӧ��֤��
 *
 * @attention ��
 *
 * @param buf          [OUT]            ���ɵ�֤��buff
 * @param len          [OUT]            ֤�鳤��
 * @param keytype      [IN]             ��Կ���� RSA 0; ECC 1
 * @param file_name    [IN]             ��Կbuff
 *
 * @retval no-zero                      ����Ϊ֤�鳤��
 * @retval #TEE_ERROR_BAD_PARAMETERS    �Ƿ����
 *
 * @par ����:
 * @li tee_ext_api.h
 * @see ��
 * @since V100R007C00
*/
TEE_Result TEE_EXT_create_cert_req(uint8_t *buf, size_t len, uint32_t keytype, const uint8_t *file_name);

/**
 * @ingroup TEE_EXT_API
 * @brief  ��ȡVerifyBoot��Ϣ
 *
 * @par ����:
 * �ӹ����ڴ��л�ȡVerifyBoot��Ϣ
 *
 * @attention ��
 *
 * @param buffer [OUT] VerifyBoot��Ϣbuff
 * @param size   [IN]  ���buff����
 *
 * @retval #TEE_SUCCESS                 ִ�гɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �Ƿ����
 * @retval #TEE_ERROR_GENERIC           ��������
 *
 * @par ����:
 * @li tee_ext_api.h
 * @see ��
 * @since V100R007C00
*/
TEE_Result TEE_EXT_GetVerifyBootInfo(const char *buffer, uint32_t size);

/**
 * @ingroup TEE_EXT_API
 * @brief  ��ȡTrustBoot������Ϣ
 *
 * @par ����:
 * �ӹ����ڴ��л�ȡTrustBoot������Ϣ
 *
 * @attention ��
 *
 * @param buffer [OUT] VerifyBoot��Ϣbuff
 * @param size   [IN]  ���buff����
 *
 * @retval #TEE_SUCCESS                 ִ�гɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �Ƿ����
 * @retval #TEE_ERROR_GENERIC           ��������
 *
 * @par ����:
 * @li tee_ext_api.h
 * @see ��
 * @since V100R007C00
*/
TEE_Result TEE_EXT_GetTrustBootImgInfo(const char *buffer, uint32_t size);

/**
 * @ingroup crypto
 * @brief  ������Կ
 *
 * @par ����:
 * �ø���ԿΪkeymaster������Կ
 *
 * @attention ��
 *
 * @param buffer [IN]  ����buffer
 * @param size   [IN]  ����buffer����
 * @param buffer [OUT] ������Կbuffer
 * @param size   [OUT] ������Կ����
 *
 * @retval #TEE_SUCCESS                 ִ�гɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �Ƿ����
 * @retval #TEE_ERROR_OUT_OF_MEMORY     ϵͳ�ڴ治��
 * @retval #TEE_ERROR_SECURITY          ��ȫ����ִ��ʧ��
 * @retval #TEE_ERROR_GENERIC           ��������
 *
 * @par ����:
 * @li tee_ext_api.h
 * @see ��
 * @since V100R007C00
*/
TEE_Result TEE_EXT_ROOT_DeriveKey2(const uint8_t *secret, uint32_t secret_len,
				   uint8_t *key, uint32_t key_len);

typedef enum {
	TEEOS_SHARED_MEM_MODEM = 0,
	TEEOS_SHARED_MEM_FINGERPRINT = 1,
	TEEOS_SHARED_MEM_ROOT_STATUS = 2,
	TEEOS_SHARED_MEM_ESE = 3,
	TEEOS_SHARED_MEM_COLORLOCK = 4,
	TEEOS_SHARED_MEM_DSS = 5,
	TEEOS_SHARED_MEM_MAILBOX = 6,
	TEEOS_SHARED_MEM_SKYTONE = 7,
	TEEOS_SHARED_MEM_NOMAP = 8,
	TEEOS_SHARED_MEM_TBIMGINFO = 9,
	TEEOS_SHARED_MEM_ES_CS = 10,
	TEEOS_SHARED_MEM_MAX,
}module_types;

/**
 * @ingroup  crypto
 * @brief  ������Կ
 *
 * @par ����:
 * ΪTA ������Կ
 *
 * @attention ��
 *
 * @param object       [IN/OUT] ObjectInfo->keytypeΪ���룬ObjectInfo->attributesΪ���
 * @param keySize      [IN]     ��Կ����
 * @param params       [IN]     δʹ��
 * @param paramCount   [IN]     δʹ��
 * @param exinfo       [IN]     �û���Ϣ��Ϊ������ֵ
 * @param exinfo_size  [IN]     �û���Ϣ���ȣ���Χ��0��64�ֽ�
 *
 * @retval #TEE_SUCCESS         ִ�гɹ�
 * @retval #others              ��������
 *
 * @par ����:
 * @li tee_ext_api.h
 * @see ��
 * @since V100R007C00
*/
TEE_Result TEE_EXT_DeriveTAPlatfromKeys(
	TEE_ObjectHandle object, uint32_t keySize,
	const TEE_Attribute *params, uint32_t paramCount,
	const uint8_t *exinfo, uint32_t exinfo_size);
/**
 * @ingroup crypto
 * @brief  ������Կ
 *
 * @par 
 * �ø���Կ������Կ
 *
 * @attention ��
 * 
 * @param salt [IN]  ����buffer
 * @param size   [IN]  ����buffer����
 * @param key [OUT] ������Կbuffer
 * @param key_size   [OUT] ������Կ����
 *
 * @retval #TEE_SUCCESS                 ִ�гɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �Ƿ����
 * @retval #TEE_ERROR_OUT_OF_MEMORY     ϵͳ�ڴ治��
 * @retval #TEE_ERROR_SECURITY          ��ȫ����ִ��ʧ��
 * @retval #TEE_ERROR_GENERIC           ��������
 *
 * @par ����:
 * @li tee_ext_api.h
 * @see ��
 * @since V100R007C00
*/
TEE_Result TEE_EXT_DeriveTARootKey(const uint8_t *salt,
				      uint32_t size,
				      uint8_t *key,
				      uint32_t key_size);

/**
 * @ingroup TEE_EXT_API
 * @brief  TA�汾У��
 *
 * @par ����:
 * ��RPMB�л�ȡTA�汾��Ϣ�����봫���TA�汾�Ƚϣ���ͬ���ؼ��ɹ������򷵻ؼ��ʧ��
 *
 * @attention ��
 *
 * @param ta_version [IN]  �����TA�汾��Ϣ
 *
 * @retval #TEE_SUCCESS                 ִ�гɹ�
 * @retval #others                      ��������
 *
 * @par ����:
 * @li tee_ext_api.h
 * @see ��
 * @since V100R007C00
*/
TEE_Result TEE_EXT_TA_version_check(uint32_t ta_version);

/**
 * @ingroup crypto
 * @brief  �Ƿ�֧��inSE
 *
 * @par ����:
 * ���ظ��豸�Ƿ�֧��inSE��֧�ַ���1����֧�ַ���0
 *
 * @attention ��
 *
 * @param ��
 *
 * @retval #INSE_CRYPTO_SUPPORT        ֧��
 * @retval #INSE_CRYPTO_NOT_SUPPORT    ��֧��
 *
 * @par ����:
 * @li tee_ext_api.h
 * @see ��
 * @since V100R007C00
*/
TEE_Result TEE_inSE_support();

/**
 * @ingroup crypto
 * @brief  SE�ӽ���
 *
 * @par ����:
 * ֧�ֽ���inSE�ӽ����Լ�mac����
 *
 * @attention ��
 *
 * @param mode          [IN]  ����ģʽ
 * @param salt          [IN]  ��ֵ
 * @param saltLen       [IN]  ��ֵ����
 * @param uuid          [IN]  TA��uuid
 * @param srcData       [IN]  ����buffer
 * @param srcLen        [IN]  ����buffer����
 * @param destData      [OUT] ���buffer
 * @param desidesstLen  [OUT] ���buff����
 *
 * @retval #TEE_SUCCESS                 ִ�гɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �Ƿ����
 * @retval #TEE_ERROR_GENERIC           ��������
 *
 * @par ����:
 * @li tee_ext_api.h
 * @see ��
 * @since V100R007C00
*/
TEE_Result TEE_EXT_SE_Crypto(TEE_OperationMode mode, const uint8_t *salt, uint32_t saltLen, TEE_UUID *uuid,
                    const uint8_t *srcData, uint32_t srcLen,
                     uint8_t *destData, uint32_t *desidesstLen);
#endif
