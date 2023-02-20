#include <stdio.h>
#include <dirent.h>
#include<string.h>
#include <unistd.h>



int main(int argc, char *argv[]){

    FILE *fp;
    fp = fopen("/proc/meminfo","r");

if(fp ==NULL){
    fprintf("There has been a error with meminfo");
    eixt(1);
}
char arrays [300];

unsigned long mem_total = 0; 
unsigned long mem_free = 0; 
unsigned long buffers = 0;

while(fgets(arrays,sizeof(arrays),fp)!=NULL){

}


}