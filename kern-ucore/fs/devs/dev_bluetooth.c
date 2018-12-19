#include <types.h>
#include <dev.h>
#include <vfs.h>
#include <iobuf.h>
#include <inode.h>
#include <error.h>
#include <assert.h>
#include <arch.h>

void delay(void)
{
    volatile unsigned int j;
    for (j = 0; j < (500); j++) ; // delay
}

static int bluetooth_open(struct device *dev, uint32_t open_flags)
{
    if (open_flags & (O_CREAT | O_TRUNC | O_EXCL | O_APPEND)) {
		return -E_INVAL;
	}
	struct device *dev = vop_info(node, device);
	return dop_open(dev, open_flags);
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

static void bluetooth_device_init(struct device *dev)
{
	memset(dev, 0, sizeof(*dev));
	dev->d_blocks = 0;
	dev->d_blocksize = 1;
	dev->d_open = bluetooth_open;
	dev->d_close = bluetooth_close;
	dev->d_io = bluetooth_io;
	dev->d_ioctl = bluetooth_ioctl;
}

void dev_init_bluetooth(void){
    // *WRITE_IO(BT_UART_BASE + lcr) = 0X00000080; // LCR[7] is 1
    // delay();
    // *WRITE_IO(BT_UART_BASE + dll) = 69;
    // delay();
    // *WRITE_IO(BT_UART_BASE + dlm) = 0X00000001;
    // delay();
    // *WRITE_IO(BT_UART_BASE + lcr) = 0X00000003;
    // delay();
    // *WRITE_IO(BT_UART_BASE + ier) = 0X00000001;
    // delay();
	struct inode *node;
	if ((node = dev_create_inode()) == NULL) {
		panic("bluetooth: dev_create_node.\n");
	}
	null_device_init(vop_info(node, device));

	int ret;
	if ((ret = vfs_add_dev("bluetooth", node, 0)) != 0) {
		panic("bluetooth: vfs_add_dev: %e.\n", ret);
	}
}


// char BT_uart_inbyte(void){
//     unsigned int RecievedByte;
//     while((*READ_IO(BT_UART_BASE + lsr) & 0x00000001) != 0x00000001){
//         delay();
//     }
//     RecievedByte = *READ_IO(BT_UART_BASE + rbr);
//     return (char)RecievedByte;
// }