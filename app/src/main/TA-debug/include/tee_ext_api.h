/**
 * @file tee_ext_api.h
 *
 * Copyright(C), 2008-2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：定义非GP标准的安全服务接口\n
 */

/**
 * @defgroup TEE_TA_CALLER_INDENTIFY  安全侧TA鉴权CA接口
 * @defgroup TEE_EXT_API  TEE侧EXT接口
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
 * REE侧信息结构体
*/
struct __ree_info {
	uint32_t userid;
	uint32_t appid;
	uint32_t reserve;
};

typedef struct __ree_info ree_info;

/**
 * @ingroup  TEE_EXT_API
 * @brief 获取REE侧信息
 *
 * @par 描述:
 * 向global发送请求，获取REE侧信息，包括userid以及appid
 *
 * @attention 无
 *
 * @param ree_info_data     [OUT]       输出数据
 * @param length            [OUT]       输出数据长度
 *
 * @retval #TEE_SUCCESS                 获取成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    输入参数错误
 * @retval #TEE_ERROR_OUT_OF_MEMORY     分配内存失败
 *
 * @par 依赖:
 * @li tee_ext_api.h 扩展API头文件
 * @see 无
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
 * 调用者信息结构体
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
 * @brief 获取设备唯一ID
 *
 * @par 描述:
 * 获取设备唯一ID信息
 *
 * @attention 无
 *
 * @param DevUniqueID       [OUT]       输出数据
 * @param length            [OUT]       输出数据长度
 *
 * @retval #TEE_SUCCESS                 获取成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    输入参数错误
 * @retval #TEE_ERROR_OUT_OF_MEMORY     分配内存失败
 *
 * @par 依赖:
 * @li tee_ext_api.h 扩展API头文件
 * @see 无
 * @since V100R005C00
*/
TEE_Result TEE_EXT_GetDeviceUniqueId(uint8_t *DevUniqueID,  uint32_t *length);

/**
 * @ingroup  TEE_EXT_API
 * @brief 获取Agent信息
 *
 * @par 描述:
 * 根据agent_id获取session_context信息及参数类型信息
 *
 * @attention 无
 *
 * @param agent_id     [IN]        输入数据
 * @param buffer       [OUT]       输出数据
 * @param length       [OUT]       输出数据长度
 *
 * @retval #TEE_SUCCESS                 获取成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    输入参数错误
 * @retval #TEE_ERROR_GENERIC     操作失败
 *
 * @par 依赖:
 * @li tee_ext_api.h 扩展API头文件
 * @see 无
 * @since V100R005C00
*/
TEE_Result TEE_EXT_GetAgentBuffer(uint32_t agent_id, void **buffer, uint32_t *length);

/**
 * @ingroup  TEE_EXT_API
 * @brief 获取会话发起者信息
 *
 * @par 描述:
 * 获取尝试加载TA的程序的session类型
 * 如果是TA2TA，则同时获取会话发起者的UUID
 *
 * @attention 无
 *
 * @param caller_info_data    [OUT]       输出数据
 * @param length              [OUT]       输出数据长度
 *
 * @retval #TEE_SUCCESS                 加解密成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    输入参数错误
 * @retval #TEE_ERROR_SECURITY          安全函数执行失败
 *
 * @par 依赖:
 * @li tee_ext_api.h 扩展API头文件
 * @see 无
 * @since V100R005C00
*/
TEE_Result TEE_EXT_GetCallerInfo(caller_info *caller_info_data, uint32_t length);

