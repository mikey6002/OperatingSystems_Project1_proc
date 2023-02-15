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

   
    fp=fopen("/proc/cpuinfo", "r");

    if (fp ==NULL){
        fprintf(stderr,"Can not open /proc/self");
        return 1;

    }

     int Cpus=0;
    int cache=0;

while(fgets(line_size,size,fp)!=NULL){
    if(strstr(line_size, "the processor:")!=NULL){
        Cpus++;
        }else if (strstr(size, "cache size") != NULL) {
            sscanf(size, "%*s %*s %d", &cache);
            printf("CPU%d cache size: %d KB\n", Cpus, cache);
        }
    }

    fclose(fp);

}
