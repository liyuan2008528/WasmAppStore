/**
* @file tee_mem_mgnt_api.h
*
* Copyright(C), 2008-2013, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.\n
*
* �������ڴ�������API\n
*/

/** @defgroup grp_mem_api �ڴ����
*@ingroup TEE_API
*/

#ifndef __TEE_MEM_MGMT_API_H
#define __TEE_MEM_MGMT_API_H

#include "tee_internal_api.h"

#ifndef ZERO_SIZE_PTR
#define ZERO_SIZE_PTR ((void *)16)
#define ZERO_OR_NULL_PTR(x) \
	((unsigned long)(x) <= (unsigned long)ZERO_SIZE_PTR)
#endif

enum MALLOC_HINT {
	ZERO = 0,
	NOT_ZERO = 1,
	ALIGN_004 = 0x80000002, /*buf align*/
	ALIGN_008 = 0x80000003,
	ALIGN_016 = 0x80000004,
	ALIGN_032 = 0x80000005,
	ALIGN_064 = 0x80000006,
	ALIGN_128 = 0x80000007,
	ALIGN_256 = 0x80000008,
	ALIGN_004_ZERO = 0x80000012, /*buf align and set to zero*/
	ALIGN_008_ZERO = 0x80000013,
	ALIGN_016_ZERO = 0x80000014,
	ALIGN_032_ZERO = 0x80000015,
	ALIGN_064_ZERO = 0x80000016,
	ALIGN_128_ZERO = 0x80000017,
	ALIGN_256_ZERO = 0x80000018,
};

/**
* @ingroup  grp_mem_api
* @brief ��bufferָ��Ļ�������ǰsize���ֽ����Ϊx,buffer����ָ���������͵Ļ�������
*
* @par ����:
* ��
*
* @attention ��
*
* @param buffer [OUT] ָ�򻺳�����ָ��
* @param x      [IN]  ����ֵ
* @param size   [IN]  �����ֽ���
*
* @retval ��
*
* @par ����:
* @li tee_internal_api.h���ڲ��������Ͷ���
* @see ��
* @since 
**/
void TEE_MemFill(void *buffer, uint32_t x, uint32_t size);

/**
* @ingroup  grp_mem_api
* @brief ��srcָ��Ļ���������size�ֽڵ�destָ��Ļ�����
*
* @par ����:
* ��
*
* @attention src��dest����ָ���������͵Ļ�����
*
* @param dest [OUT] ָ��Ŀ�껺������ָ��
* @param src  [IN]  ָ��Դ��������ָ��
* @param size [IN]  �������ֽ���
*
* @retval ��
*
* @par ����:
* @li tee_internal_api.h���ڲ��������Ͷ���
* @see ��
* @since
**/
void TEE_MemMove(void *dest, void *src, uint32_t size);
/**
* @ingroup  grp_mem_api
* @brief ��̬�����ֽ���Ϊsize���ڴ�
*
* @par ����:
* ���ص�ָ��Ķ��뷽ʽ��֤����ָ���κ�C�����ж���Ļ������ͣ�\n
* ����hint��һ�����ݸ��������ı�־����ǰ�汾ֻʵ����һ��hintֵ��\n
* �����汾�������hint�����࣬���������ص�������
*
* @attention ��
* @param size [IN] ������ڴ��С
* @param hint [IN] �����־��0��ʾ������ڴ��ڷ���ǰ�Ѿ������㣬����ֵ��������
*
* @retval ������NULL��ֵ ָ�����뵽���ڴ��ָ��
* @retval NULL ��ʾ����ʧ��
*
* @par ����:
* @li tee_internal_api.h���ڲ��������Ͷ���
* @see TEE_Realloc | TEE_Free
* @since
**/
void *TEE_Malloc(size_t size, uint32_t hint);

/**
* @ingroup  grp_mem_api
* @brief �ͷŶ�̬������ڴ�
*
* @par ����:
* ���buffer����NULL����ôTEE_Free�����κζ�����\n
* �û���Ҫע�⴫�ݵ�bufferָ����ͨ��TEE_Malloc����TEE_Realloc����ģ�\n
* ����û�б�TEE_Free�ͷŹ���������������Ԥ�ϡ�
*
* @attention ����ڴ��漰�û�������Ϣ����Ҫ��Free֮ǰ����������߻�������������
* @param buffer [IN] ָ����Ҫ�ͷŵ��ڴ��ָ��
*
* @retval ��
*
* @par ����:
* @li tee_internal_api.h���ڲ��������Ͷ���
* @see TEE_Malloc | TEE_Realloc
* @since
**/
void TEE_Free(void *buffer);

