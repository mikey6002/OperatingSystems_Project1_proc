#include <stdio.h>
#include <dirent.h>
#include<string.h>
#include <unistd.h>
#include <stdlib.h>


#define size = 1000






int main(int argc, char *argv[]){

    FILE *fp;
    char line [size];

    fp=fopen("/proc/cpuinfo", "r");


    if (fp ==NULL){
        fprintf(stderr,"Can not open /proc/self");
        return 1;

    }

}