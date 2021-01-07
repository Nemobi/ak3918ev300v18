#include <linux/module.h>     //֧�ֶ�̬��Ӻ�ж��ģ��
#include <linux/kernel.h>    //����Ҫд���ںˣ����ں���ص�ͷ�ļ�
#include <linux/init.h>      //��ʼ��ͷ�ļ�

#include <linux/fs.h>        //�������ļ��������struct�Ķ���
#include <linux/types.h>     //��һЩ�������͵Ķ���
#include <linux/fcntl.h>     //�������ļ����������õ�����غ�
#include <linux/vmalloc.h>  //vmalloc()������ڴ������ַ�������������ַ������
#include <linux/blkdev.h>  //����request��ʽ ���豸����������Ҫ����blk_init_queue �����������
#include <linux/hdreg.h> //Ӳ�̲���ͷ�ļ����������Ӳ�̼Ĵ����˿ڡ�״̬��ͷ��������Ϣ��
#include <mach/map.h>

#define RAMHD_NAME              "video_ram"    //�豸����
#define RAMHD_MAX_DEVICE        1           //����豸��
#define RAMHD_MAX_PARTITIONS    1           //��������

#define RAMHD_SECTOR_SIZE       512        //������С
#define RAMHD_SECTORS           16         //������  http://www.embedu.org/Column/Column863.htm
#define RAMHD_HEADS             4         //��ͷ��
#define RAMHD_CYLINDERS         256      //�ŵ�(����)�� 

#define RAMHD_SECTOR_TOTAL      (RAMHD_SECTORS * RAMHD_HEADS * RAMHD_CYLINDERS)  //�ܴ�С
#define RAMHD_SIZE              (RAMHD_SECTOR_SIZE * RAMHD_SECTOR_TOTAL) //8MB

typedef struct{
    unsigned char   *data;             //�豸���ݿռ��׵�ַ
    struct request_queue *queue;       //�豸�������
    spinlock_t      lock;             //����������
    struct gendisk  *gd;              //ͨ�ô��̽ṹ��
}RAMHD_DEV;

static char *sdisk[RAMHD_MAX_DEVICE];  //�����ڴ���׵�ַ
static RAMHD_DEV *rdev[RAMHD_MAX_DEVICE];  //�����ڴ���׵�ַ

static dev_t ramhd_major;   //���豸��

static unsigned long disk_addr = AK_PA_VIDEO_BUFF;
static unsigned long disk_size = AK_SZ_VIDEO_BUFF;

module_param(disk_addr, ulong, S_IRUGO);
module_param(disk_size, ulong, S_IRUGO);

static int ramhd_space_init(void)
{
    int i;
    int err = 0;
    for(i = 0; i < RAMHD_MAX_DEVICE; i++){
        sdisk[i] = ioremap(disk_addr, disk_size);
        if(!sdisk[i]){
            err = -ENOMEM;  //errno:12 �ڴ治��
            return err;
        }
		memset(sdisk[i], 0, disk_size);
    }

    return err;
}

static void ramhd_space_clean(void)
{
    int i;
    for(i = 0; i < RAMHD_MAX_DEVICE; i++){
        iounmap((void*)disk_addr);
    }
}

static int alloc_ramdev(void)
{
    int i;
    for(i = 0; i < RAMHD_MAX_DEVICE; i++){
        rdev[i] = kzalloc(sizeof(RAMHD_DEV), GFP_KERNEL); //���ں�������RAMHD_DEV�ṹ����ڴ�ռ�
        if(!rdev[i])
            return -ENOMEM;   //errno:12  �ڴ治��
    }
    return 0;
}

static void clean_ramdev(void)
{
    int i;
    for(i = 0; i < RAMHD_MAX_DEVICE; i++){
        if(rdev[i])
            kfree(rdev[i]);   //�ͷŷ�����ڴ�
    }   
}       

int ramhd_open(struct block_device *bdev, fmode_t mode)   //�豸���õ�
{   
    return 0;
}

int ramhd_release(struct gendisk *gd, fmode_t mode)   //�豸�ر��õ�
{   
    return 0;
}

static int ramhd_ioctl(struct block_device *bdev, fmode_t mode, unsigned int cmd, unsigned long arg) //IO����
{
    int err;
    struct hd_geometry geo;  //hd_geometry�ṹ�������ͷ���������������Ϣ

    switch(cmd)
    {
        case HDIO_GETGEO:  //��ȡ���豸��������� 
            err = !access_ok(VERIFY_WRITE, arg, sizeof(geo));//���ָ����ָ��Ĵ洢���Ƿ��д
            if(err) return -EFAULT;     //errno:14   ��ַ�� 
        
            geo.cylinders = RAMHD_CYLINDERS;     //������
            geo.heads = RAMHD_HEADS;            //��ͷ��
            geo.sectors = RAMHD_SECTORS;        //������
            geo.start = get_start_sect(bdev);   //��ʼ��ַ
            if(copy_to_user((void *)arg, &geo, sizeof(geo)))
             //���ں˵�ַ&geoָʾ�����ݸ��Ƶ�argָ�����û��ռ�ĵ�ַ��
                return -EFAULT;   //errno:14   ��ַ�� 
            return 0;
    }
            
    return -ENOTTY;      //errno:25     ���ʵ���IO���Ʋ��� 
}

