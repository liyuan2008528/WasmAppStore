/**
* @file tee_tui_api.h
*
* Copyright(C), 2008-2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
*
* 描述：安全显示相关API
*/

/**
* @defgroup  TEE_TUI_API  安全显示
* @ingroup TEE_API
*/


#ifndef __TEE_TUI_API_H__
#define __TEE_TUI_API_H__
#include "tui_global.h"

/* -------------------------------------------- */
#define UNSET  0
#define UNMEASURED  (-654321)
#define INVALID_VAL_PRINT    "invalid"
#define MAX_FILENAME_LEN     1024
#define TEE_STORAGE_PRIVATE 0x00000001  //need change to 1

#define DEFA_SCRN_WIDTH  320
#define DEFA_SCRN_HEIGHT 480


#define DEFAULT_SCREENLABEL_TOP      10
#define DEFAULT_SCREENLABEL_LEFT     10
#define DEFAULT_SCREENLABEL_WIDTH    200
#define DEFAULT_SCREENLABEL_HEIGHT   80
#define DEFAULT_SCREENLABEL_IMAGE    "/usr/share/app-install/icons/agave.png"
#define DEFAULT_ENTRY_LABEL_WIDTH    750
#define DEFAULT_ENTRY_LABEL_HEIGHT   96
#define DEFAULT_BUTTON_WIDTH         300
#define DEFAULT_BUTTON_HEIGHT        150

#define DEFAULT_MARGIN               1
#define DEFAULT_MARGIN_STR          "1"
#define DEFAULT_PADDING              2
#define DEFAULT_PADDING_STR         "2"
#define DEFAULT_BG                  (0x00202020)
#define DEFAULT_BG_STR              "0x00202020"
#define DEFAULT_FG                  (0x00A2A2A2)
#define DEFAULT_FG_STR              "0x00A2A2A2"
#define INVALID_COORD               (0x9FFFFFFF)
#define INVALID_COORD_DEF_STR       "0x9FFFFFFF"

#define DEFAULT_UI_TEXT_ROTATE       0
#define DEFAULT_UI_TEXT_ROTATE_STR  "0"
#define DEFAULT_UI_FONT_SIZE         12  /* not specified in GP */
#define DEFAULT_UI_FONT_SIZE_STR    "12"
#define DEFAULT_UI_FONT_SPACING      2
#define DEFAULT_UI_FONT_SPACING_STR "2"

#define DEFAULT_TEXT_MODE            1    /* TEE_TUI_CLEAR_MODE */
#define DEFAULT_INPUT_TYPE           1    /* TEE_TUI_ALPHANUMERICAL */
#define DELAY_BEFORE_HIDDEN          300  /* milliseconds */
#define NO_LIMIT                     (-1)
#define NO_CARET                     (-1)
#define PASSWD_CHAR                  ('*')

#define DRIFT_DOWN                   3   /* for button: pressed */
#define DRIFT_UP                     1   /* for button: released */
#define TEXT_RECT_SINK               2   /* do not draw */

#define EDITBOX_SPACE				5 //gap + drift + sink

#define INVALID_KEY                 (-3)
#define INVALID_KEY_STR             "-3"
#define INVALID_KEY_VAL             (-4)
#define INVALID_KEY_VAL_STR         "-4"
#define INVALID_IM_INDEX           (-14)
#define INVALID_IM_INDEX_STR       "-14"