/**
 * @ingroup  crypto
 * @brief AES加解密集成模式
 *
 * @par 描述:
 * AES集成加解密，目前支持AES_CBC_NOPAD,AES_ECB_PKCS5，可以通过rootkey派生密钥
 *
 * @attention 
 * 目前只支持ECB和CBC
 *
 * @param DB        [IN]        是否用传入的key和rootkey派生密钥
 * @param IV        [IN]        初始化向量指针
 * @param mode      [IN]        0:加密;1:解密
 * @param algothem  [IN]        AES算法 #TEE_CRYPTO_ALGORITHM_ID
 * @param key       [IN]        密钥指针
 * @param key_len   [IN]        指针长度
 * @param cyp_src   [IN]        输入数据
 * @param dst       [OUT]       输出数据
 * @param srclen    [IN]        输入数据长度
 * @param dstlen    [OUT]       输出数据长度
 *
 * @retval #TEE_SUCCESS                 加解密成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    输入参数错误
 * @retval #TEE_ERROR_OUT_OF_MEMORY     分配内存失败
 *
 * @par 依赖:
 * @li crypto 加解密模块
 * @li tee_ext_api.h 扩展API头文件
 * @see TEE_CipherInit | TEE_CipherUpdate | TEE_CipherDoFinal
 * @since V100R005C00
*/
TEE_Result TEE_EXT_AES_CRYPTO(bool DB, const uint8_t *IV, bool mode, uint32_t algothem, const uint8_t *key, uint32_t key_len,
			      const uint8_t *cyp_src, uint8_t *dst, uint32_t srclen, uint32_t *dstlen);

/**
 * @ingroup  crypto
 * @brief 计算摘要
 *
 * @par 描述:
 * 计算摘要
 *
 * @attention 无
 *
 * @param algorithm     [IN]            摘要算法，如SHA1,SHA256
 * @param DataIn_ptr    [IN]            输入数据
 * @param DataSize      [IN]            输入数据长度
 * @param hash_result   [OUT]           摘要结果 SHA1 20bytes;SHA256 32bytes
 *
 * @retval #TEE_SUCCESS                 摘要成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    输入参数错误
 * @retval #TEE_ERROR_GENERIC           摘要失败
 *
 * @par 依赖:
 * @li crypto 加解密模块
 * @li tee_ext_api.h 扩展API头文件
 * @since V100R005C00
*/
TEE_Result TEE_EXT_HASH(TEE_CRYPTO_ALGORITHM_ID algorithm, const uint8_t *DataIn_ptr, uint32_t DataSize, uint8_t *hash_result);

/**
 * @ingroup  crypto
 * @brief 生成RSA密钥对
 *
 * @par 描述:
 * RSA密钥对生成，输出为加密后密钥对数据结构
 *
 * @attention 
 * 输出密钥对数据结构只能用于本模块产生密钥
 *
 * @param pubExp        [IN]        公钥的exponent 例如0x10001
 * @param key_size      [IN]        密钥长度 一般为2048bit
 * @param key_blob      [OUT]       加密后的密钥对数据结构
 * @param key_blob_size [OUT]       key_blob长度
 *
 * @retval #TEE_SUCCESS                 加解密成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    输入参数错误
 * @retval #TEE_ERROR_OUT_OF_MEMORY     分配内存失败
 *
 * @par 依赖:
 * @li crypto 加解密模块
 * @li tee_ext_api.h 扩展API头文件
 * @see 无
 * @since V100R005C00
*/
TEE_Result TEE_EXT_generate_keypair(uint32_t pubExp, uint32_t key_size, uint8_t *key_blob, uint32_t *key_blob_size);

/**
 * @ingroup  crypto
 * @brief 获取公钥
 *
 * @par 描述:
 * RSA公钥获取
 *
 * @attention 无
 *
 * @param key_blob      [IN]        密钥对数据结构
 * @param exopnent      [OUT]       公钥的exponent
 * @param modulus       [OUT]       公钥的modulus
 * @param exponentSize  [OUT]       exponent长度
 * @param modulusSize   [OUT]       modulus长度
 *
 * @retval #TEE_SUCCESS                 获取公钥成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    输入参数错误
 * @retval #TEE_ERROR_GENERIC           获取公钥失败
 *
 * @par 依赖:
 * @li crypto 加解密模块
 * @li tee_ext_api.h 扩展API头文件
 * @see 无
 * @since V100R005C00
*/
TEE_Result TEE_EXT_get_keypair_public(uint8_t *key_blob, uint8_t *exopnent, uint8_t *modulus,
				      uint32_t *exponentSize, uint32_t *modulusSize);

