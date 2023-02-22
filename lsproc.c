#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


// thinking with project 0A

int main() {
    DIR *dir;
    struct dirent *entry;
    char path[6969], cmdline[6969];

  
    dir = opendir("/proc");

    if (dir) {
    
        while ((entry = readdir(dir)) != NULL) {
           
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
              
                sprintf(path, "/proc/%s/cmdline", entry->d_name);

          
                FILE *fp = fopen(path, "r");
                if (fp) {
                
                    fgets(cmdline, sizeof(cmdline), fp);
                    fclose(fp);

                    
                    printf("%s: %s\n", entry->d_name, cmdline);
                }
            }
        }
        closedir(dir);
    }

    return 0;
}
