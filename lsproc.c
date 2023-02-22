#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// thinking with code from project 0A

int main(){

DIR *dir;

struct dirent *entry;

char path [69];
char pid [69];
char cmd [69];


dir = opendir("/proc");
 
 if(dir){
     while(entry != NULL){
    if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && atoi(entry->d_name) != 0) {
        printf(path, "/proc/%s/cmdline", entry->d_name);

                FILE *fp = fopen(path, "r");
                if (fp) {
                   
                    fgets(cmd, sizeof(cmd), fp);
                    fclose(fp);

                    printf("%s: %s\n",  entry->d_name, cmd);
                }
        }
     }

        closedir(dir);
    }
    return 0;
}