/**
 * @ingroup  crypto
 * @brief 对数据签名
 *
 * @par 描述:
 * 对数据签名，算法有限制，目前支持pkcs1v15和pkcs1v21以及nopad
 *
 * @attention 无
 *
 * @param algorithm     [IN]        RSA算法
 * @param key_blob      [IN]        密钥对数据结构
 * @param datain        [IN]        需要签名的数据
 * @param inSize        [IN]        需要签名数据长度
 * @param dataout       [OUT]       签名后的数据
 * @param outSize       [OUT]       签名后的数据长度
 *
 * @retval #TEE_SUCCESS                 获取公钥成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    输入参数错误
 * @retval #TEE_ERROR_GENERIC           获取公钥失败
 * @retval #TEE_ERROR_OUT_OF_MEMORY     分配内存失败
 * @retval #TEE_ERROR_NOT_SUPPORTED     算法不支持
 *
 * @par 依赖:
 * @li crypto 加解密模块
 * @li tee_ext_api.h 扩展API头文件
 * @see 无
 * @since V100R005C00
*/
TEE_Result TEE_EXT_sign_data(TEE_CRYPTO_ALGORITHM_ID algorithm, uint8_t *key_blob, uint8_t *datain,
			     uint32_t inSize, uint8_t *dataout, uint32_t *outSize);

/**
 * @ingroup  crypto
 * @brief 对数据签名
 *
 * @par 描述:
 * 对数据签名，算法有限制，目前支持pkcs1v15和pkcs1v21以及nopad
 *
 * @attention 无
 *
 * @param algorithm     [IN]        RSA算法
 * @param key_blob      [IN]        密钥对数据结构
 * @param srcData       [IN]        需要解密的数据
 * @param srcLen        [IN]        需要解密数据长度
 * @param destData      [OUT]       解密后的数据
 * @param destLen       [OUT]       解密后的数据长度
 *
 * @retval #TEE_SUCCESS                 获取公钥成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    输入参数错误
 * @retval #TEE_ERROR_GENERIC           获取公钥失败
 * @retval #TEE_ERROR_OUT_OF_MEMORY     分配内存失败
 * @retval #TEE_ERROR_NOT_SUPPORTED     算法不支持
 *
 * @par 依赖:
 * @li crypto 加解密模块
 * @li tee_ext_api.h 扩展API头文件
 * @see 无
 * @since V100R005C00
*/
TEE_Result TEE_EXT_RSA_decrypt(TEE_CRYPTO_ALGORITHM_ID algorithm, uint8_t *key_blob,
			       uint8_t *srcData, uint32_t srcLen, uint8_t *destData, uint32_t *destLen);

/**
 * @ingroup  TEE_EXT_API
 * @brief 获取设备是否被root
 *
 * @par 描述:
 * 获取设备root信息，若设备已经被root，返回1，没有被root返回0
 *
 * @attention 无
 *
 * @param 无
 *
 * @retval #true    设备已经root
 * @retval #false   设备没有root
 *
 * @par 依赖:
 * @li tee_ext_api.h 扩展API头文件
 * @see 无
 * @since V100R005C00
*/
bool TEE_EXT_IsDeviceRooted(void);

/**
 * @ingroup  TEE_EXT_API
 * @brief 检查设备的root状态
 *
 * @par 描述:
 * 查设备的root状态，最低位表示总体状态
 *
 * @attention 无
 *
 * @param 无
 *
 * @retval #state    设备root状态
 *
 * @par 依赖:
 * @li tee_ext_api.h 扩展API头文件
 * @see 无
 * @since V100R005C00
 */
uint32_t TEE_EXT_DeviceRootStatus(void);

/**
 * @ingroup TEE_EXT_API
 * @brief 获取vsim共享内存 
 * 
 * @par 描述:
 * 获取vsim共享内存 成功返回success，失败返回错误码
 *
 * @attention 无
 *
 * @param addr      [OUT]       共享内存地址
 * @param size      [OUT]        共享内存大小
 *
 * @retval #TEE_SUCCESS                 成功获取共享内存
 * @retval #TEE_ERROR_BAD_PARAMETERS    参数错误
 * @retval #TEE_ERROR_GENERIC           内存映射失败
 *
 * @par 依赖:
 * @li tee_ext_api.h 扩展API头文件
 * @see 无
 * @since V100R005C00
*/
TEE_Result TEE_EXT_GetVsimShareMem(uint32_t *addr, uint32_t *size);

