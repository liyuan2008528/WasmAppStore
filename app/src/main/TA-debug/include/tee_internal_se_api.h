/**
* @file tee_internal_se_api.h
*
* Copyright(C), 2008-2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.\n
*
* ��������ȫ����SE���API\n
*/

/**
* @defgroup TEE_SE_API  ��ȫSE
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
* SE��ؾ������
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
* SE Reader����
*/
typedef struct __TEE_SEReaderProperties {
	bool sePresent;            // true if an SE is present in the reader
	bool teeOnly;              // true if this reader is only accessible via the TEE
	bool selectResponseEnable; // true if the response to a SELECT is available in the TEE
} TEE_SEReaderProperties;

/**
* @ingroup  TEE_SE_API
* Applet AID����
*/
typedef struct __TEE_SEAID {
	uint8_t *buffer;    // the value of the applet��s AID
	size_t bufferLen;   // length of the applet��s AID
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
* @brief ��ʼ��SE
*
* @par ����:
* ��ʼ��SE���������ݽṹ����
*
* @attention ��
*
* @param ��
*
* @retval ��
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
void init_tee_se_api(void);

/**
* @ingroup  TEE_SE_API
* @brief �򿪷�����
*
* @par ����:
* TEE_SEServiceOpen����Ϊ�����ӷ��������þ�����������ӵ�TEE���õ�����SE��
*
* @attention ��
*
* @param seServiceHandle [OUT] ������
*
* @retval #TEE_SUCCESS               ִ�гɹ�
* @retval #TEE_ERROR_ACCESS_CONFLICT TA�Ѿ���һ�����
* @retval #TEE_ERROR_OUT_OF_MEMORY   �ڴ治��
* @retval #TEE_ERROR_BAD_PARAMETERS  ��������
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_SEServiceOpen(TEE_SEServiceHandle *seServiceHandle);

/**
* @ingroup  TEE_SE_API
* @brief �رշ�����
*
* @par ����:
* TEE_SEServiceClose�����ͷŴ�seService���������SE��Դ��
*
* @attention ��
*
* @param seServiceHandle [IN] ������
*
* @retval ��
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
void TEE_SEServiceClose(TEE_SEServiceHandle seServiceHandle);

/**
* @ingroup  TEE_SE_API
* @brief ��ÿ��õ�SE Reader���
*
* @par ����:
* TEE_SEServiceGetReaders�������ؿ��õ�SE Reader����б�
* ���ص��б��б���û���ظ��Ķ���
*
* @attention ��
*
* @param seServiceHandle       [IN]    ������
* @param seReaderHandleList    [OUT]   Reader���List
* @param seReaderHandleListLen [INOUT] ���ش�С
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_ITEM_NOT_FOUND û�п�����
* @retval #TEE_ERROR_OUT_OF_MEMORY  �ڴ治��
* @retval #TEE_ERROR_SHORT_BUFFER   buffer��С
* @retval #TEE_ERROR_BAD_PARAMETERS ��������
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_SEServiceGetReaders(TEE_SEServiceHandle seServiceHandle,
				   TEE_SEReaderHandle *seReaderHandleList,
				   size_t *seReaderHandleListLen);

/**
* @ingroup  TEE_SE_API
* @brief ��ȡReader������
*
* @par ����:
* TEE_SEReaderGetProperties��������Reader�����ԡ� ��Щ���԰�����
* ����Ϣ����ȡ�����Ƿ����SE��SE�Ƿ�ֱ�����ӵ�TEE���Լ��Ƿ���TEE��
* ���Ի�ö�SELECT����Ӧ��
*
* @attention ��
*
* @param seReaderHandle   [IN]  Reader���
* @param readerProperties [OUT] Reader������
*
* @retval ��
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
void TEE_SEReaderGetProperties(TEE_SEReaderHandle seReaderHandle,
			       TEE_SEReaderProperties *readerProperties);

/**
* @ingroup  TEE_SE_API
* @brief ��ȡReader������
*
* @par ����:
* TEE_SEReaderGetName�������ش�Reader���Ѻ����ơ�
*
* @attention ��
*
* @param seReaderHandle [IN]  Reader���
* @param readerName     [OUT] Reader����
* @param readerNameLen  [OUT] ���ش�С
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_SHORT_BUFFER   buffer��С
* @retval #TEE_ERROR_ITEM_NOT_FOUND �����Ч
* @retval #TEE_ERROR_SHORT_BUFFER   buffer̫С
* @retval #TEE_ERROR_GENERIC        ͨ�ô���
* @retval #TEE_ERROR_BAD_PARAMETERS ��������
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_SEReaderGetName(TEE_SEReaderHandle seReaderHandle,
			       char *readerName, size_t *readerNameLen);

/**
* @ingroup  TEE_SE_API
* @brief ��һ��Reader��Session
*
* @par ����:
* TEE_SEReaderOpenSession�������ӵ���Reader�е�SE��
*
* @attention ��
*
* @param seReaderHandle  [IN]  Reader���
* @param seSessionHandle [OUT] Session���
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_COMMUNICATION  ͨѶ����
* @retval #TEE_ERROR_ITEM_NOT_FOUND �����Ч
* @retval #TEE_ERROR_OUT_OF_MEMORY  �ڴ治��
* @retval #TEE_ERROR_BAD_PARAMETERS ��������
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_SEReaderOpenSession(TEE_SEReaderHandle seReaderHandle,
				   TEE_SESessionHandle *seSessionHandle);

/**
* @ingroup  TEE_SE_API
* @brief �ر�Reader������Session
*
* @par ����:
* TEE_SEReaderCloseSessions�����ر��ڴ�Reader�ϴ򿪵�����Session�� 
* ��ЩSession������Channel�����رա�
*
* @attention ��
*
* @param seReaderHandle [IN] Reader���
*
* @retval ��
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
void TEE_SEReaderCloseSessions(TEE_SEReaderHandle seReaderHandle);

/**
* @ingroup  TEE_SE_API
* @brief ��ȡ�ش�����
*
* @par ����:
* TEE_SESessionGetATR�������ش�SE��ATR��
*
* @attention ��
*
* @param seSessionHandle [IN] Session���
* @param atr             [OUT] ATR buffer
* @param atrLen          [OUT] ���ش�С
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_COMMUNICATION  ͨѶ����
* @retval #TEE_ERROR_SHORT_BUFFER   buffer��С
* @retval #TEE_ERROR_GENERIC        ͨ�ô���
* @retval #TEE_ERROR_BAD_PARAMETERS ��������
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_SESessionGetATR(TEE_SESessionHandle seSessionHandle,
			       void *atr, size_t *atrLen);

/**
* @ingroup  TEE_SE_API
* @brief �ж�Session�Ƿ��Ѿ��ر�
*
* @par ���� ��
* �����Session�رգ���TEE_SESessionIsClosed�������ɹ����ء�
*
* @attention ��
*
* @param seSessionHandle [IN] Session���
*
* @retval #TEE_SUCCESS             Session�Ѿ��ر�
* @retval #TEE_ERROR_COMMUNICATION ͨѶ����
* @retval #TEE_ERROR_GENERIC       ͨ�ô���
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_SESessionIsClosed(TEE_SESessionHandle seSessionHandle);

/**
* @ingroup  TEE_SE_API
* @brief �ر�Session������Channel�����ҹر�Session
*
* @par ����:
* TEE_SESessionClose�����ر��ڴ�Session��Session�����ϴ򿪵�����Channel��
*
* @attention ��
*
* @param seSessionHandle [IN] Session���
*
* @retval ��
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
void TEE_SESessionClose(TEE_SESessionHandle seSessionHandle);

/**
* @ingroup  TEE_SE_API
* @brief �ر�Session������Channel
*
* @par ����:
* TEE_SESessionCloseChannels�����ر��ڴ˻Ự�д򿪵�����ͨ����
* �Ự����δ�رա�
*
* @attention ��
*
* @param seSessionHandle [IN] Session���
*
* @retval ��
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
void TEE_SESessionCloseChannels(TEE_SESessionHandle seSessionHandle);

/**
* @ingroup  TEE_SE_API
* @brief �򿪻���Channel
*
* @par ����:
* TEE_SESessionOpenBasicChannel������ö�ISO/IEC 7816-4([ISO 7816-4])
* (���Ϊ0��ͨ��)�ж���Ļ���ͨ���ķ��ʡ�
*
* @attention ��
*
* @param seSessionHandle [IN]  Session���
* @param seAID           [IN]  ��Channel��AID
* @param seChannelHandle [OUT] Channel���
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_COMMUNICATION  ͨѶ����
* @retval #TEE_ERROR_BAD_STATE      Session�Ѿ��ر�
* @retval #TEE_ERROR_BAD_PARAMETERS ��������
* @retval #TEE_ERROR_NOT_SUPPORTED  SE����AID������
* @retval #TEE_ERROR_SECURITY       �����ܷ���AID����SE
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_SESessionOpenBasicChannel(TEE_SESessionHandle seSessionHandle,
		TEE_SEAID *seAID, TEE_SEChannelHandle *seChannelHandle);

/**
* @ingroup  TEE_SE_API
* @brief ��SE���߼�Channel
*
* @par ����:
* TEE_SESessionOpenLogicalChannel����ʹ��SE���߼�ͨ����ѡ���ɸ���AID��ʾ��Ӧ�ó���
*
* @attention ��
*
* @param seSessionHandle [IN]  Session���
* @param seAID           [IN]  ����Channel��AID
* @param seChannelHandle [OUT] Channel���
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_COMMUNICATION  ͨѶ����
* @retval #TEE_ERROR_BAD_STATE      Session�Ѿ��ر�
* @retval #TEE_ERROR_NOT_SUPPORTED  SE����AID�����ã�һ���߼�Channel�Ѿ�ռ��
* @retval #TEE_ERROR_SECURITY       �����ܷ���AID����SE
* @retval #TEE_ERROR_BAD_PARAMETERS ��������
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_SESessionOpenLogicalChannel(TEE_SESessionHandle seSessionHandle,
		TEE_SEAID *seAID, TEE_SEChannelHandle *seChannelHandle);

/**
* @ingroup  TEE_SE_API
* @brief �ر�SE��Channel
*
* @par ����:
* TEE_SEChannelClose��������ͨ���رյ�SE�� �����ͨ���ر�ʱ���øú������򽫺��Ժ������á�
* �ڹر�ͨ��֮ǰ��TEE_SEChannelClose����Ӧ�ȴ��κι����TEE_SEChannelTransmit����ɡ�
*
* @attention ��
*
* @param seChannelHandle [IN] Channel���
*
* @retval ��
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
void TEE_SEChannelClose(TEE_SEChannelHandle seChannelHandle);

/**
* @ingroup  TEE_SE_API
* @brief ��Channel��ִ����һ��Applet��ѡ��
*
* @par ����:
* TEE_SEChannelSelectNext����ִ�д�ͨ������һ��Applet��ѡ�� 
* �豸Ӧ�ó������ʹ�ô˷���������ƥ����ͬ����AID������Applet��
* 
* @attention ��
*
* @param seChannelHandle  [IN] Channel���
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_ITEM_NOT_FOUND ��ö�������һ��Applet
* @retval #TEE_ERROR_NOT_SUPPORTED  �ú�����֧��
* @retval #TEE_ERROR_COMMUNICATION  ͨѶ����
* @retval #TEE_ERROR_BAD_STATE      Session�ѹر�
* @retval #TEE_ERROR_BAD_PARAMETERS ��������
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_SEChannelSelectNext(TEE_SEChannelHandle seChannelHandle);

/**
* @ingroup  TEE_SE_API
* @brief ��ȡ��SELECT����������صĻظ����ݺ�״̬��
*
* @par ����:
* TEE_SEChannelGetSelectResponse����������Ӧ���ݺ����ڴ�ͨ����SELECT���������״̬�֡�
*
* @attention ��
*
* @param seChannelHandle   [IN]    Channel���
* @param response          [OUT]   �ظ�buffer
* @param responseLen       [OUT]   �ظ���С
*
* @retval #TEE_SUCCESS              ִ�гɹ�
* @retval #TEE_ERROR_COMMUNICATION  ͨѶ����
* @retval #TEE_ERROR_BAD_STATE      Session�Ѿ��ر�
* @retval #TEE_ERROR_NO_DATA        û������
* @retval #TEE_ERROR_BAD_PARAMETERS ��������
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_SEChannelGetSelectResponse(TEE_SEChannelHandle seChannelHandle,
		void *response, size_t *responseLen);

/**
* @ingroup  TEE_SE_API
* @brief ����һ��APDU���SE
*
* @par ����:
* TEE_SEChannelTransmit���ܽ�APDU�������[ISO 7816-4]�����͵�SE�� �ײ�����˴����
* APDU����ľ����ܶ��TPDU�� ���䲿����Ӧ�ó������ǲ��ɼ��ġ� ���ɵ���Ӧ��APDU����Ӧ��
*
* @attention ��
*
* @param seChannelHandle   [IN]    Channel���
* @param command           [IN]    ��������buffer
* @param commandLen        [IN]    ����buffer��С
* @param response          [OUT]   ���ջظ�buffer
* @param responseLen       [OUT]   �ظ���С
*
* @retval #TEE_SUCCESS                 ִ�гɹ�
* @retval #TEE_ERROR_COMMUNICATION SE  ͨѶ����
* @retval #TEE_ERROR_BAD_STATE		   Session�Ѿ��ر�
* @retval #TEE_ERROR_BAD_PARAMETERS    ��������
* @retval #TEE_ERROR_SECURITY          �������
*
* @par ����:
* @li tee_internal_se_api.h���ýӿ��������ڵ�ͷ�ļ�
* @see ��
* @since V100R007C00
*/
TEE_Result TEE_SEChannelTransmit(TEE_SEChannelHandle seChannelHandle,
				 void *command, size_t commandLen,
				 void *response, size_t *responseLen);

#endif
