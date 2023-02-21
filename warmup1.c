#include <stdio.h>
#include <dirent.h>
#include<string.h>
#include <unistd.h>
#include <stdlib.h>



// using  /proc/cpuinfo

int main(void){

    //https://www.gnu.org/software/libc/manual/html_node/Processor-Resources.html
    //determines num of processors
    long numOf_Processorss = sysconf(_SC_NPROCESSORS_ONLN);
    printf("num of processors %ld\n",numOf_Processorss);

    // opens file that has cpu info 
    FILE *fp;
    char line_size;
     fp=fopen("/proc/cpuinfo", "r");

   
   

    if (fp ==NULL){
        fprintf(stderr,"Can not open /proc/self");
        return 1;

    }
    // read cpuinfo line by line and loof for cache size 
    char* size =NULL;
    size_t length = 0;
    ssize_t read;
    int cache_size=-1;

//www.ibm.com/docs/en/zos/2.1.0?topic=functions-read-read-from-file-socket
// And idea by TA
while ((read = getline(&size, &length, fp)) != -1) {
        if (sscanf(size, "cache size : %d", &cache_size) == 1) {
            printf("Cache size: %d kB\n", cache_size);
        }
    }

    free(size);
    fclose(fp);

    return 0;
}
