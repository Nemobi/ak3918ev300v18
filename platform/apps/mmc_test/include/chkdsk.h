#ifndef _CHKDSK_H_
#define _CHKDSK_H_
#define CLUSTER_MAP_NUMBER  100
typedef struct _CLUSTER_MAP_ARRAY_INFO *PSECTOR_MAP_ARRAY_INFO;

typedef struct _CLUSTER_MAP_INFO
{
	T_U32 sectorAddr;	//�˻���������Ӧ��SECOTR,��ΪFAT������̫��,���Զ���ΪT_U16�Ա��ʡ�ڴ�,�����ֵΪ-1,��ʾ���������û�б���ʹ��.
	T_U32 bitNum;		//��¼λͼ���ж��ٸ�λ����1��,���������CluserPerSector,����ʾλͼΪȫ1״̬,���ͷŴ˻�����.
	T_U8 *bitMap;		//λͼ����,������ָ����,����Ϊ��ʱ����1,����Ϊ0,���ȫΪ1ʱ,���ͷ����������(��sectorAddr = T_U16_MAX),�Ա���������ʹ��.����������Ĵ�СΪBytesPerSector/8.
} CLUSTER_MAP_INFO, *PCLUSTER_MAP_INFO;

typedef struct _CLUSTER_MAP_ARRAY_INFO
{
	T_U32 index;		//�ػ�����,ÿ�η���100��.
	PSECTOR_MAP_ARRAY_INFO next;		//ָ����һ���󻺳���
	PCLUSTER_MAP_INFO pMapArray;		//�ػ�����,ÿ�η���100��.
	PSECTOR_MAP_ARRAY_INFO pCurSecMap;		//ָ��ǰ����ʹ�õ�С������
}SECTOR_MAP_ARRAY_INFO;


enum{MARK_FAT_OK, FAT_LINK_ERROR, MARK_MALLOC_ERROR, FAT_READ_ERROR};

#define TestBitMap(BitMap, item)    (((BitMap)[(item)>>3]&(1<<((item)&7))))
#define SetBitMap(BitMap, item)     ((BitMap)[(item)>>3] |= (1<<((item)&7)))
#define ClrBitMap(BitMap, item)     ((BitMap)[(item)>>3] &= ~(1<<((item)&7)))

typedef void F_ChkDskCallback(T_VOID *pData, T_U8 percent);
T_U32 FAT_GetFatLinkInfo(T_U8 * pFatBuf, T_U16 offset, T_U8 FSType);
T_U32 FAT_GetFatLinkInfo_chkdsk(T_U8 * pFatBuf, T_U16 offset, T_U8 FSType);
T_BOOL Fat_ChkDsk(T_U32  DriverID, F_ChkDskCallback pCallBack, T_VOID *CallbackData);
T_VOID FAT_SetFatLinkInfo(T_U8 * pFatBuf, T_U16 offset, T_U8 FSType, T_U32 newValue);


#endif

