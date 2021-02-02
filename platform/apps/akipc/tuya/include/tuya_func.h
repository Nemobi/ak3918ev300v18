#ifndef __TUYA_FUNC_H__
#define __TUYA_FUNC_H__
#include "tuya_ipc_media.h"
VOID TUYA_APP_Enable_Speaker_CB(BOOL_T enabled);
VOID TUYA_APP_Rev_Audio_CB(IN CONST MEDIA_FRAME_S *p_audio_frame,
                           TUYA_AUDIO_SAMPLE_E audio_sample,
                           TUYA_AUDIO_DATABITS_E audio_databits,
                           TUYA_AUDIO_CHANNEL_E audio_channel);
VOID tuya_ipc_sd_format(VOID);
UINT_T IPC_APP_get_sd_record_mode(VOID);
BOOL_T IPC_APP_get_alarm_function_onoff(VOID);
BOOL_T IPC_APP_get_alarm_zone_onoff(VOID);
char * IPC_APP_get_alarm_zone_draw(VOID);
#endif