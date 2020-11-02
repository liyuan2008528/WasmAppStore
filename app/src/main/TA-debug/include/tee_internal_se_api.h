/**
* @file tee_internal_se_api.h
*
* Copyright(C), 2008-2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.\n
*
* 描述：安全世界SE相关API\n
*/

/**
* @defgroup TEE_SE_API  安全SE
* @ingroup TEE_API
*/

#ifndef __TEE_INTERNAL_SE_API_H
#define __TEE_INTERNAL_SE_API_H

#include "tee_internal_api.h"

typedef struct _list_object {
	struct _list_object *pstPrev;
	struct _list_object *pstNext;
} list_object;

struct __TEE_SEServiceHandle;
struct __TEE_SEReaderHandle;
struct __TEE_SESessionHandle;
struct __TEE_SEChannelHandle;

/**
* @ingroup  TEE_SE_API
* SE相关句柄定义
*/
typedef struct __TEE_SEServiceHandle *TEE_SEServiceHandle;
typedef struct __TEE_SEReaderHandle *TEE_SEReaderHandle;
typedef struct __TEE_SESessionHandle *TEE_SESessionHandle;
typedef struct __TEE_SEChannelHandle *TEE_SEChannelHandle;

#define ATR_LEN_MAX 32
#define AID_LEN_MIN 5
#define AID_LEN_MAX 16

#define SE_READER_COUNT 1

#define SE_LOGIC_CHANNEL_MAX 8 // 0 is for basic channel

/**
* @ingroup  TEE_SE_API
* SE Reader属性
*/
typedef struct __TEE_SEReaderProperties {
	bool sePresent;            // true if an SE is present in the reader
	bool teeOnly;              // true if this reader is only accessible via the TEE
	bool selectResponseEnable; // true if the response to a SELECT is available in the TEE
} TEE_SEReaderProperties;

/**
* @ingroup  TEE_SE_API
* Applet AID定义
*/
typedef struct __TEE_SEAID {
	uint8_t *buffer;    // the value of the applet’s AID
	size_t bufferLen;   // length of the applet’s AID
} TEE_SEAID;

struct __TEE_SEServiceHandle {
	TEE_MUTEX_HANDLE se_mutex;
};

struct __TEE_SEReaderHandle {
	unsigned int id;
	TEE_SEReaderProperties property;
	bool basic_channel_locked;
	unsigned short session_count;
	unsigned short atr_len;
	char atr[ATR_LEN_MAX];
	const char *name;
	list_object session_head;
	uint8_t logic_channel_bm[(SE_LOGIC_CHANNEL_MAX+7)/8];
};

struct __TEE_SESessionHandle {
	char state;  // 0 - closed, 1 - open, -1 - invalid
	unsigned char channel_count;
	short reserved;
	TEE_SEReaderHandle reader;
	list_object list;
	list_object channel_head;
};

struct __TEE_SEChannelHandle {
	TEE_SEAID se_aid;
	bool basic_channel;
	char logic_channel;
	unsigned short resp_len;
	char *resp_buffer;
	TEE_SESessionHandle session;
	list_object list;
};

