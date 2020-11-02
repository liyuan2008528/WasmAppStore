/**
* @file tee_mem_mgnt_api.h
*
* Copyright(C), 2008-2013, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.\n
*
* 描述：内存管理相关API\n
*/

/** @defgroup grp_mem_api 内存管理
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
* @brief 将buffer指向的缓冲区的前size个字节填充为x,buffer可以指向任意类型的缓冲区。
*
* @par 描述:
* 无
*
* @attention 无
*
* @param buffer [OUT] 指向缓冲区的指针
* @param x      [IN]  填充的值
* @param size   [IN]  填充的字节数
*
* @retval 无
*
* @par 依赖:
* @li tee_internal_api.h：内部数据类型定义
* @see 无
* @since 
**/
void TEE_MemFill(void *buffer, uint32_t x, uint32_t size);

/**
* @ingroup  grp_mem_api
* @brief 从src指向的缓冲区拷贝size字节到dest指向的缓冲区
*
* @par 描述:
* 无
*
* @attention src和dest可以指向任意类型的缓冲区
*
* @param dest [OUT] 指向目标缓冲区的指针
* @param src  [IN]  指向源缓冲区的指针
* @param size [IN]  拷贝的字节数
*
* @retval 无
*
* @par 依赖:
* @li tee_internal_api.h：内部数据类型定义
* @see 无
* @since
**/
void TEE_MemMove(void *dest, void *src, uint32_t size);
/**
* @ingroup  grp_mem_api
* @brief 动态申请字节数为size的内存
*
* @par 描述:
* 返回的指针的对齐方式保证可以指向任何C语言中定义的基本类型，\n
* 参数hint是一个传递给分配器的标志。当前版本只实现了一种hint值，\n
* 后续版本如果增加hint的种类，则会增加相关的描述。
*
* @attention 无
* @param size [IN] 申请的内存大小
* @param hint [IN] 分配标志，0表示申请的内存在返回前已经被清零，其它值都被忽略
*
* @retval 不等于NULL的值 指向申请到的内存的指针
* @retval NULL 表示申请失败
*
* @par 依赖:
* @li tee_internal_api.h：内部数据类型定义
* @see TEE_Realloc | TEE_Free
* @since
**/
void *TEE_Malloc(size_t size, uint32_t hint);

/**
* @ingroup  grp_mem_api
* @brief 释放动态申请的内存
*
* @par 描述:
* 如果buffer等于NULL，那么TEE_Free不做任何动作。\n
* 用户需要注意传递的buffer指针是通过TEE_Malloc或者TEE_Realloc申请的，\n
* 并且没有被TEE_Free释放过，否则后果将不可预料。
*
* @attention 如果内存涉及用户敏感信息，需要在Free之前先做清零或者混淆等脱敏操作
* @param buffer [IN] 指向需要释放的内存的指针
*
* @retval 无
*
* @par 依赖:
* @li tee_internal_api.h：内部数据类型定义
* @see TEE_Malloc | TEE_Realloc
* @since
**/
void TEE_Free(void *buffer);

/**
* @ingroup grp_mem_api
* @brief 修改动态内存的大小
*
* @par 描述:
* 修改大小后的内存如果大于原始大小，原内存中的内容会被保留，超出部分的内容是任意的。\n
* 在更改内存大小时，可能需要重新申请内存，如果这时分配失败，那么原始内存就会被保留，\n
* 同时函数返回NULL。\n
* 如果buffer等于NULL，那么函数功能就与TEE_Malloc相同。
*
* @attention
* 用户需要注意传递的buffer指针是通过TEE_Malloc或者TEE_Realloc申请的，
* 并且没有被TEE_Free释放过，否则后果将不可预料。
*
* @param buffer   [IN] 指向需要修改大小的内存的指针
* @param new_size [IN] 修改后的大小
*
* @retval 不等于NULL的值 指向新的动态内存的指针
* @retval NULL           表示申请失败
*
* @par 依赖:
* @li tee_internal_api.h：内部数据类型定义
* @see TEE_Malloc | TEE_Free
**/
void *TEE_Realloc(void *buffer, uint32_t new_size);

/**
* @ingroup grp_mem_api
* @brief 内存内容比较
*
* @par 描述:
* 字符串大小是按照顺序比较每个字符的ASCII大小，直到出现大小不一样的字符或者结束符。
*
* @attention 无
* @param buffer1 [IN] 指向比较的第一个缓冲区的指针
* @param buffer2 [IN] 指向比较的第二个缓冲区的指针
* @param size    [IN] 比较的字节数
*
* @retval #-1 buffer1指向的缓冲区小于buffer2指向的缓冲区
* @retval #0  buffer1指向的缓冲区等于buffer2指向的缓冲区
* @retval #1  buffer1指向的缓冲区大于buffer2指向的缓冲区
*
* @par 依赖:
* @li tee_internal_api.h：内部数据类型定义
* @see 无
* @since
**/
int32_t TEE_MemCompare(void *buffer1, void *buffer2, uint32_t size);

/**
* @ingroup grp_mem_api
* @brief
* 设置一个全局变量用于同一Instance内的多个Session间共享。\n
* Instance和Session的具体描述见用户开发手册相应章节。
*
* @par 描述:
* 无
*
* @attention 无
* @param instanceData [IN] 设置的全局变量的地址
*
* @retval 无
*
* @par 依赖:
* @li tee_internal_api.h：内部数据类型定义
* @see 无
* @since
**/
void TEE_SetInstanceData(void *instanceData);

/**
* @ingroup grp_mem_api
* @brief 获取TEE_SetInstanceData设置的全局变量的指针
*
* @par 描述:
* 无
*
* @attention 无
* @param 无
*
* @retval 不等于NULL的值 指向TEE_SetInstanceData设置的全局变量的指针
* @retval NULL 没有InstanceData被设置
*
* @par 依赖:
* @li tee_internal_api.h：内部数据类型定义
* @see 无
* @since
**/
void *TEE_GetInstanceData(void);

/**
* @ingroup grep_mem_api
* @brief 检查大小为size的buffer是否属于安全内存
*
* @par 描述:
* 检查buffer对应物理地址是否在TEEOS内存、静态ION或动态ION中
*
* @attention 
* 函数首先会检查buffer对应物址的映射是否有效
*
* @param buffer [IN] 需要检查的buffer
* @param size   [IN] 需要检查buffer的长度
*
* @retval #true    是安全内存
* @retval #false   无效地址或非安全内存
* 
* @par 依赖:
* @li tee_internal_api.h：内部数据类型定义
* @see 无
* @since
* */
bool TEE_IsSecureMemory(void *buffer, uint32_t size);

/**
* @ingroup grep_mem_api
* @brief 获取内存使用情况
*
* @par 描述:
* 该函数目前未实现
*
* @attention 无
*
* @param show [IN] 是否打印
*
* @retval #1 返回定值
*
* @par 依赖:
* @li tee_internal_api.h：内部数据类型定义
* @see 无
* @since
* */
uint32_t get_mem_usage(bool show);

/**
* @ingroup grep_mem_api
* @breief 目前堆的使用率
*
* @par 描述:
* 获得当前堆的使用情况
*
* @attention 无
*
* @param show [IN] 是否打印
*
* @retval #uint32 使用率
*
* @par 依赖:
* @li tee_internal_api.h：内部数据类型定义
* @see 无
* @since
* */
uint32_t get_heap_usage(bool show);

#endif
