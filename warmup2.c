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

char *size = NULL;
size_t len = 0;
ssize_t read;
int buffer = 0;

// expects arguement type long long int 
long long mem_free =0;


////www.ibm.com/docs/en/zos/2.1.0?topic=functions-read-read-from-file-socket
 while ((read = getline(&size, &len, fp)) != -1) {
        if (sscanf(size, "Buffers: %d", &buffer) == 1) {
            printf("Number of memory buffers: %d\n", buffer);
        }
       else if (sscanf(size, "MemFree: %lld", &mem_free) == 1) {
            printf("Free memory: %lld kB\n", mem_free);
            break;  
        }
    
    
    }
    free(size);
    fclose(fp);


    return 0;
}