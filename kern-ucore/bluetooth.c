#include <arch.h>
#include <trap.h>
#include <stdio.h>
#include <picirq.h>
#include <sched.h>
#include <asm/mipsregs.h>

int bluetooth_int_handler(void *data)
{
    kprintf("ke yi ma\n\r");
    return 0;
}

void bluetooth_init()
{
    *WRITE_IO(BT_UART_BASE + lcr) = 0X00000080; // LCR[7] is 1
    delay();
    *WRITE_IO(BT_UART_BASE + dll) = 69;
    delay();
    *WRITE_IO(BT_UART_BASE + dlm) = 0X00000001;
    delay();
    *WRITE_IO(BT_UART_BASE + lcr) = 0X00000003;
    delay();
    *WRITE_IO(BT_UART_BASE + ier) = 0X00000001;
    delay();
    pic_enable(BT_IRQ);
}

char BT_uart_inbyte(void)
{
    unsigned int RecievedByte;
    while((*READ_IO(BT_UART_BASE + lsr) & 0x00000001) != 0x00000001){
        delay();
    }
    RecievedByte = *READ_IO(BT_UART_BASE + rbr);
    return (char)RecievedByte;
}