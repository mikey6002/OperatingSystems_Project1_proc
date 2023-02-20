#include <stdio.h>
#include <dirent.h>
#include<string.h>
#include <unistd.h>



int main(void){

    FILE *fp;
    fp = fopen("/proc/meminfo","r");

if(fp ==NULL){
    printf("There has been a error with meminfo");
    return 1;
}
char arrays [300];

unsigned long mem_total = 0; 
unsigned long mem_free = 0; 
unsigned long buffers = 0;

while(fgets(arrays,sizeof(arrays),fp)!=NULL){
    if(sscanf(arrays,"Memory total: %lu kB", &mem_total)==1){
        //total memory size 
    }else if(sscanf(arrays,"Memory Free: %lu kB", &mem_free)==1){
        } else if(sscanf(arrays,"Buffers : %lu kB", &buffers)==1){

        }
    }
    fclose(fp);

    printf("Total memory: %lu kB\n", mem_total);
    printf("Free memory: %lu kB\n", mem_free);
    printf("Buffers: %lu kB\n", buffers);

    return 0;
}