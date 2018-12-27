#ifndef __KERN_DRIVER_BLUETOOTH_H__
#define __KERN_DRIVER_BLUETOOTH_H__

#include <defs.h>

#define command_size 30
#define bt_size 256
#define bt_max_size 258

uint32_t bt_data[2];
char bt_command[command_size];
int pos;
// uint32_t *p_bt;
// struct bt_data{
//     uint32_t data;
//     struct bt_data* next;
// };

// struct bt_data* head;

void bluetooth_init(void);
char BT_uart_inbyte(void);
int bluetooth_int_handler(void *data);

#endif /* !__KERN_DRIVER_BLUETOOTH_H__ */