#define LOWERCASE                       0
#define UPPERCASE                       1
#define DEFAULT_LETTER_CASE             LOWERCASE
#define SPECIAL_KEY_VAL__BACKSPACE      (0x08)
#define SPECIAL_KEY_VAL__BACKSPACE_STR  "BackSpace"
#define SPECIAL_KEY_VAL__LINEFEED       (0x0A)
#define SPECIAL_KEY_VAL__LINEFEED_STR   "LineFeed"
#define SPECIAL_KEY_VAL__ENTER          (0x0D)
#define SPECIAL_KEY_VAL__ENTER_STR      "Enter"
#define SPECIAL_KEY_VAL__DEL            (0xFF)
#define SPECIAL_KEY_VAL__DEL_STR        "Del"
#define SPECIAL_KEY_VAL__CAPS_LOCK      (-101)
#define SPECIAL_KEY_VAL__CAPS_LOCK_STR  "CAPS_LOCK"
#define SPECIAL_KEY_VAL__SHIFT          (-102)
#define SPECIAL_KEY_VAL__SHIFT_STR      "SHIFT"
#define SPECIAL_KEY_VAL__HIDE_IM        (-103)
#define SPECIAL_KEY_VAL__HIDE_IM_STR    "HIDE_IM"
#define SPECIAL_KEY_VAL_TERPER_LOCK    (-104)
#define SPECIAL_KEY_VAL__BLANK          (0x20)



#define DEFAULT_MAX_ENTRY_FIELDS          3   /* account, passwd */
#define DEFAULT_MAX_INPUT_FIELD_LEN       20  /* in chars */
#define DEFAULT_MAX_INPUT_FIELD_LEN_STR  "20"
#define DEFAULT_BUTTON_TEXT_LEN    20

/* refer to section 3.10.4 "Minimum Text Area for Screen Lables": */
#define MIN_LABEL_HEIGHT_IN_CHARS    4  /* lines */
#define MIN_LABEL_WIDTH_IN_CHARS     25 /* chars */

#define DEFAULT_SECURITY_INDICATOR_WIDTH     50
#define DEFAULT_SECURITY_INDICATOR_HEIGHT    50
#define DEFAULT_SECURITY_INDICATOR_BG        (0x00FF1212)
#define DEFAULT_SECURITY_INDICATOR_FG        (0x0012FF12)
#define DEFAULT_SECURITY_INDICATOR_IMAGE     "/usr/share/app-install/icons/akicon.png"  /* solid square */
#define DEFAULT_SECURITY_INDICATOR_IMAGE2    "/usr/share/app-install/icons/xv.png" /* solid square */

/* -------------------------------------------- */
/* color index */
#define RED_IDX   0
#define GREEN_IDX 1
#define BLUE_IDX  2

/* -------------------------------------------- */



/* Global Platform constants & data types */

#define TUI_SESSION_TIMEOUT          10 /* 10 seconds in GP */
#define TEE_TUI_NUMBER_BUTTON_TYPES  0x00000006

typedef enum {
	TEE_TUI_HIDDEN_MODE = 0,      /* never visible */
	TEE_TUI_CLEAR_MODE,           /* always visible */
	TEE_TUI_TEMPORARY_CLEAR_MODE  /* visible then hidden, delay=? */
} TEE_TUIEntryFieldMode;

typedef enum {
	TEE_TUI_NUMERICAL = 0,
	TEE_TUI_ALPHANUMERICAL
} TEE_TUIEntryFieldType;

typedef enum {
	TEE_TUI_PORTRAIT = 0,
	TEE_TUI_LANDSCAPE
} TEE_TUIScreenOrientation;

typedef enum {
	TEE_TUI_CORRECTION = 0,
	TEE_TUI_OK,
	TEE_TUI_CANCEL,
	TEE_TUI_VALIDATE,
	TEE_TUI_PREVIOUS,
	TEE_TUI_NEXT,
	TEE_TUI_TERMINATE = 0x8001
} TEE_TUIButtonType;

typedef enum {
	TEE_TUI_NO_SOURCE = 0,
	TEE_TUI_REF_SOURCE,
	TEE_TUI_OBJECT_SOURCE,
	TEE_TUI_FILE_SOURCE = 0x8001
} TEE_TUIImageSource;

typedef struct {
	TEE_TUIImageSource source;
	struct {
		/* [inbuf] */
		void *image;
		size_t imageLength;
	} ref;
	struct {
		uint32_t storageID;
		/* [in(objectIDLength)] */
		void *objectID;
		size_t objectIDLen;
	} object;
	uint32_t width;
	uint32_t height;
} TEE_TUIImage;

