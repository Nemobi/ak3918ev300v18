#ifndef        _PARTITION_LIB_H_
#define        _PARTITION_LIB_H_


#ifndef	NULL
#define	NULL	((void *) 0)
#endif

#ifdef CONFIG_MTD_AK_SPIFLASH
#define SUPPORT_SPIFLASH
#endif

#ifdef CONFIG_MTD_AK_SPINAND
#define SUPPORT_SPINAND
#endif


#define     PARTITION_NAME_LEN                  6

typedef enum
{
   PART_NO_HIDDEN = 0,
   PART_HIDDEN,
}PART_HIDDEN_TYPE;


typedef enum
{
   PART_ONLY_READ = 0,
   PART_READ_WRITE,
}PART_R_OR_W_TYPE;


typedef enum
{
   PART_DATA_TYPE = 0,
   PART_BIN_TYPE,
   PART_FS_TYPE,
}PART_TYPE;

typedef enum
{
   FS_SQSH4 = 0,
   FS_JFFS2,
   FS_YAFFS2,
}FS_TYPE;


typedef enum
{
   MEDIUM_SPINOR = 0,
   MEDIUM_SPINAND,
}MEDIUM_TYPE;

typedef enum
{
   PART_SPIFLASH = 0,
   PART_SPINAND,
   PART_SPINOR_SPINAND,
}PART_MEDIUM;




typedef struct
{
    unsigned long page_size; /*spi page size*/
    unsigned long pages_per_block;/*page per block*/
    unsigned long total_size;/*spiflash size*/
}T_SPI_INIT_INFO, *T_PSPI_INIT_INFO;

typedef struct
{
	unsigned char  name[PARTITION_NAME_LEN];	//�̷���
	unsigned long  Size;                     //������С
    unsigned long  ld_addr;	                //���е�ַ
    unsigned char  type;				        //�����������ͣ�data , bin, fs
    unsigned char  r_w_flag;			        //	r_w or onlyread
    unsigned char  hidden_flag;			    //	hidden_flag or no hidden_flag
    unsigned char  backup;				    //�Ƿ񱸷�
	unsigned char  check;                   //�Ƚ�
	unsigned char  mtd_idex;                //mtd��idex
    unsigned char  fs_type;                 //�ļ�ϵͳ����
    unsigned char  medium_flag:1;           //0 -> not need medium_tpye,1->need medium_type
	unsigned char  medium_type:1;           //0->spi, 1->spinand
	unsigned char  rev1:6;
    unsigned long  flash_startpos;          //�˷�����flash
}T_CREAT_PARTITION_INFO;


typedef struct
{
    unsigned long   file_length;    //bin:file_length  fs:δ��      
    unsigned long   ld_addr;        //bin: ld_addr     fs:δ��
    unsigned long   backup_pos;     //bin:backup_page  fs:δ��     //�ֽ�Ϊ��λ
    unsigned char   check;          //bin:check          fs:δ��  
    unsigned char   mtd_idex;
    unsigned char   medium_flag:1;  //介质是否区分的标志，0 -》not need medium_tpye,1->need medium_type
	unsigned char   medium_type:1; //0表示spi, 1表示spinand
	unsigned char   rev1:6;
    unsigned char   rev2;
}T_BIN_CONFIG;

typedef struct
{
    unsigned long   file_length;    //  �ļ�ϵͳ�ľ����ļ�����Ч���ȣ�Ŀǰ�ض��������õ�    
    unsigned char   check;          //  �Ƿ�Ƚ�
    unsigned char   mtd_idex;       //mtd��idex
    unsigned char   fs_type;        //�ļ�ϵͳ��������
    unsigned char   medium_flag:1;  //介质是否区分的标志，0 -》not need medium_tpye,1->need medium_type
	unsigned char   medium_type:1;  //0表示spi, 1表示spinand
	unsigned char   rev1:6;
    unsigned long   rev2;          //
    unsigned long   rev3;          //  
}T_FS_CONFIG;

typedef struct
{
    unsigned long   pos;    //      
    unsigned char   table[512];
}T_PARTITION_TABLE_CONFIG;


typedef struct
{
    unsigned long  parameter1;    //bin:file_length  fs:δ��      
    unsigned long  parameter2;    //bin: ld_addr     fs:δ��
    unsigned long  parameter3;    //bin:backup_page  fs:δ��     
    unsigned long  parameter4;    //bin:check          fs:δ��     
}T_EX_PARTITION_CONFIG;

typedef struct
{
    unsigned char           type;                     //data,/bin/fs  ,  E_PARTITION_TYPE
    volatile unsigned char  r_w_flag:4;               //only read or write
    unsigned char           hidden_flag:4;            //hidden or no hidden
    unsigned char           name[PARTITION_NAME_LEN]; //������
    unsigned long           ksize;                    //������С��KΪ��λ
    unsigned long           start_pos;                //�����Ŀ�ʼλ�ã��ֽ�Ϊ��λ     
}T_PARTITION_CONFIG;


