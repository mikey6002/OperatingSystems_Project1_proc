#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


// thinking with project 0A to get process list 

int main() {
    DIR *dir;
    struct dirent *entry;
    char path[6969], cmdline[6969],*endptr;

   \
    long pid;
  
  
    dir = opendir("/proc");

    printf("\n" "PID", "TTY", "TIME", "CMD");

    
    
        while ((entry = readdir(dir)) != NULL) {
            // if the entry is a directory it will open the read the subfolder
        // "borrowed" and inpired by https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-opendir-open-director
            if (entry->d_type == DT_DIR && (pid = strtol(entry->d_name, &endptr, 10)) > 0 && *endptr == '\0') {
              
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
    

    return 0;
}
