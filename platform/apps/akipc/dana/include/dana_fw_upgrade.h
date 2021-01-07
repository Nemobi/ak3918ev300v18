#ifndef __DANA_FW_UPGRADE_H__
#define __DANA_FW_UPGRADE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef enum _dana_fw_upgrade_err_e_ {
    DANA_FW_UPGRADE_ERR_NULL            =   0x00000000, // succeeded
    DANA_FW_UPGRADE_ERR_FAILED          =   0x00000001, // failed
    DANA_FW_UPGRADE_ERR_UNKNOWN         =   0x00000002, // δ֪����
    DANA_FW_UPGRADE_ERR_URL_NOT_SUPPORT =   0x00000003, // ��֧��URL����
    DANA_FW_UPGRADE_ERR_FILE_CORRUPTION =   0x00000005, // �ļ���
    DANA_FW_UPGRADE_ERR_NETWORK         =   0x00000006, // �����쳣
    DANA_FW_UPGRADE_ERR_RW              =   0x00000007, // �ļ�дʧ��
    DANA_FW_UPGRADE_ERR_CANCEL          =   0x00000008, // ���ر�ȡ��
} dana_fw_upgrade_err_t;



typedef struct _dana_fw_upgrade_callback_funs_s {
    // �¹̼��ص�
    // �������0,ģ��Ὺʼ���������̼���, ��Ҫָ��save_pathname ��������·�����ļ���
    uint32_t (*dana_fw_upgrade_new_rom_come)(const uint64_t rom_size, const char *rom_ver, char save_pathname[512]);
    
    // ������ɻص�
    void (*dana_fw_upgrade_rom_download_complete)(const uint32_t code, const char *rom_pathname);
    
    // ȷ�������ص�
    // �ɹ����ع̼�����App�����û�ȷ��,ֻ������ص���������,�ſ�����������
    // upgrade_timeout_sec �������������ʱ��(��������������,���豸ʵ������ʵ��,����ֻ��Ҫһ��Ԥ��ʱ��)
    // ��Ҫ��֤����������: �ļ��滻+�豸����+����
    void (*dana_fw_upgrade_confirm)(const char *rom_pathname, uint32_t *upgrade_timeout_sec);
} dana_fw_upgrade_callback_funs_t;



bool dana_fw_upgrade_init(const char *danale_path, const dana_fw_upgrade_callback_funs_t *cbs);

bool dana_fw_upgrade_deinit();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __DANA_FW_UPGRADE_H__ */