typedef struct
{
    T_PARTITION_CONFIG        partition_info;
    T_EX_PARTITION_CONFIG     ex_partition_info;
}T_PARTITION_TABLE_INFO;



/************************************************************************
 * NAME:     partition_getversion
 * FUNCTION  get partition vesion
 * PARAM:    void
 * RETURN:   version
**************************************************************************/
unsigned char *partition_getversion(void);

/************************************************************************
 * NAME:     Sflash_Creat
 * FUNCTION  partition creat
 * PARAM:    [in] T_CREAT_PARTITION_INFO *partition
 * RETURN:   success handle, fail retuen null
**************************************************************************/
void *partition_creat(T_CREAT_PARTITION_INFO *partition);


/************************************************************************
 * NAME:     Sflash_Close
 * FUNCTION  partition close
 * PARAM:    [in] T_PARTITION_TABLE_INFO *pFile
 * RETURN:   success return 0, fail retuen -1
**************************************************************************/
int partition_close(void *handle);

/************************************************************************
 * NAME:     Sflash_Open
 * FUNCTION  partition open
 * PARAM:    [in] unsigned char *partition_name
 * RETURN:   success return T_PARTITION_TABLE_INFO *pFile, fail retuen AK_NULL
**************************************************************************/
void *partition_open(unsigned char *name);

/************************************************************************
 * NAME:     Sflash_Write
 * FUNCTION  partition write
 * PARAM:    [in] T_PARTITION_TABLE_INFO *pFile, 
                   [in] unsigned char *data, 
                   [in]  unsigned LONG data_len
 * RETURN:   success handle, fail retuen null
**************************************************************************/
int partition_write(void *handle, unsigned char *data, unsigned long data_len);


/************************************************************************
 * NAME:     Sflash_Read
 * FUNCTION  partition read
 * PARAM:    [in] T_PARTITION_TABLE_INFO *pFile, 
                   out] unsigned char *data, 
                   [in]  unsigned LONG data_len
 * RETURN:   success return 0, fail retuen -1
**************************************************************************/
int partition_read(void *handle, unsigned char *data, unsigned long data_len);


/************************************************************************
 * NAME:     Partition_Get_Attr
 * FUNCTION  get partition ex_attr 
 * PARAM:   [in] T_U32pFile, 
                  [out]  T_pVOID ex_arrt
 * RETURN:   success return 0, fail retuen -1
**************************************************************************/

int partition_get_attr(void *handle, T_EX_PARTITION_CONFIG *ex_arrt);


/************************************************************************
 * NAME:     Partition_Set_Attr
 * FUNCTION  set partition ex_attr 
 * PARAM:    [in] T_U32pFile, 
                   [out]  T_pVOID ex_arrt
 * RETURN:   success return 0, fail retuen -1
**************************************************************************/
int partition_set_attr(void *handle, T_EX_PARTITION_CONFIG *ex_arrt);


/************************************************************************
 * NAME:     Partition_Get_Partition_Table
 * FUNCTION get the partition table
 * PARAM:    T_PARTITION_TABLE_CONFIG *part_talbe
 * RETURN:    success return 0, fail retuen -1
**************************************************************************/
//spiflash��spinand��page size is diffrent
int partition_get_partition_table(T_PARTITION_TABLE_CONFIG *part_talbe, PART_MEDIUM medium_type);
int partition_get_partition_backup_table(T_PARTITION_TABLE_CONFIG *part_talbe, PART_MEDIUM medium_type);


/************************************************************************
 * NAME:     partition_get_data_size
 * FUNCTION get the partition data size
 * PARAM:    T_PARTITION_TABLE_CONFIG *part_talbe
 * RETURN:    success return data_size, fail retuen 0
**************************************************************************/
unsigned long partition_get_data_size(void *handle);


/************************************************************************
 * NAME:     partition_get_ksize
 * FUNCTION get partition size ,K
 * PARAM:    void *handle
 * RETURN:    success return ksize, fail retuen 0
**************************************************************************/

unsigned long partition_get_ksize(void *handle);


///////////////////////////////////////////////////////////////////////////////////////
//�˽ӿ����ṩ����¼ʹ�ã�
//����ȫ����¼ʱ�����һ��mac��ַ����
//����ʱboot�Ĵ�С�����֮ǰ��һ������ô�������λ�þͲ�һ����
//�����ڶ�mac��ַʱ����Ҫ���þɵķ������������������µķ�����
void partition_set_partition_startpage(unsigned long start_page, PART_MEDIUM medium_type);
void partition_set_partition_startpage_spinand(unsigned long *start_page, unsigned long *backup_start_page);


//������ӿ�ֻӦ����spiflash��
//�����Ż����ܵ����⣬��¼ʱpartition����ж�β�д����ռ��һЩʱ�䣬������������¼ʱ��ֻ��������ʱ���ٽ��а���Щ����д��ȥ
int partition_burn_partitiontab_info_init_spiflash(unsigned char burn_mode);
int partition_burn_partitiontab_info_end_spiflash(void);



#endif      //_FHA_BINBURN_H_