static struct block_device_operations ramhd_fops =  //��������һ�����豸�Ĳ���������
{   
	.owner = THIS_MODULE,
    .open = ramhd_open,
    .release = ramhd_release,
    .ioctl = ramhd_ioctl,
};

void ramhd_req_func (struct request_queue *q)  //�����ݸ�����豸������
{
    struct request *req;  //������ȡreq
	RAMHD_DEV *pdev;
	char *pData;
	unsigned long addr, size, start;
	req = blk_fetch_request(q); //�ӿ��豸������ȡ�洢��req;
        //blk_fetch_request()���Զ�ε��ã����queue����û�����ݣ�req������NULL
	while (req) {   //�жϵ�ǰrequest�Ƿ�Ϸ�  ѭ������������л�ȡ��һ��Ҫ���������
		start = blk_rq_pos(req); // ��ȡ��ǰrequest�ṹ����ʼ���� 
		pdev = (RAMHD_DEV *)req->rq_disk->private_data; //����豸�ṹ��ָ��
		pData = pdev->data;//�豸��ַ
		addr = (unsigned long)pData + start * RAMHD_SECTOR_SIZE;//�����ַ
        size = blk_rq_cur_bytes(req); //���� req ����һ������
		if (rq_data_dir(req) == READ) //������ݴ��ͷ���.����0��ʾ���豸��ȡ,�����ʾд���豸.
			memcpy(req->buffer, (char *)addr, size); //��
		else
			memcpy((char *)addr, req->buffer, size); //д
	
		if(!__blk_end_request_cur(req, 0))  //������������귵��false
			req = blk_fetch_request(q);  //����ȡ����������е�����
	}
}

int ramhd_init(void)   //��ʼ��
{
    int i;
	int ret;

	if((disk_addr < 0x80000000) || ((disk_addr + disk_size)  > (0x80000000 + AK_SZ_VIDEO_BUFF))){
		printk(KERN_ERR "###error!\n");
		printk(KERN_ERR "disk_addr + disk_size must :0x80000000 - %x!\n", 0x80000000 + AK_SZ_VIDEO_BUFF);
		return -1;
	}
	
    ret = ramhd_space_init();
	if(ret < 0){
		printk(KERN_ERR "###ramhd_space_init fail!\n");
		return -1;
	}
	
    ret = alloc_ramdev();
	if(ret < 0){
		printk(KERN_ERR "###alloc_ramdev fail!\n");
		return -1;
	}
    
    ramhd_major = register_blkdev(0, RAMHD_NAME); //���豸����ע�ᵽ�ں���
    //majorΪ0���ں˻��Զ�����һ���µ����豸�ţ�ramhd_major ��  
    for(i = 0; i < RAMHD_MAX_DEVICE; i++)
    {
        rdev[i]->data = sdisk[i]; 
        rdev[i]->gd = alloc_disk(RAMHD_MAX_PARTITIONS);
        spin_lock_init(&rdev[i]->lock);  //��ʼ��������
        rdev[i]->queue = blk_init_queue(ramhd_req_func, &rdev[i]->lock);//��ʼ����ramhd_req_func��������а�
        rdev[i]->gd->major = ramhd_major; 
        rdev[i]->gd->first_minor = i * RAMHD_MAX_PARTITIONS;
        rdev[i]->gd->fops = &ramhd_fops;  //����������豸�ķ�������
        rdev[i]->gd->queue = rdev[i]->queue;
        rdev[i]->gd->private_data = rdev[i]; //ʹ�������Ա��ָ����������
        sprintf(rdev[i]->gd->disk_name, "video_ram%d", i);
        //set_capacity(rdev[i]->gd, RAMHD_SECTOR_TOTAL);
        set_capacity(rdev[i]->gd, disk_size/RAMHD_SECTOR_SIZE);
        add_disk(rdev[i]->gd);   //��ϵͳ�����������豸
    }
        
    return 0;
}

void ramhd_exit(void)  //ģ��ж�غ���
{
    int i;
    for(i = 0; i < RAMHD_MAX_DEVICE; i++)
    {
        del_gendisk(rdev[i]->gd); //ɾ��gendisk�ṹ��   
        put_disk(rdev[i]->gd);   //����gendisk�ṹ������ü���
        blk_cleanup_queue(rdev[i]->queue);  //����������
    }
    unregister_blkdev(ramhd_major,RAMHD_NAME); ; //ע�����豸 
    clean_ramdev();
    ramhd_space_clean();  
}

module_init(ramhd_init);
module_exit(ramhd_exit);


MODULE_AUTHOR("lyl");
MODULE_DESCRIPTION("The Ramdisk implementation with request function");
MODULE_LICENSE("GPL");