typedef struct {
	char *text;
	uint32_t textXOffset;         /* top-LEFT */
	uint32_t textYOffset;         /* TOP-left */
	uint8_t textColor[3];         /* 0=Red, 1=Green, 2=Blue */
	TEE_TUIImage image;
	uint32_t imageXOffset;
	uint32_t imageYOffset;
} TEE_TUIScreenLabel;           /* the label for TA branding/mesg, generally on the top of screen */

typedef struct {
	char *text;
	TEE_TUIImage image;
} TEE_TUIButton;


/* this is for ONE tui (one session may contain N TUIs): */
typedef struct {
	TEE_TUIScreenOrientation screenOrientation;
	TEE_TUIScreenLabel label;     /* for TA branding */
	TEE_TUIButton *buttons[TEE_TUI_NUMBER_BUTTON_TYPES];
	bool requestedButtons[TEE_TUI_NUMBER_BUTTON_TYPES];
} TEE_TUIScreenConfiguration;

/* zxf: These buttons can be part of the soft-keyboard! */
typedef struct {
	char *buttonText;
	uint32_t buttonWidth;         /* 0 for non-customnization */
	uint32_t buttonHeight;        /* 0 for non-customnization */
	bool buttonTextCustom;        /* exclusive: below */
	bool buttonImageCustom;       /* exclusive: up */
} TEE_TUIScreenButtonInfo;


/* this is for hardware & button info: */
typedef struct {
	uint32_t grayscaleBitsDepth;
	uint32_t redBitsDepth;
	uint32_t greenBitsDepth;
	uint32_t blueBitsDepth;
	uint32_t widthInch;           /* pixel per inch */
	uint32_t heightInch;          /* pixel per inch */
	uint32_t maxEntryFields;      /* max number of entry fields that can be displayed. */
	uint32_t entryFieldLabelWidth;        /* in pixel */
	uint32_t entryFieldLabelHeight;       /* in pixel */
	uint32_t maxEntryFieldLength; /* max chars for each entry field. */
	uint8_t labelColor[3];        /* 0=Red, 1=Green, 2=Blue */
	uint32_t labelWidth;          /* for canvas */
	uint32_t labelHeight;         /* for canvas */
	TEE_TUIScreenButtonInfo buttonInfo[TEE_TUI_NUMBER_BUTTON_TYPES];
} TEE_TUIScreenInfo;

/* r,g,b: uint8_t */
#define RGB(r,g,b)  ((r<<16) | (g<<8) | b)
#define ARGB(a,r,g,b)  ((a<<24) | (r<<16) | (g<<8) | b)
#define MK_HW_COLOR(scrninfo,red8,green8,blue8)  ({ \
        uint32_t c = 0; \
        TEE_TUIScreenInfo *scrn = (scrninfo); \
        uint8_t r=(red8), g=(green8), b=(blue8); \
        c +=  scrn->redBitsDepth>8   ?r<<(scrn->redBitsDepth   - 8) :r>>(8 - scrn->redBitsDepth); \
        c <<= scrn->greenBitsDepth; \
        c +=  scrn->greenBitsDepth>8 ?g<<(scrn->greenBitsDepth - 8) :g>>(8 - scrn->greenBitsDepth); \
        c <<= scrn->blueBitsDepth; \
        c +=  scrn->greenBitsDepth>8 ?b<<(scrn->greenBitsDepth - 8) :b>>(8 - scrn->greenBitsDepth); \
        c; \
        })

/**
* @ingroup  TEE_TUI_API
* 表示获取用户输入的输入字段
*/
typedef struct {
	char *label;
	TEE_TUIEntryFieldMode mode;
	TEE_TUIEntryFieldType type;
	uint32_t minExpectedLength;
	uint32_t maxExpectedLength;
	/* [outstring] */
	char *buffer;
	size_t bufferLength;
} TEE_TUIEntryField;

