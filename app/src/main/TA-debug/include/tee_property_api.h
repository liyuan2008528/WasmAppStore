/**
* @file tee_property_api.h
*
* Copyright(C), 2008-2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.\n
*
* 描述：安全世界安全属性相关API\n
*/

/**
* @defgroup TEE_PROPERTY_API  TEE安全属性
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
* @brief 请求Property，以String形式返回
*
* @par 描述:
* TEE_GetPropertyAsString函数在属性集中执行查找以检索单个属性并将其值转换为可打
* 印字符串。 当查找成功时，实现必须将属性转换为可打印的字符串，并将结果复制到
* valueBuffer和valueBufferLen描述的缓冲区中。
*
* @attention 无
*
* @param propsetOrEnumerator [IN]  属性枚举句柄
* @param name                [IN]  查询内容
* @param valueBuffer         [OUT] 接收内容buffer
* @param valueBufferLen      [OUT] 返回内容长度
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_ITEM_NOT_FOUND 找不到该属性，或者名称不是有效的UTF-8编码
* @retval #TEE_ERROR_BAD_FORMAT     属性值无法转换为标识
*
* @par 依赖:
* @li tee_property_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_GetPropertyAsString(TEE_PropSetHandle propsetOrEnumerator,
				   char *name, char *valueBuffer, size_t *valueBufferLen);

/**
* @ingroup TEE_PROPERTY_API
* @brief 请求Property，以bool形式返回
*
* @par 描述:
* TEE_GetPropertyAsBool函数检索属性集中的单个属性，并将其值转换为布尔值。 如果
* 属性不能被视为布尔值，则此函数必须返回TEE_ERROR_BAD_FORMAT。
*
* @attention 无
*
* @param propsetOrEnumerator [IN]  属性枚举句柄
* @param name                [IN]  查询内容
* @param value               [OUT] 接收内容空间
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_ITEM_NOT_FOUND 找不到该属性，或者名称不是有效的UTF-8编码
* @retval #TEE_ERROR_BAD_FORMAT     属性值无法转换为标识
*
* @par 依赖:
* @li tee_property_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_GetPropertyAsBool(TEE_PropSetHandle propsetOrEnumerator,
				 char *name, bool *value);

/**
* @ingroup TEE_PROPERTY_API
* @brief 请求Property，以32位整形形式返回
*
* @par 描述:
* TEE_GetPropertyAsU32函数检索属性集中的单个属性，并将其值转换为32位无符号整数。 
* 如果属性不能被视为32位无符号整数，则此函数必须返回TEE_ERROR_BAD_FORMAT。
*
* @attention 无
*
* @param propsetOrEnumerator [IN]  属性枚举句柄
* @param name                [IN]  查询内容
* @param value               [OUT] 接收内容空间
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_ITEM_NOT_FOUND 找不到该属性，或者名称不是有效的UTF-8编码
* @retval #TEE_ERROR_BAD_FORMAT     属性值无法转换为标识
*
* @par 依赖:
* @li tee_property_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_GetPropertyAsU32(TEE_PropSetHandle propsetOrEnumerator,
				char *name, uint32_t *value);

/**
* @ingroup TEE_PROPERTY_API
* @brief 请求Property，以二进制形式返回
*
* @par 描述:
* 函数TEE_GetPropertyAsBinaryBlock检索单个属性并将其值转换为二进制块。 如果
* 属性不能被视为二进制块，则此函数必须返回TEE_ERROR_BAD_FORMAT。
*
* @attention 无
*
* @param propsetOrEnumerator  [IN]  属性枚举句柄
* @param name                 [IN]  查询内容
* @param valueBuffer          [OUT] 接收内容buffer
* @param valueBufferLen       [OUT] 返回内容长度
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_ITEM_NOT_FOUND 找不到该属性，或者名称不是有效的UTF-8编码
* @retval #TEE_ERROR_BAD_FORMAT     属性值无法转换为标识
* @retval #TEE_ERROR_SHORT_BUFFER   输出buffer过小
*
* @par 依赖:
* @li tee_property_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_GetPropertyAsBinaryBlock(TEE_PropSetHandle propsetOrEnumerator,
					char *name, void *valueBuffer, size_t *valueBufferLen);

/**
* @ingroup TEE_PROPERTY_API
* @brief 请求Property，以UUID形式返回
*
* @par 描述:
* 函数TEE_GetPropertyAsUUID检索单个属性并将其值转换为UUID。 如果属性不能被视为UUID，
* 则此函数必须返回TEE_ERROR_BAD_FORMAT。
*
* @attention 无
*
* @param propsetOrEnumerator  [IN]  属性枚举句柄
* @param name                 [IN]  查询内容
* @param value                [OUT] 接收内容空间
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_ITEM_NOT_FOUND 找不到该属性，或者名称不是有效的UTF-8编码
* @retval #TEE_ERROR_BAD_FORMAT     属性值无法转换为标识
*
* @par 依赖:
* @li tee_property_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_GetPropertyAsUUID(TEE_PropSetHandle propsetOrEnumerator,
				 char *name, TEE_UUID *value);

/**
* @ingroup TEE_PROPERTY_API
* @brief 请求Property，以TEE_Identity形式返回
*
* @par 描述:
* 函数TEE_GetPropertyAsIdentity检索单个属性并将其值转换为TEE_Identity。
*
* @attention 无
*
* @param propsetOrEnumerator  [IN]  属性枚举句柄
* @param name                 [IN]  查询内容
* @param value                [OUT] 接收内容buffer
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_ITEM_NOT_FOUND 找不到该属性，或者名称不是有效的UTF-8编码
* @retval #TEE_ERROR_BAD_FORMAT     属性值无法转换为标识
*
* @par 依赖:
* @li tee_property_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_GetPropertyAsIdentity(TEE_PropSetHandle propsetOrEnumerator,
				     char *name, TEE_Identity *value);

/**
* @ingroup TEE_PROPERTY_API
* @brief 分配Property Enumerator
*
* @par 描述:
* 函数TEE_AllocatePropertyEnumerator分配属性枚举器对象。 一旦分配了属性枚举器的句
* 柄，就可以使用它来使用函数TEE_StartPropertyEnumerator枚举属性集中的属性。
*
* @attention 无
*
* @param enumerator [OUT] 枚举句柄
*
* @retval #TEE_SUCCESS             执行成功
* @retval #TEE_ERROR_OUT_OF_MEMORY 资源不足
*
* @par 依赖:
* @li tee_property_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_AllocatePropertyEnumerator(TEE_PropSetHandle *enumerator);

/**
* @ingroup TEE_PROPERTY_API
* @brief 释放Property Enumerator
*
* @par 描述:
* 函数TEE_FreePropertyEnumerator释放属性枚举器对象。
*
* @attention 无
*
* @param enumerator [IN] 句柄
*
* @par 依赖:
* @li tee_property_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
void TEE_FreePropertyEnumerator(TEE_PropSetHandle enumerator);

/**
* @ingroup TEE_PROPERTY_API
* @brief 开始Property枚举
*
* @par 描述:
* 函数TEE_StartPropertyEnumerator开始枚举枚举器中的属性。 将枚举器附加到属性集后：
* @li 可以使用TEE_GetPropertyAsXXX函数之一检索属性，将枚举器句柄作为属性集并将NULL作为名称传递。
* @li 函数TEE_GetPropertyName可用于检索枚举器中当前属性的名称。
* @li 函数TEE_GetNextProperty可用于将枚举推进到属性集中的下一个属性。
*
* @attention 无
*
* @param enumerator [IN] 枚举句柄
* @param propSet    [IN] 属性集
*
* @retval 无
*
* @par 依赖: 无
* @li tee_property_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
void TEE_StartPropertyEnumerator(TEE_PropSetHandle enumerator, TEE_PropSetHandle propSet);

/**
* @ingroup TEE_PROPERTY_API
* @brief 重置Property Enumerator
*
* @par 描述:
* 函数TEE_ResetPropertyEnumerator在执行后立即将Property枚举重置为初始状态。 
* 如果当前启动枚举，则将其放弃。
*
* @attention 无
*
* @param enumerator [IN] 句柄
*
* @retval 无
*
* @par 依赖:
* @li tee_property_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
void TEE_ResetPropertyEnumerator(TEE_PropSetHandle enumerator);

/**
* @ingroup TEE_PROPERTY_API
* @brief 请求Property名称
*
* @par 描述:
* 函数TEE_GetPropertyName获取枚举器中当前属性的名称。
*
* @attention 属性名称必须是不包含U + 0000代码点的Unicode字符串的有效UTF-8编码。
*
* @param enumerator    [IN]  句柄
* @param nameBuffer    [OUT] 名称buffer
* @param nameBufferLen [OUT] 返回大小
*
* @retval #TEE_SUCCESS               执行成功
* @retval #TEE_ERROR_ITEM_NOT_FOUND  枚举未开始或已至最后一项
* @retval #TEE_ERROR_SHORT_BUFFER    buffer过小
*
* @par 依赖:
* @li tee_property_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_GetPropertyName(TEE_PropSetHandle enumerator, void *nameBuffer, size_t *nameBufferLen);

/**
* @ingroup TEE_PROPERTY_API
* @brief 进行一次枚举
*
* @par 描述:
* 函数TEE_GetNextProperty将枚举进行到下一个属性。
*
* @attention 无
*
* @param enumerator [IN] 句柄
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_ITEM_NOT_FOUND 枚举未开始或已至最后一项
*
* @par 依赖:
* @li tee_property_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_GetNextProperty(TEE_PropSetHandle enumerator);

#endif
