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
    // printf("kernel: hello!\n");
    printf("The return of bluetooth is %d\n\r", bluetooth());
    return 0;
}