/* -------------------------------------------- */

/* -------------------------------------------- */
/* functions  */

/**
* @ingroup  TEE_TUI_API
* @brief 声明对当前TA的TUI资源的独占访问权
*
* @par 描述:
* 初始化TUI SESSION
*
* @attention 无
*
* @param 无
*
* @retval #TEE_SUCCESS             执行成功
* @retval #TEE_ERROR_BUSY TUI      已被占用
* @retval #TEE_ERROR_OUT_OF_MEMORY 内存太少
*
* @par 依赖:
* @li tee_tui_api.h：该接口声明所在的头文件。
* @see 无
* @since iCOS V100R007C00SPC200
*/
TEE_Result TEE_TUIInitSession(void);

/**
* @ingroup  TEE_TUI_API
* @brief 释放之前占用的TUI资源
 *
 * @par 描述:
 * 关闭TUI SESSION
 *
* @attention 无
*
* @param
*
* @retval #TEE_SUCCESS         执行成功
* @retval #TEE_ERROR_BAD_STATE 当前TA不在最初由成功调用
*                              TEE_TUIInitSession启动的
*                              TUI会话内。
* @retval #TEE_ERROR_BUSY TUI  资源正在使用
*
* @par 依赖:
* @li tee_tui_api.h：该接口声明所在的头文件。
* @see 无
* @since iCOS V100R007C00SPC200
*/
TEE_Result TEE_TUICloseSession(void);

/**
* @ingroup  TEE_TUI_API
* @brief 检查文本是否满足显示要求，并且返回宽高信息
 *
 * @par 描述:
 * 检查字符串是否可以显示，并返回系统显示字符串的高度和宽度
 *
* @attention 无
*
* @param text        [IN]  需检查文本
* @param width       [OUT] 宽
* @param height      [OUT] 高
* @param lastIndex   [OUT] 指示已检查的最后一个字符。如果成功，
*                          则它对应于文本字符串的最后一个字符。
*                          如果失败，则表示导致失败的字符索引。
*                          索引从0开始。
*
* @retval #TEE_SUCCESS             执行成功
* @retval #TEE_ERROR_NOT_SUPPORTED 该文本不支持
*
* @par 依赖:
* @li tee_tui_api.h：该接口声明所在的头文件。
* @see 无
* @since iCOS V100R007C00SPC200
*/
TEE_Result TEE_TUICheckTextFormat(
	/*[in] */ char *text,
	/*[out] */ uint32_t *width,
	/*[out] */ uint32_t *height,
	/*[out] */ uint32_t *lastIndex
);

/**
* @ingroup  TEE_TUI_API
* @brief 根据其方向和所需输入字段的数量检索有关屏幕的信息
*
* @par 描述:
* 获取基于输入框数目和屏幕方向的屏幕信息
*
* @attention 无
*
* @param screenOrientation   [IN]  请求的方向屏幕信息
* @param nbEntryFields       [IN]  请求了多少个输入字段
* @param screenInfo          [OUT] 返回给定方向的请求屏幕上的信息
*
* @retval #TEE_SUCCESS             执行成功
* @retval #TEE_ERROR_NOT_SUPPORTED 请求的输入字段数不支持。
*				                   在这种情况下，screenInfo输出
*				                   参数的字段maxEntryFields设置
*				                   为给定方向支持的最大输入字段数。
*
* @par 依赖:
* @li tee_tui_api.h：该接口声明所在的头文件。
* @see 无
* @since iCOS V100R007C00SPC200
*/
TEE_Result TEE_TUIGetScreenInfo(
	/*[in] */ TEE_TUIScreenOrientation screenOrientation,
	/*[in] */ uint32_t nbEntryFields,
	/*[out] */ TEE_TUIScreenInfo *screenInfo
);

