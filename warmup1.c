#include <stdio.h>
#include <dirent.h>
#include<string.h>
#include <unistd.h>
#include <stdlib.h>


#define size = 1000

// using  /proc/cpuinfo

int main(int argc, char *argv[]){

    FILE *fp;
    char line_size[size];

    int Cpus;
    int cache;

    fp=fopen("/proc/cpuinfo", "r");


    if (fp ==NULL){
        fprintf(stderr,"Can not open /proc/self");
        return 1;

    }

while(fgets(line_size,size,fp)!=NULL){
    if(strstr(line_size, "the processor:")!=NULL){
        Cpus++;
        }
    }

}