/**
* @ingroup grp_mem_api
* @brief �޸Ķ�̬�ڴ�Ĵ�С
*
* @par ����:
* �޸Ĵ�С����ڴ��������ԭʼ��С��ԭ�ڴ��е����ݻᱻ�������������ֵ�����������ġ�\n
* �ڸ����ڴ��Сʱ��������Ҫ���������ڴ棬�����ʱ����ʧ�ܣ���ôԭʼ�ڴ�ͻᱻ������\n
* ͬʱ��������NULL��\n
* ���buffer����NULL����ô�������ܾ���TEE_Malloc��ͬ��
*
* @attention
* �û���Ҫע�⴫�ݵ�bufferָ����ͨ��TEE_Malloc����TEE_Realloc����ģ�
* ����û�б�TEE_Free�ͷŹ���������������Ԥ�ϡ�
*
* @param buffer   [IN] ָ����Ҫ�޸Ĵ�С���ڴ��ָ��
* @param new_size [IN] �޸ĺ�Ĵ�С
*
* @retval ������NULL��ֵ ָ���µĶ�̬�ڴ��ָ��
* @retval NULL           ��ʾ����ʧ��
*
* @par ����:
* @li tee_internal_api.h���ڲ��������Ͷ���
* @see TEE_Malloc | TEE_Free
**/
void *TEE_Realloc(void *buffer, uint32_t new_size);

/**
* @ingroup grp_mem_api
* @brief �ڴ����ݱȽ�
*
* @par ����:
* �ַ�����С�ǰ���˳��Ƚ�ÿ���ַ���ASCII��С��ֱ�����ִ�С��һ�����ַ����߽�������
*
* @attention ��
* @param buffer1 [IN] ָ��Ƚϵĵ�һ����������ָ��
* @param buffer2 [IN] ָ��Ƚϵĵڶ�����������ָ��
* @param size    [IN] �Ƚϵ��ֽ���
*
* @retval #-1 buffer1ָ��Ļ�����С��buffer2ָ��Ļ�����
* @retval #0  buffer1ָ��Ļ���������buffer2ָ��Ļ�����
* @retval #1  buffer1ָ��Ļ���������buffer2ָ��Ļ�����
*
* @par ����:
* @li tee_internal_api.h���ڲ��������Ͷ���
* @see ��
* @since
**/
int32_t TEE_MemCompare(void *buffer1, void *buffer2, uint32_t size);

/**
* @ingroup grp_mem_api
* @brief
* ����һ��ȫ�ֱ�������ͬһInstance�ڵĶ��Session�乲��\n
* Instance��Session�ľ����������û������ֲ���Ӧ�½ڡ�
*
* @par ����:
* ��
*
* @attention ��
* @param instanceData [IN] ���õ�ȫ�ֱ����ĵ�ַ
*
* @retval ��
*
* @par ����:
* @li tee_internal_api.h���ڲ��������Ͷ���
* @see ��
* @since
**/
void TEE_SetInstanceData(void *instanceData);

/**
* @ingroup grp_mem_api
* @brief ��ȡTEE_SetInstanceData���õ�ȫ�ֱ�����ָ��
*
* @par ����:
* ��
*
* @attention ��
* @param ��
*
* @retval ������NULL��ֵ ָ��TEE_SetInstanceData���õ�ȫ�ֱ�����ָ��
* @retval NULL û��InstanceData������
*
* @par ����:
* @li tee_internal_api.h���ڲ��������Ͷ���
* @see ��
* @since
**/
void *TEE_GetInstanceData(void);

/**
* @ingroup grep_mem_api
* @brief ����СΪsize��buffer�Ƿ����ڰ�ȫ�ڴ�
*
* @par ����:
* ���buffer��Ӧ�����ַ�Ƿ���TEEOS�ڴ桢��̬ION��̬ION��
*
* @attention 
* �������Ȼ���buffer��Ӧ��ַ��ӳ���Ƿ���Ч
*
* @param buffer [IN] ��Ҫ����buffer
* @param size   [IN] ��Ҫ���buffer�ĳ���
*
* @retval #true    �ǰ�ȫ�ڴ�
* @retval #false   ��Ч��ַ��ǰ�ȫ�ڴ�
* 
* @par ����:
* @li tee_internal_api.h���ڲ��������Ͷ���
* @see ��
* @since
* */
bool TEE_IsSecureMemory(void *buffer, uint32_t size);

/**
* @ingroup grep_mem_api
* @brief ��ȡ�ڴ�ʹ�����
*
* @par ����:
* �ú���Ŀǰδʵ��
*
* @attention ��
*
* @param show [IN] �Ƿ��ӡ
*
* @retval #1 ���ض�ֵ
*
* @par ����:
* @li tee_internal_api.h���ڲ��������Ͷ���
* @see ��
* @since
* */
uint32_t get_mem_usage(bool show);

/**
* @ingroup grep_mem_api
* @breief Ŀǰ�ѵ�ʹ����
*
* @par ����:
* ��õ�ǰ�ѵ�ʹ�����
*
* @attention ��
*
* @param show [IN] �Ƿ��ӡ
*
* @retval #uint32 ʹ����
*
* @par ����:
* @li tee_internal_api.h���ڲ��������Ͷ���
* @see ��
* @since
* */
uint32_t get_heap_usage(bool show);

#endif