/**
* @ingroup  TEE_TUI_API
* @brief 显示TUI界面
*
* @par 描述:
* 根据传入的各区域参数，从上到下显示TUI界面，
*
* @attention 无
*
* @param screenConfiguration   [IN]  配置屏幕标签和屏幕按钮
* @param closeTUISession       [IN]  函数退出时TUI Session是否自动关闭
* @param entryFields           [IN]  entry数组
* @param entryFieldCount       [IN]  数组个数
* @param selectedButton        [OUT] 表示用户选择退出TUI屏幕的按钮
*
* @retval #TEE_SUCCESS               执行成功
* @retval #TEE_ERROR_OUT_OF_MEMORY   内存不足
* @retval #TEE_ERROR_ITEM_NOT_FOUND  TA提供的至少一个图像是指
*                                    由不存在的storageID表示的存储
*                                    ，或者在存储中找不到相应的对象
*                                    标识符
* @retval #TEE_ERROR_ACCESS_CONFLICT TA提供的至少一个图像引用可
*                                    信存储中的数据对象，则在打开对
*                                    象时检测到访问权限冲突。
* @retval #TEE_ERROR_BAD_FORMAT      至少一个输入图像不符合PNG格式。
* @retval #TEE_ERROR_BAD_STATE       当前TA不在最初由成功调用
*                                    TEE_TUIInitSession启动的TUI会话内。
* @retval #TEE_ERROR_BUSY TUI        资源当前正在使用
* @retval #TEE_ERROR_CANCEL          在当前显示TUI屏幕时取消了操作。
* @retval #TEE_ERROR_EXTERNAL_CANCEL 当前显示TUI屏幕时，REE中
*                                    发生的外部事件已取消操作。
*
* @par 依赖:
* @li tee_tui_api.h：该接口声明所在的头文件。
* @see 无
* @since iCOS V100R007C00SPC200
*/
TEE_Result TEE_TUIDisplayScreen(
	/*[in] */ TEE_TUIScreenConfiguration *screenConfiguration,
	/*[in] */ bool closeTUISession,
	/*[in] */ TEE_TUIEntryField *entryFields,
	/*[in] */ uint32_t entryFieldCount,
	/*[out] */ TEE_TUIButtonType *selectedButton
);

/**
* @ingroup  TEE_TUI_API
* @brief TUI显示，用户通过指纹进行验证
*
* @par 描述:
* 该函数用于通知TUI退出，在TUI+指纹的场景，TA的一个session打开TUI，
* 当用户按指纹时通知另一个session调用该函数，TUI函数会返回指纹ID。
* 使用该接口需要与华为确认
*
* @attention 使用该接口需要与华为确认
*
* @param 无
*
* @retval #TEE_SUCCESS         执行成功
* @retval #TEE_ERROR_BAD_STATE 关闭的TUI session没有被成功的打开或者
*                              已经关闭（由于timeout或其它异常事件导致）
* @retval #TEE_ERROR_GENERIC   系统内部通用错误
*
* @par 依赖:
* @li tee_tui_api.h：该接口声明所在的头文件。
* @see 无
* @since iCOS V100R007C00SPC200
*/
TEE_Result TEE_TUINotify_fp(void);

/**
* @ingroup  TEE_TUI_API
* @brief 设置汉字编码格式
* 
* @par 描述:
* 函数用于设置汉字编码，系统默认支持UTF-8，如果是UTF-8编码则无需调用
* 此函数，系统默认支持； 如果是GBK编码则需要调用该函数，参数传1。每个
* TUI界面仅支持一种编码。使用该接口需要与华为确认
*
* @attention 使用该接口需要与华为确认
*
* @param type     [IN] 需要支持的汉字编码格式，0为UTF-8编码，1为GBK编码
*
* @retval #TEE_SUCCESS 执行成功
*
* @par 依赖:
* @li tee_tui_api.h：该接口声明所在的头文件。
* @see 无
* @since iCOS V100R007C00SPC200
*/
TEE_Result  TEE_TUISetInfo(int type);
/* -------------------------------------------- */
/* -------------------------------------------- */

#endif
