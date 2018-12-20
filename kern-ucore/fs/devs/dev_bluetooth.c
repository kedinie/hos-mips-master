#include <types.h>
#include <string.h>
#include <stat.h>
#include <dev.h>
#include <inode.h>
#include <unistd.h>
#include <error.h>


// void delay(void)
// {
//     volatile unsigned int j;
//     for (j = 0; j < (500); j++) ; // delay
// }

static int bluetooth_open(struct inode *node, uint32_t open_flags)
{
    if (open_flags & (O_CREAT | O_TRUNC | O_EXCL | O_APPEND)) {
		return -E_INVAL;
	}
	struct device *dev = vop_info(node, device);
	return dop_open(dev, open_flags);
	return 0;
}

static int bluetooth_close(struct device *dev)
{
	return 0;
}

static int bluetooth_io(struct device *dev, struct iobuf *iob, bool write)
{	
    return 0;
}

static int bluetooth_ioctl(struct device *dev, int op, void *data)
{
	return 0;
}


void dev_init_bluetooth(void)
{
	// struct inode *node;
	// if ((node = dev_create_inode()) == NULL) {
	// 	panic("bluetooth: dev_create_node.\n");
	// }
	// null_device_init(vop_info(node, device));

	// int ret;
	// if ((ret = vfs_add_dev("bluetooth", node, 0)) != 0) {
	// 	panic("bluetooth: vfs_add_dev: %e.\n", ret);
	// }
}


// char BT_uart_inbyte(void){
//     unsigned int RecievedByte;
//     while((*READ_IO(BT_UART_BASE + lsr) & 0x00000001) != 0x00000001){
//         delay();
//     }
//     RecievedByte = *READ_IO(BT_UART_BASE + rbr);
//     return (char)RecievedByte;
// }