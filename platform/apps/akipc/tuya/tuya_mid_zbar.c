#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include "ak_common.h"
#include "ak_thread.h"
#include "ak_vi.h"
#include "ak_venc.h"
#include "ak_config.h"
#include "zbar.h"
#include <sys/types.h>    
#include <fcntl.h>
#include <ctype.h>

#include "ak_config.h"
#include "tuya_func.h"

char wifiinfo_buf[1024]={0};

static int qrcode_parse_from_buffer(void *y8data, int w, int h)
{
	zbar_image_scanner_t *scanner = NULL;
	zbar_image_t *image =NULL;
	if(y8data == NULL) {
		return -1;
	}
	scanner = zbar_image_scanner_create();
	zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_ENABLE, 1);
	image =zbar_image_create();
	zbar_image_set_format(image, *(int*)"Y800");
	zbar_image_set_size(image, w, h);
	zbar_image_set_data(image, y8data, w * h, zbar_image_free_data);
	int n = zbar_scan_image(scanner, image);
	if(n>0)
	{
		const zbar_symbol_t *symbol = zbar_image_first_symbol(image);
		for(; symbol; symbol = zbar_symbol_next(symbol)) {
			zbar_symbol_type_t typ = zbar_symbol_get_type(symbol);
			const char *data = zbar_symbol_get_data(symbol);
			if(data != NULL) {
				strncpy(wifiinfo_buf, data, zbar_symbol_get_data_length(symbol));
				printf("decoded %s symbol \"%s\"\n", zbar_get_symbol_name(typ), data);
			}
		 }
	}
	if(image != NULL)
	{
	  //zbar_image_destroy(image);
	  free(image);
	  image = NULL;
	}
	zbar_image_scanner_destroy(scanner);
	return 0;
}

static int  get_yuv_frame()
{
	    ak_print_normal_ex("begin\n");
		struct video_input_frame vframe;
		void *video_snap_handle=NULL;
        int i =0;
		while(1){
			if(video_snap_handle==NULL)
			{
				ak_sleep_ms(10);
				video_snap_handle=mid_in_get_vi_handle();
				continue;
				
			}
			if((ak_vi_get_frame(video_snap_handle, &vframe) == 0)){
				ak_vi_release_frame(video_snap_handle, &vframe);
			}
			memset(&vframe, 0, sizeof(struct video_input_frame));
			if( i++ > 3) break;
	    }
		for (i = 0; i < 2; )
		{
			if (ak_vi_get_frame(video_snap_handle, &vframe)) {
				//ak_print_error_ex("ak_video_input_get_frame fail!\n");
				continue;
			} else {
			    i++;
				if(!qrcode_parse_from_buffer(vframe.vi_frame[VIDEO_CHN_SUB].data,640,360))
				{
			    	printf("-----wifiinfo_buf = %s-------\n",wifiinfo_buf);
				}
				ak_vi_release_frame(video_snap_handle, &vframe);
			}
	 }
	ak_print_normal_ex("end\n");
	return 0;
}

char * mid_get_wifiinfo_from_zbar2()
{
	int ret=1;
	int count=0;
	while(1)
	{
		ret=get_yuv_frame();
		if(ret==0 && strlen(wifiinfo_buf)>10)
		{
			break;
		}
		if(count==0)
		{
			printf("------------------------------------------------------------------------\n");
			printf("------------------------------------------------------------------------\n");
			printf("-------ret=%d---wifiinfo_buf_len=%d-----------------------\n",ret,strlen(wifiinfo_buf));
			printf("------------------------------------------------------------------------\n");
			printf("------------------------------------------------------------------------\n");
		}
		count=(count+1)%20;
		ak_sleep_ms(100);
	}
	
	printf("------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n");
	printf("-------wifiinfo_buf=%s--------------------------\n",wifiinfo_buf);
	printf("------------------------------------------------------------------------\n");
	printf("------------------------------------------------------------------------\n");
	return wifiinfo_buf;
}


