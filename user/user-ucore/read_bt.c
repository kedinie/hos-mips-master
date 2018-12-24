#include <ulib.h>
#include <stdio.h>
#include <string.h>
#include <dir.h>
#include <file.h>
#include <stat.h>
#include <dirent.h>
#include <unistd.h>

#define printf(...)                     fprintf(1, __VA_ARGS__)
#define bt_size 258

void delay(void)
{
    unsigned int j = 0;
    while(j < 1000000) j = j + 1;
    // for (j = 0; j < (); j++) ; // delay
}

int main(){
    while(1){
        int res = read_bt();
        if(res != 0){
            int x = 0;
            int y = 0;
            x = res >> 16;
            y = res << 16;
            y = y >> 16;
            printf("-------------(x, y) (%d, %d)\n\r", x, y);
        }
        else printf("there is no data output!\n\r");
        sleep(30);
    }
    return 0;
   /*  uint32_t  bt_data[bt_size];
    bt_data[0] = 0;
    bt_data[1] = 0; */
    // bt_data[2] = 4555;
    // printf("outside address is %x\n\r", bt_data);
    // read_bt();
    // printf("after read_bt bt_data[0] is %d\n\r", bt_data[0]);
   /*  uint32_t i = 0;
    while(i < 200){
        int front = bt_data[0];
        int back = bt_data[1];
        printf("out %u\n\r", i);
        if(front != back){
            // printf("in\n\r");
            uint32_t x = 0;
            uint32_t y = 0;
            x = bt_data[front] >> 16;
            y = (bt_data[front] << 16) >> 16;
            printf("x = %d, y = %d\n\r", x, y);
            bt_data[0] = (front + 1) % (bt_size -2);
        }
        i = i + 1;
        sleep(30);
    }
    i = 0;
    while(i < bt_size){
        printf("%u\n\r", bt_data[i++]);
    } */
    // printf("read is over\n\r");
    // read_bt();
    // printf("read_bt is wrong?\n\r");
}