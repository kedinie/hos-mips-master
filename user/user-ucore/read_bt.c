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
    int a=0;
    while(1){
        a = read_bt();
        if(a != 0)printf("uint32_t is %d\n\r", a);
    }
    return 0;
}