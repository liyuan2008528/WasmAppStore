#ifndef __WINDOW_EXT_H__
#define __WINDOW_EXT_H__

struct __WindowHandle_ext {
	void *winhandle;
};
typedef struct  __WindowHandle_ext *WindowHandle_ext;

typedef struct{
	char *text;
	uint32_t text_color;         /* 0=Red, 1=Green, 2=Blue */
	uint32_t bg_color;
	uint32_t fg_color;
	uint32_t value;

}obj_info_ext;

struct dia_config_ext {
	obj_info_ext label;
	obj_info_ext button;
	uint32_t width;
	uint32_t height;
	uint32_t top;
	uint32_t timeout;
};
struct entry_config_ext {
	char *name;
	uint32_t name_len;
	char *text;
	uint32_t text_len;
	char *img;
	int img_len;
	uint32_t entry_type;
	uint32_t color;
	uint32_t paddingLeft;
	uint32_t key_val;
};
enum TEE_dialog_type_ext {
    TICK_DIALOG_TIMEOUT_TYPE_EXT = 0x1,
    TICK_DIALOG_BUTTON_TYPE_EXT = 0x2,
    TICK_DIALOG_MAX_TYPE_EXT = 0x3
};

TEE_Result TEE_EXT_tui_hw_init(void);
TEE_Result TEE_EXT_tui_create_win(char *text, uint32_t text_len, WindowHandle_ext *win_handle);
TEE_Result TEE_EXT_tui_set_entry(struct entry_config_ext *entry_change, WindowHandle_ext win_handle);
TEE_Result TEE_EXT_tui_show_win(WindowHandle_ext win_handle);
TEE_Result TEE_EXT_tui_create_dialog(int type, const struct dia_config_ext *dia_t, WindowHandle_ext win_handle);
TEE_Result TEE_EXT_tui_destory_win(WindowHandle_ext win_handle);
TEE_Result TEE_EXT_tui_get_event(WindowHandle_ext win_handle, int32_t *type);
TEE_Result TEE_EXT_tui_hw_exit(void);

#endif
