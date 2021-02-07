/*********************************************************************************
  *Copyright(C),2015-2020, TUYA www.tuya.comm
  *FileName:    tuya_ipc_qrcode_demo
**********************************************************************************/
#include "tuya_ipc_api.h"
#include "tuya_ipc_qrcode_proc.h"
#include <unistd.h>
#include "tuya_func.h"

#if defined(WIFI_GW) && (WIFI_GW==1)

STATIC CHAR_T* __tuya_linux_get_snap_qrcode(VOID)
{
    //需要开发者实现从摄像头解析二维码信息
    return mid_get_wifiinfo_from_zbar2();
}

int s_enable_qrcode = 1;
void *thread_qrcode(void *arg)
{
    printf("Qrcode Thread start\r\n");
    while(s_enable_qrcode)
    {
        usleep(1000*1000);
        char *pStr = __tuya_linux_get_snap_qrcode();
        if(pStr)
        {
			printf("-%s:%s:%d---------------------\n",__FILE__,__func__,__LINE__);
			printf("-%s:%s:%d---------------------\n",__FILE__,__func__,__LINE__);
            printf("get string from qrcode %s\r\n",pStr);
			printf("-%s:%s:%d---------------------\n",__FILE__,__func__,__LINE__);
			printf("-%s:%s:%d---------------------\n",__FILE__,__func__,__LINE__);
            OPERATE_RET ret = tuya_ipc_direct_connect(pStr, TUYA_IPC_DIRECT_CONNECT_QRCODE);
            if(ret == OPRT_OK)
            {
                printf("register to tuya cloud via qrcode success\r\n");
                break;
            }
        }
    }

    printf("Qrcode Proc Finish\r\n");
    return (void *)0;
}
#endif

