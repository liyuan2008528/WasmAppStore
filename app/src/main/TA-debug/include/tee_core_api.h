/**
 * @file tee_core_api.h
 *
 * Copyright(C), 2008-2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 * 
 * 描述：安全世界TA与TA交互API  \n
 */

/**
 * @defgroup TEE_TA2TA_FUNC  TA与TA交互
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
 * @brief 会话结束，打印错误信息
 *
 * @par 描述:
 * 当TA出现无法继续运行下去的故障时将调用它，该函数会导致TA中止，所有资源将被收回
 * 函数执行时，CA会收到一个TEE_ERROR_TARGET_DEAD返回码
 * 系统将会显示相关错误信息并打印调用栈
 *
 * @attention 无
 *
 * @param destination [OUT] 由TA定义的错误码，可以在调用栈中打印出来
 *
 * @retval 无
 *
 * @par 依赖:
 * @li tee_core_api.h：该接口声明所在头文件
 * @see 无
 * @since V100R002C00
 */
void TEE_Panic(TEE_Result panicCode);
 /**
 * @ingroup  TEE_TA2TA_FUNC
 * @brief 打开会话
 *
 * @par 描述:
 * 为客户端应用或安全服务 与UUID为destination的安全服务建立一条链接，传递的数据包含在params里
 * 打开会话成功后，输出参数session是对该链接的一个描述；
 * 如果打开会话失败，输出参数returnOrigin为错误来源。
 *
 * @attention 无
 *
 * @param destination                [IN]     安全服务的UUID，一个安全服务拥有唯一的UUID
 * @param cancellationRequestTimeout [IN]     未使用参数，请勿使用
 * @param paramTypes                 [IN]     需要传递给目标TA的参数的类型
 * @param params[4]                  [IN]     需要传递给目标TA的参数集
 * @param session                    [OUT]    输出打开的TA对应session
 * @param returnOrigin               [IN/OUT] 错误来源，取值范围为#TEE_ReturnCodeOrigin
 *
 * @retval #TEE_SUCCESS              打开会话成功
 * @retval #TEE_ERROR_BAD_PARAMETERS 参数不正确，参数destination为空或session为空
 * @retval #TEE_ERROR_OUT_OF_MEMORY  系统可用资源不足
 * @retval #TEE_ERROR_ITEM_NOT_FOUND 请求的数据未找到
 * @retval 其它返回值参考 #TEEC_ReturnCode
 *
 * @par 依赖:
 * @li tee_core_api.h：该接口声明所在头文件
 * @see TEE_CloseTASession
 * @since V100R002C00
 */
TEE_Result TEE_OpenTASession(TEE_UUID *destination, uint32_t cancellationRequestTimeout,
			     uint32_t paramTypes, TEE_Param params[4],
			     TEE_TASessionHandle *session, uint32_t *returnOrigin);

/**
 * @ingroup  TEE_TA2TA_FUNC 
 * @brief 关闭会话
 *
 * @par 描述:
 * 关闭指定session会话TA，断开源安全服务与目标安全服务的链接
 *
 * @attention 无
 *
 * @param session [IN/OUT] 需要关闭TA对应session
 *
 * @retval 无
 *
 * @par 依赖:
 * @li tee_core_api.h：该接口声明所在头文件
 * @see TEE_OpenTASession
 * @since V100R002C00
 */
void TEE_CloseTASession(TEE_TASessionHandle session);

/**
 * @ingroup  TEE_TA2TA_FUNC
 * @brief 发送命令
 *
 * @par 描述:
 * 在指定的会话session里，由客户端应用向安全服务发送命令commandID，发送的数据为params里
 * 如果发送命令失败，输出参数returnOrigin为错误来源
 *
 * @attention 无
 *
 * @param session                    [IN/OUT] 指向已打开成功的会话
 * @param cancellationRequestTimeout [IN]     未使用参数，请勿使用
 * @param commandID                  [IN]     安全服务支持的命令ID，由安全服务定义
 * @param paramTypes                 [IN]     需要传递给目标TA的参数的类型
 * @param params[4]                  [IN]     需要传递给目标TA的参数集
 * @param returnOrigin               [IN/OUT] 错误来源，取值范围为#TEE_ReturnCodeOrigin
 *
 * @retval #TEE_SUCCESS              发送命令成功
 * @retval #TEE_ERROR_BAD_PARAMETERS 参数不正确，参数destination为空或session为空
 * @retval #TEE_ERROR_OUT_OF_MEMORY  系统可用资源不足
 * @retval #TEE_ERROR_ITEM_NOT_FOUND 请求的数据未找到
 * @retval 其它返回值参考 #TEEC_ReturnCode
 *
 * @par 依赖:
 * @li tee_client_api.h：该接口声明所在头文件
 * @see 无
 * @since V100R002C00
 */
TEE_Result TEE_InvokeTACommand(TEE_TASessionHandle session, uint32_t cancellationRequestTimeout,
			       uint32_t commandID, uint32_t paramTypes,
			       TEE_Param params[4], uint32_t *returnOrigin);

/**
 * @ingroup  TEE_TA2TA_FUNC 
 * @brief 取消标记当前任务的取消状态
 *
 * @par 描述:
 * 无
 *
 * @attention 无
 *
 * @param 无
 *
 * @retval #true  调用此函数前已经标记了取消
 * @retval #false 其他情况
 *
 * @par 依赖:
 * @li tee_core_api.h：该接口声明所在头文件
 * @see 无
 * @since V100R002C00
 */
bool TEE_UnmaskCancellation(void);

/**
 * @ingroup  TEE_TA2TA_FUNC 
 * @brief 标记当前任务的取消状态 
 *
 * @par 描述:
 * 无
 * 
 * @attention 无
 *
 * @param 无
 *
 * @retval #true  调用此函数前已经标记了取消
 * @retval #false 其他情况
 *
 * @par 依赖:
 * @li tee_core_api.h：该接口声明所在头文件
 * @see 
 * @since V100R002C00
 */
bool TEE_MaskCancellation(void);

/**
 * @ingroup  TEE_TA2TA_FUNC 
 * @brief 获取session类型
 *
 * @par 描述:获取当前session的类型
 *
 * @attention 无
 *
 * @param 无
 *
 * @retval 当前参数类型
 *
 * @par 依赖:
 * @li tee_core_api.h：该接口声明所在头文件
 * @see 
 * @since V100R002C00
 */
uint32_t TEE_GetSessionType(void);
#endif