/**
 * @ingroup  TEE_TA_CALLER_INDENTIFY
 * @brief  添加允许加载TA的CA身份信息
 *
 * @par 描述:
 * TA可以通过调用这个函数，来添加允许加载此TA的CA的信息,
 * 该API只适用于二进制形式运行的CA
 *
 * @attention 无
 *
 * @param ca_name     [IN]		CA的包名
 * @param ca_uid      [IN]		CA的uid
 *
 * @retval #TEE_SUCCESS               添加CA信息成功.
 * @retval #TEE_ERROR_BAD_PARAMETERS  输入参数错误.
 * @retval #TEE_ERROR_OUT_OF_MEMORY   系统内存不足.
 * @retval #TEE_ERROR_GENERIC         其他错误.
 * *
 * @par 依赖:
 * @li tee_ext_api.h
 * @see 无
 * @since V100R007C00
*/
TEE_Result AddCaller_CA_exec(char *ca_name, uint32_t ca_uid);

/**
 * @ingroup  TEE_TA_CALLER_INDENTIFY
 * @brief  添加允许加载TA的CA身份信息
 *
 * @par 描述：  
 * TA可以通过调用这个函数，来添加允许加载此TA的CA的信息,
 * 该API只适用于以APK形式运行的CA.
 
 * @attention 无
 *
 * @param ca_name       [IN]		APK的包名
 * @param modulus       [IN]		APK证书的modulus
 * @param pub_exponent  [IN]		APK证书的pub_exponent
 *
 * @retval #TEE_SUCCESS               添加CA信息成功.
 * @retval #TEE_ERROR_BAD_PARAMETERS  输入参数错误.
 * @retval #TEE_ERROR_OUT_OF_MEMORY   系统内存不足.
 * @retval #TEE_ERROR_GENERIC         其他错误.
 *
 * @par 依赖:
 * @li tee_ext_api.h
 * @see 无
 * @since V100R007C00
*/
TEE_Result AddCaller_CA_apk(char *ca_name, char *modulus, char *pub_exponent);

/**
 * @ingroup  TEE_TA_CALLER_INDENTIFY
 * @brief  添加允许加载TA的TA身份信息
 *
 * @par 依赖:
 * TA可以通过调用这个函数，来添加允许加载此TA的TA的信息,
 * 且无需添加TA的UUID.
 *
 * @attention 无
 *
 * @retval #TEE_SUCCESS               成功添加TA.
 * @retval #TEE_ERROR_BAD_PARAMETERS  输入参数错误.
 * @retval #TEE_ERROR_OUT_OF_MEMORY   系统内存不足.
 * @retval #TEE_ERROR_GENERIC         其他错误.
 *
 * @par 依赖:
 * @li tee_ext_api.h
 * @see 无
 * @since V100R007C00
*/
TEE_Result AddCaller_TA_all(void);

/**
 * @ingroup crypto
 * @brief  派生密钥derive key from device rootkey and UUID of the current task
 *
 * @par 依赖:
 * 根据设备根密钥以及TA的UUID派生密钥
 *
 * @attention 无
 *
 * @param salt          [IN]            盐值
 * @param size          [IN]            盐值长度
 * @param key           [OUT]           指向派生密钥的指针
 * @param key_size      [OUT]           派生密钥大小
 *
 * @retval #TEE_SUCCESS                 派生成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    非法入参
 * @retval #TEE_ERROR_GENERIC           其他错误
 *
 * @par 依赖:
 * @li tee_ext_api.h
 * @see 无
 * @since V100R007C00
*/
TEE_Result TEE_EXT_ROOT_UuidDeriveKey(const uint8_t *salt, uint32_t size, uint8_t *key, uint32_t *key_size);

