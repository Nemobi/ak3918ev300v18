#ifndef DANA_VIDEO_IPC_CLOUD_UTILITY_H
#define DANA_VIDEO_IPC_CLOUD_UTILITY_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _danavideo_cloud_alarm_e {
    DANAVIDEO_CLOUD_ALARM_NO    = 0,    // �޸澯 
    DANAVIDEO_CLOUD_ALARM_MD    = 1,    // ��Ƶ�ڵ�       
    DANAVIDEO_CLOUD_ALARM_VB    = 2,    // �ƶ����
    DANAVIDEO_CLOUD_ALARM_UD_1  = 3,    // �Զ���澯1
    DANAVIDEO_CLOUD_ALARM_UD_2  = 4,    // �Զ���澯2
} danavideo_cloud_alarm_t;

typedef enum _danavideo_clodu_mode_e {
    DANAVIDEO_CLOUD_MODE_UNKNOWN = 0,
    DANAVIDEO_CLOUD_MODE_REALTIME,
    DANAVIDEO_CLOUD_MODE_ALARM,
} danavideo_cloud_mode_t;

uint32_t lib_danavideo_cloud_linked_version(void);
char *lib_danavideo_cloud_linked_version_str(uint32_t version);

// ���ƴ���ƻ������ı�ʱ(δ��ͨ->��ͨ; ��ͨ->δ��ͨ; realtime->alarm; alarm->realtime)
// �û���Ҫ�ڸûص������ʵʱ�ϴ��͸澯�ϴ��Ŀ���
typedef void (*danavideo_cloud_mode_changed_callback_t) (const danavideo_cloud_mode_t cloud_mode, const int32_t chan_no);
void lib_danavideo_cloud_set_cloud_mode_changed(danavideo_cloud_mode_changed_callback_t fun);

// ����ͨ������������ʹ�õ�����ڴ�(��С1M)
bool lib_danavideo_cloud_init(const uint32_t chan_num, const int32_t maximum_buffering_data, const int32_t package_size, danavideo_cloud_mode_t mode);

// ʵʱ�ϴ�
bool lib_danavideo_cloud_realtime_on();

bool lib_danavideo_cloud_realtime_off();

// msg_type����danavdieo.h�еĶ���(��֧��audio��video)
/*
 * typedef enum _danavideo_msg_type {
 *    audio_stream = 0x20000000,
 *    video_stream = 0x40000000,
 *    extend_data   = 0x60000000,
 *    pic_stream   = 0x80000000,
 * } danavideo_msg_type_t;
 */
// codec����danavideo.h�еĶ���
/*
 * typedef enum _danavideo_codec_type {
 *     H264    = 1,
 *     MPEG    = 2,
 *     MJPEG   = 3,
 *     H265    = 4,
 *     H265_HISILICON    = 5,
 *     MJPEG_DIFT        = 6,
 *     G711A   = 101,
 *     ULAW    = 102,
 *     G711U   = 103,
 *     PCM     = 104,
 *     ADPCM   = 105,
 *     G721    = 106,
 *     G723    = 107,
 *     G726_16 = 108,
 *     G726_24 = 109,
 *     G726_32 = 110,
 *     G726_40 = 111,
 *     AAC     = 112,
 *     JPG     = 200,
 * } danavidecodec_t;
 */
bool lib_danavideo_cloud_realtime_upload(const uint32_t chan_no, const uint32_t msg_type, const uint32_t codec, const uint32_t is_keyfram, const uint32_t timestamp, const danavideo_cloud_alarm_t alarm, const char *data, const uint32_t data_len, const uint32_t timeout_usec);

// �澯�ϴ� & �ļ��ϴ�
// �ļ��ϴ�����ע��һ���ϴ�����,�����ƴ洢����Զ�����ϴ�����
// ���ϴ����(�ɹ���ʧ��)����øûص�,����֪ͨ�û����ĸ������ļ�,�����û��ĺ�������(����ɾ���ļ�)
typedef void (*danavideo_cloud_customfile_upload_callback_t) (const int8_t retcode, const char *file_name, const char *file_path);

// ע��һ�������ļ��ϴ�
// ���øýӿں�save_site & save_path��������lib_danavideo_util_pushmsg
bool lib_danavideo_cloud_customfile_async_upload_pre(const uint32_t ch_no, const char *file_name, const char *file_path, uint32_t *save_site, char *save_path, const size_t save_path_len);
// ���ڸ澯�ϴ�ʱ,���籾��¼����һ����Ƶ�ļ�(Ŀǰ��֧��mp4�ļ�)
// ���ϴ���Ϻ�����lib_danavideo_cloud_realtime_upload�ص�,����ɾ���澯¼���ļ��Խ�ʡ�ռ�
bool lib_danavideo_cloud_customfile_async_upload(const uint32_t ch_no, const char *file_name, const char *file_path, danavideo_cloud_customfile_upload_callback_t fun);

bool lib_danavideo_cloud_deinit();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
