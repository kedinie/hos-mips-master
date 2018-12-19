#include <ulib.h>
#include <stdio.h>
#include <string.h>
#include <dir.h>
#include <file.h>
#include <stat.h>
#include <dirent.h>
#include <unistd.h>

#define printf(...)                     fprintf(1, __VA_ARGS__)

int main(){
    int spd = 9;
    int stat = 0x2e;
    char c;
    char buf[100];
    const char *bt_path = "/dev/bluetooth";
    printf("Will open: %s\r\n", bt_path);
    int fd_bt = open(bt_path, O_RDONLY);
    if(fd_bt < 0){
        printf("failed to open bt_path\r\n");
        return fd_bt;
    }
}