/**
 * @ingroup TEE_EXT_API
 * @brief  证书校验
 *
 * @par 描述:
 * 根据上级证书的公钥对证书进行校验
 *
 * @attention 无
 *
 * @param cert           [IN]            待校验的证书
 * @param cert_len       [IN]            证书长度
 * @param parent_key     [IN]            验证证书密钥
 * @param parent_key_len [IN]            密钥长度
 *
 * @retval #TEE_SUCCESS                 执行成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    非法入参
 * @retval #TEE_ERROR_GENERIC           其他错误
 *
 * @par 依赖:
 * @li tee_ext_api.h
 * @see 无
 * @since V100R007C00
*/
TEE_Result TEE_EXT_verify_dev_cert(const uint8_t *cert, uint32_t cert_len, const uint8_t *parent_key, uint32_t parent_key_len);

/**
 * @ingroup TEE_EXT_API
 * @brief  生成证书
 *
 * @par 描述:
 * 根据密钥类型生成对应的证书
 *
 * @attention 无
 *
 * @param buf          [OUT]            生成的证书buff
 * @param len          [OUT]            证书长度
 * @param keytype      [IN]             密钥类型 RSA 0; ECC 1
 * @param file_name    [IN]             密钥buff
 *
 * @retval no-zero                      返回为证书长度
 * @retval #TEE_ERROR_BAD_PARAMETERS    非法入参
 *
 * @par 依赖:
 * @li tee_ext_api.h
 * @see 无
 * @since V100R007C00
*/
TEE_Result TEE_EXT_create_cert_req(uint8_t *buf, size_t len, uint32_t keytype, const uint8_t *file_name);

/**
 * @ingroup TEE_EXT_API
 * @brief  获取VerifyBoot信息
 *
 * @par 描述:
 * 从共享内存中获取VerifyBoot信息
 *
 * @attention 无
 *
 * @param buffer [OUT] VerifyBoot信息buff
 * @param size   [IN]  输出buff长度
 *
 * @retval #TEE_SUCCESS                 执行成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    非法入参
 * @retval #TEE_ERROR_GENERIC           其他错误
 *
 * @par 依赖:
 * @li tee_ext_api.h
 * @see 无
 * @since V100R007C00
*/
TEE_Result TEE_EXT_GetVerifyBootInfo(const char *buffer, uint32_t size);

/**
 * @ingroup TEE_EXT_API
 * @brief  获取TrustBoot镜像信息
 *
 * @par 描述:
 * 从共享内存中获取TrustBoot镜像信息
 *
 * @attention 无
 *
 * @param buffer [OUT] VerifyBoot信息buff
 * @param size   [IN]  输出buff长度
 *
 * @retval #TEE_SUCCESS                 执行成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    非法入参
 * @retval #TEE_ERROR_GENERIC           其他错误
 *
 * @par 依赖:
 * @li tee_ext_api.h
 * @see 无
 * @since V100R007C00
*/
TEE_Result TEE_EXT_GetTrustBootImgInfo(const char *buffer, uint32_t size);

/**
 * @ingroup crypto
 * @brief  派生密钥
 *
 * @par 描述:
 * 用根密钥为keymaster派生密钥
 *
 * @attention 无
 *
 * @param buffer [IN]  输入buffer
 * @param size   [IN]  输入buffer长度
 * @param buffer [OUT] 派生密钥buffer
 * @param size   [OUT] 派生密钥长度
 *
 * @retval #TEE_SUCCESS                 执行成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    非法入参
 * @retval #TEE_ERROR_OUT_OF_MEMORY     系统内存不足
 * @retval #TEE_ERROR_SECURITY          安全函数执行失败
 * @retval #TEE_ERROR_GENERIC           其他错误
 *
 * @par 依赖:
 * @li tee_ext_api.h
 * @see 无
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
 * @brief  派生密钥
 *
 * @par 描述:
 * 为TA 派生密钥
 *
 * @attention 无
 *
 * @param object       [IN/OUT] ObjectInfo->keytype为输入，ObjectInfo->attributes为输出
 * @param keySize      [IN]     密钥长度
 * @param params       [IN]     未使用
 * @param paramCount   [IN]     未使用
 * @param exinfo       [IN]     用户信息作为派生盐值
 * @param exinfo_size  [IN]     用户信息长度，范围是0到64字节
 *
 * @retval #TEE_SUCCESS         执行成功
 * @retval #others              其他错误
 *
 * @par 依赖:
 * @li tee_ext_api.h
 * @see 无
 * @since V100R007C00
*/
TEE_Result TEE_EXT_DeriveTAPlatfromKeys(
	TEE_ObjectHandle object, uint32_t keySize,
	const TEE_Attribute *params, uint32_t paramCount,
	const uint8_t *exinfo, uint32_t exinfo_size);
