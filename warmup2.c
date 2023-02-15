#include <stdio.h>
#include <dirent.h>
#include<string.h>
#include <unistd.h>





int main(int argc, char *argv[]){

    FILE *fp;
    fp = fopen("/proc/meminfo","r");

if(fp ==NULL){
    fprintf("There has been a error with meminfo");
    return 1;
}
char arrays [300];
unsigned long mem_total = 0, mem_free = 0, buffers = 0;


}