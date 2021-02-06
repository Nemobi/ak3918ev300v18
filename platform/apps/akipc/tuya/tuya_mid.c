#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#include "ak_config.h"

#include "ak_vi.h"
#include "tuya_func.h"

#define ANYKA_CONFIG_PATH "/etc/jffs2/anyka_cfg.ini"

void * mid_vi_handle=NULL;
void * mid_ai_handle=NULL;
void * mid_ao_handle=NULL;

/////for palt
void mid_plat_init(void *vi_handle, void * ai_handle, void * ao_handle )
{
	mid_vi_handle= vi_handle;
	mid_ai_handle= ai_handle;
	mid_ao_handle= ao_handle;
}

////////////////for in
void * mid_in_get_vi_handle()
{
	return mid_vi_handle;
}

void * mid_in_get_ai_handle()
{
	return mid_ai_handle;
}

void * mid_in_get_ao_handle()
{
	return mid_ao_handle;
}

int mid_net_get_flip_mirror()
{
	int flip=0, mirror=0,  ret=0 ;
	ak_vi_get_flip_mirror(mid_vi_handle, &flip,        &mirror);
	if(flip==0 && mirror==0)
	{
		ret=0;
	}
	else if(flip==1 && mirror==0)
	{
		ret=1;
	}
	else if(flip==0 && mirror==1)
	{
		ret=2;
	}
	else if(flip==1 && mirror==1)
	{
		ret=3;
	}

	return ret;
}

void mid_net_set_flip_mirror(int mode)
{
	int flip=0, mirror=0 ;
	switch (mode)
	{
		case 0:
		{
			flip=0;
			mirror=0;
		}
		case 1:
		{
			flip=1;
			mirror=0;
		}
		case 2:
		{
			flip=0;
			mirror=1;
		}
		break;
		case 3:
		{
			flip=1;
			mirror=1;
		}
		break;
		default:
		break;	
	}
	ak_vi_set_flip_mirror(mid_vi_handle, flip,        mirror);
}




int mid_net_get_record_type()
{
	int ret=0;
	struct video_record_config *record_config = ak_config_get_record();
	if(record_config->server_flag==0)
	{
		ret = 0; //stop
	}
	else
	{
		if(record_config->record_mode ==1)
		{
			ret=1;//full time
		}
		else
		{
			ret=2;
		}
	}
	return ret;
}

int mid_net_set_flip_mirror2(int flip_enable)
{	
	if(mid_vi_handle)
	{
		return ak_vi_set_flip_mirror(mid_vi_handle, flip_enable, 0);
	}
	else
	return -1;
}