/**
 * @ingroup crypto
 * @brief  派生密钥
 *
 * @par 
 * 用根密钥派生密钥
 *
 * @attention 无
 * 
 * @param salt [IN]  输入buffer
 * @param size   [IN]  输入buffer长度
 * @param key [OUT] 派生密钥buffer
 * @param key_size   [OUT] 派生密钥长度
 *
 * @retval #TEE_SUCCESS                 执行成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    非法入参
 * @retval #TEE_ERROR_OUT_OF_MEMORY     系统内存不足
 * @retval #TEE_ERROR_SECURITY          安全函数执行失败
 * @retval #TEE_ERROR_GENERIC           其他错误
 *
 * @par 依赖:
 * @li tee_ext_api.h
 * @see 无
 * @since V100R007C00
*/
TEE_Result TEE_EXT_DeriveTARootKey(const uint8_t *salt,
				      uint32_t size,
				      uint8_t *key,
				      uint32_t key_size);

/**
 * @ingroup TEE_EXT_API
 * @brief  TA版本校验
 *
 * @par 描述:
 * 从RPMB中获取TA版本信息，并与传入的TA版本比较，相同返回检查成功，否则返回检查失败
 *
 * @attention 无
 *
 * @param ta_version [IN]  传入的TA版本信息
 *
 * @retval #TEE_SUCCESS                 执行成功
 * @retval #others                      其他错误
 *
 * @par 依赖:
 * @li tee_ext_api.h
 * @see 无
 * @since V100R007C00
*/
TEE_Result TEE_EXT_TA_version_check(uint32_t ta_version);

/**
 * @ingroup crypto
 * @brief  是否支持inSE
 *
 * @par 描述:
 * 返回该设备是否支持inSE，支持返回1，不支持返回0
 *
 * @attention 无
 *
 * @param 无
 *
 * @retval #INSE_CRYPTO_SUPPORT        支持
 * @retval #INSE_CRYPTO_NOT_SUPPORT    不支持
 *
 * @par 依赖:
 * @li tee_ext_api.h
 * @see 无
 * @since V100R007C00
*/
TEE_Result TEE_inSE_support();

/**
 * @ingroup crypto
 * @brief  SE加解密
 *
 * @par 描述:
 * 支持进行inSE加解密以及mac操作
 *
 * @attention 无
 *
 * @param mode          [IN]  操作模式
 * @param salt          [IN]  盐值
 * @param saltLen       [IN]  盐值长度
 * @param uuid          [IN]  TA的uuid
 * @param srcData       [IN]  输入buffer
 * @param srcLen        [IN]  输入buffer长度
 * @param destData      [OUT] 输出buffer
 * @param desidesstLen  [OUT] 输出buff长度
 *
 * @retval #TEE_SUCCESS                 执行成功
 * @retval #TEE_ERROR_BAD_PARAMETERS    非法入参
 * @retval #TEE_ERROR_GENERIC           其他错误
 *
 * @par 依赖:
 * @li tee_ext_api.h
 * @see 无
 * @since V100R007C00
*/
TEE_Result TEE_EXT_SE_Crypto(TEE_OperationMode mode, const uint8_t *salt, uint32_t saltLen, TEE_UUID *uuid,
                    const uint8_t *srcData, uint32_t srcLen,
                     uint8_t *destData, uint32_t *desidesstLen);
#endif
