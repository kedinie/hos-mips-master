#include <arch.h>
#include <trap.h>
#include <stdio.h>
#include <picirq.h>
#include <sched.h>
#include <asm/mipsregs.h>
#include <bluetooth.h>
#include <pmm.h>

int atoi(char *str)
{
        if(!str)
                return -1;
        bool bMinus=0;
        int result=0;
 
        if(('0'>*str || *str>'9')&&(*str=='+'||*str=='-'))
        {
               if(*str=='-')
                bMinus=1;
               *str++;
        }
        while( *str != '\0')
        {
                if('0'> *str || *str>'9')
                        break;
                else
                        result = result*10+(*str++ - '0');
        }
 
        if (*str != '\0')//no-normal end
                return -2;
 
        return bMinus?-result:result;
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

int bluetooth_int_handler(void *data)
{
    // kprintf("read a char from bluetooth\n\r");
    char c = BT_uart_inbyte(); 
    int x = 0, y = 0;
    // kprintf("the char recieved from bluetooth is %c\n\r", c);
    if(c == ';'){
        if(pos > 2){
            int tpos = 0, yn = 0;
            int i = 0;
            while(i < pos){
                if(bt_command[i] == ','){
                    char temp[5];
                    i++;
                    while(i < pos && bt_command[i] != '.'){
                        temp[tpos++] = bt_command[i++];
                    };
                    temp[tpos] = '\0';
                    if(yn == 0) {
                        yn = 1;
                        x = atoi(temp);
                    }
                    else {
                        yn = 0;
                        y = atoi(temp);
                    }
                    tpos = 0;
                }
                else i++;
            }
            uint32_t res = 255;
            res = res & y;
            x = x << 16;
            res = res | x;
            kprintf("recieve char %d\n\r", res);
            if(head == NULL){
                head = (struct bt_data * )kmalloc(sizeof(struct bt_data));
                head->data = res;
                head->next = NULL;
            }
            else {
                struct bt_data * p = head;
                while(p->next)p=p->next;
                p->next = (struct bt_data * )kmalloc(sizeof(struct bt_data));
                p = p->next;
                p->data = res;
                p->next = NULL;
            }
        }
        pos = 0;
    }
    else {
        if(pos == command_size) pos = 0;
        else bt_command[pos++] = c;
    }
    return 0;
}

void bluetooth_init()
{
    head = NULL;
    pos = 0;
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