/**
* @ingroup  TEE_SE_API
* @brief 初始化SE
*
* @par 描述:
* 初始化SE和所需数据结构、锁
*
* @attention 无
*
* @param 无
*
* @retval 无
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
void init_tee_se_api(void);

/**
* @ingroup  TEE_SE_API
* @brief 打开服务句柄
*
* @par 描述:
* TEE_SEServiceOpen函数为新连接分配句柄，该句柄可用于连接到TEE可用的所有SE。
*
* @attention 无
*
* @param seServiceHandle [OUT] 服务句柄
*
* @retval #TEE_SUCCESS               执行成功
* @retval #TEE_ERROR_ACCESS_CONFLICT TA已经打开一个句柄
* @retval #TEE_ERROR_OUT_OF_MEMORY   内存不足
* @retval #TEE_ERROR_BAD_PARAMETERS  参数错误
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_SEServiceOpen(TEE_SEServiceHandle *seServiceHandle);

/**
* @ingroup  TEE_SE_API
* @brief 关闭服务句柄
*
* @par 描述:
* TEE_SEServiceClose函数释放此seService分配的所有SE资源。
*
* @attention 无
*
* @param seServiceHandle [IN] 服务句柄
*
* @retval 无
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
void TEE_SEServiceClose(TEE_SEServiceHandle seServiceHandle);

/**
* @ingroup  TEE_SE_API
* @brief 获得可用的SE Reader句柄
*
* @par 描述:
* TEE_SEServiceGetReaders函数返回可用的SE Reader句柄列表。
* 返回的列表中必须没有重复的对象。
*
* @attention 无
*
* @param seServiceHandle       [IN]    服务句柄
* @param seReaderHandleList    [OUT]   Reader句柄List
* @param seReaderHandleListLen [INOUT] 返回大小
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_ITEM_NOT_FOUND 没有可用项
* @retval #TEE_ERROR_OUT_OF_MEMORY  内存不足
* @retval #TEE_ERROR_SHORT_BUFFER   buffer过小
* @retval #TEE_ERROR_BAD_PARAMETERS 参数错误
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_SEServiceGetReaders(TEE_SEServiceHandle seServiceHandle,
				   TEE_SEReaderHandle *seReaderHandleList,
				   size_t *seReaderHandleListLen);

/**
* @ingroup  TEE_SE_API
* @brief 获取Reader的属性
*
* @par 描述:
* TEE_SEReaderGetProperties函数返回Reader的属性。 这些属性包括以
* 下信息：读取器中是否存在SE，SE是否直接连接到TEE，以及是否在TEE中
* 可以获得对SELECT的响应。
*
* @attention 无
*
* @param seReaderHandle   [IN]  Reader句柄
* @param readerProperties [OUT] Reader的属性
*
* @retval 无
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
void TEE_SEReaderGetProperties(TEE_SEReaderHandle seReaderHandle,
			       TEE_SEReaderProperties *readerProperties);

/**
* @ingroup  TEE_SE_API
* @brief 获取Reader的名称
*
* @par 描述:
* TEE_SEReaderGetName函数返回此Reader的友好名称。
*
* @attention 无
*
* @param seReaderHandle [IN]  Reader句柄
* @param readerName     [OUT] Reader名称
* @param readerNameLen  [OUT] 返回大小
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_SHORT_BUFFER   buffer过小
* @retval #TEE_ERROR_ITEM_NOT_FOUND 句柄无效
* @retval #TEE_ERROR_SHORT_BUFFER   buffer太小
* @retval #TEE_ERROR_GENERIC        通用错误
* @retval #TEE_ERROR_BAD_PARAMETERS 参数错误
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_SEReaderGetName(TEE_SEReaderHandle seReaderHandle,
			       char *readerName, size_t *readerNameLen);

/**
* @ingroup  TEE_SE_API
* @brief 打开一个Reader的Session
*
* @par 描述:
* TEE_SEReaderOpenSession函数连接到此Reader中的SE。
*
* @attention 无
*
* @param seReaderHandle  [IN]  Reader句柄
* @param seSessionHandle [OUT] Session句柄
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_COMMUNICATION  通讯错误
* @retval #TEE_ERROR_ITEM_NOT_FOUND 句柄无效
* @retval #TEE_ERROR_OUT_OF_MEMORY  内存不足
* @retval #TEE_ERROR_BAD_PARAMETERS 参数错误
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_SEReaderOpenSession(TEE_SEReaderHandle seReaderHandle,
				   TEE_SESessionHandle *seSessionHandle);

/**
* @ingroup  TEE_SE_API
* @brief 关闭Reader的所有Session
*
* @par 描述:
* TEE_SEReaderCloseSessions函数关闭在此Reader上打开的所有Session。 
* 这些Session的所有Channel都将关闭。
*
* @attention 无
*
* @param seReaderHandle [IN] Reader句柄
*
* @retval 无
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
void TEE_SEReaderCloseSessions(TEE_SEReaderHandle seReaderHandle);

/**
* @ingroup  TEE_SE_API
* @brief 获取回答重置
*
* @par 描述:
* TEE_SESessionGetATR函数返回此SE的ATR。
*
* @attention 无
*
* @param seSessionHandle [IN] Session句柄
* @param atr             [OUT] ATR buffer
* @param atrLen          [OUT] 返回大小
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_COMMUNICATION  通讯错误
* @retval #TEE_ERROR_SHORT_BUFFER   buffer过小
* @retval #TEE_ERROR_GENERIC        通用错误
* @retval #TEE_ERROR_BAD_PARAMETERS 参数错误
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_SESessionGetATR(TEE_SESessionHandle seSessionHandle,
			       void *atr, size_t *atrLen);

/**
* @ingroup  TEE_SE_API
* @brief 判断Session是否已经关闭
*
* @par 描述 ：
* 如果此Session关闭，则TEE_SESessionIsClosed函数将成功返回。
*
* @attention 无
*
* @param seSessionHandle [IN] Session句柄
*
* @retval #TEE_SUCCESS             Session已经关闭
* @retval #TEE_ERROR_COMMUNICATION 通讯错误
* @retval #TEE_ERROR_GENERIC       通用错误
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_SESessionIsClosed(TEE_SESessionHandle seSessionHandle);

/**
* @ingroup  TEE_SE_API
* @brief 关闭Session的所有Channel，并且关闭Session
*
* @par 描述:
* TEE_SESessionClose函数关闭在此Session和Session本身上打开的所有Channel。
*
* @attention 无
*
* @param seSessionHandle [IN] Session句柄
*
* @retval 无
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
void TEE_SESessionClose(TEE_SESessionHandle seSessionHandle);

/**
* @ingroup  TEE_SE_API
* @brief 关闭Session的所有Channel
*
* @par 描述:
* TEE_SESessionCloseChannels函数关闭在此会话中打开的所有通道。
* 会话本身未关闭。
*
* @attention 无
*
* @param seSessionHandle [IN] Session句柄
*
* @retval 无
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
void TEE_SESessionCloseChannels(TEE_SESessionHandle seSessionHandle);

/**
* @ingroup  TEE_SE_API
* @brief 打开基本Channel
*
* @par 描述:
* TEE_SESessionOpenBasicChannel函数获得对ISO/IEC 7816-4([ISO 7816-4])
* (编号为0的通道)中定义的基本通道的访问。
*
* @attention 无
*
* @param seSessionHandle [IN]  Session句柄
* @param seAID           [IN]  打开Channel的AID
* @param seChannelHandle [OUT] Channel句柄
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_COMMUNICATION  通讯错误
* @retval #TEE_ERROR_BAD_STATE      Session已经关闭
* @retval #TEE_ERROR_BAD_PARAMETERS 参数错误
* @retval #TEE_ERROR_NOT_SUPPORTED  SE或者AID不可用
* @retval #TEE_ERROR_SECURITY       程序不能访问AID或者SE
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_SESessionOpenBasicChannel(TEE_SESessionHandle seSessionHandle,
		TEE_SEAID *seAID, TEE_SEChannelHandle *seChannelHandle);

/**
* @ingroup  TEE_SE_API
* @brief 打开SE的逻辑Channel
*
* @par 描述:
* TEE_SESessionOpenLogicalChannel函数使用SE打开逻辑通道，选择由给定AID表示的应用程序。
*
* @attention 无
*
* @param seSessionHandle [IN]  Session句柄
* @param seAID           [IN]  打开了Channel的AID
* @param seChannelHandle [OUT] Channel句柄
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_COMMUNICATION  通讯错误
* @retval #TEE_ERROR_BAD_STATE      Session已经关闭
* @retval #TEE_ERROR_NOT_SUPPORTED  SE或者AID不可用，一个逻辑Channel已经占用
* @retval #TEE_ERROR_SECURITY       程序不能访问AID或者SE
* @retval #TEE_ERROR_BAD_PARAMETERS 参数错误
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_SESessionOpenLogicalChannel(TEE_SESessionHandle seSessionHandle,
		TEE_SEAID *seAID, TEE_SEChannelHandle *seChannelHandle);

/**
* @ingroup  TEE_SE_API
* @brief 关闭SE的Channel
*
* @par 描述:
* TEE_SEChannelClose函数将此通道关闭到SE。 如果在通道关闭时调用该函数，则将忽略函数调用。
* 在关闭通道之前，TEE_SEChannelClose函数应等待任何挂起的TEE_SEChannelTransmit的完成。
*
* @attention 无
*
* @param seChannelHandle [IN] Channel句柄
*
* @retval 无
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
void TEE_SEChannelClose(TEE_SEChannelHandle seChannelHandle);

/**
* @ingroup  TEE_SE_API
* @brief 在Channel上执行下一个Applet的选择
*
* @par 描述:
* TEE_SEChannelSelectNext函数执行此通道上下一个Applet的选择。 
* 设备应用程序可以使用此方法来迭代匹配相同部分AID的所有Applet。
* 
* @attention 无
*
* @param seChannelHandle  [IN] Channel句柄
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_ITEM_NOT_FOUND 已枚举至最后一个Applet
* @retval #TEE_ERROR_NOT_SUPPORTED  该函数不支持
* @retval #TEE_ERROR_COMMUNICATION  通讯错误
* @retval #TEE_ERROR_BAD_STATE      Session已关闭
* @retval #TEE_ERROR_BAD_PARAMETERS 参数错误
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_SEChannelSelectNext(TEE_SEChannelHandle seChannelHandle);

/**
* @ingroup  TEE_SE_API
* @brief 获取由SELECT命令产生返回的回复数据和状态字
*
* @par 描述:
* TEE_SEChannelGetSelectResponse函数返回响应数据和用于打开通道的SELECT命令产生的状态字。
*
* @attention 无
*
* @param seChannelHandle   [IN]    Channel句柄
* @param response          [OUT]   回复buffer
* @param responseLen       [OUT]   回复大小
*
* @retval #TEE_SUCCESS              执行成功
* @retval #TEE_ERROR_COMMUNICATION  通讯错误
* @retval #TEE_ERROR_BAD_STATE      Session已经关闭
* @retval #TEE_ERROR_NO_DATA        没有数据
* @retval #TEE_ERROR_BAD_PARAMETERS 参数错误
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_SEChannelGetSelectResponse(TEE_SEChannelHandle seChannelHandle,
		void *response, size_t *responseLen);

/**
* @ingroup  TEE_SE_API
* @brief 发送一个APDU命令到SE
*
* @par 描述:
* TEE_SEChannelTransmit功能将APDU命令（根据[ISO 7816-4]）发送到SE。 底层产生了传输该
* APDU所需的尽可能多的TPDU。 传输部分在应用程序中是不可见的。 生成的响应是APDU的响应。
*
* @attention 无
*
* @param seChannelHandle   [IN]    Channel句柄
* @param command           [IN]    发送命令buffer
* @param commandLen        [IN]    命令buffer大小
* @param response          [OUT]   接收回复buffer
* @param responseLen       [OUT]   回复大小
*
* @retval #TEE_SUCCESS                 执行成功
* @retval #TEE_ERROR_COMMUNICATION SE  通讯错误
* @retval #TEE_ERROR_BAD_STATE		   Session已经关闭
* @retval #TEE_ERROR_BAD_PARAMETERS    参数错误
* @retval #TEE_ERROR_SECURITY          命令被过滤
*
* @par 依赖:
* @li tee_internal_se_api.h：该接口声明所在的头文件
* @see 无
* @since V100R007C00
*/
TEE_Result TEE_SEChannelTransmit(TEE_SEChannelHandle seChannelHandle,
				 void *command, size_t commandLen,
				 void *response, size_t *responseLen);

#endif
