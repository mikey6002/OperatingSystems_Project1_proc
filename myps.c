#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include<sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>




int main(int argc, char **argv){
    int state =0;
    int user_time=1;
    int option;
    int system_time=1;
    int virtualm =1;
    int pid = -1;
    int command_line =1;
    int display_pid = 0;
    
    //https://linux.die.net/man/3/optarg
    while((option=getopt(argc,argv,"sUSvcp:"))!=1){
        switch(option){
            case 'p':
                display_pid =1;
                pid=atoi(optarg);
                break;
                
            case 's':
                state =1;
                break;
            
            case 'U':
                user_time =0;
                 break;

            case 'S':
                system_time=1;
                break;
        
            case 'v':
                virtualm=1;
                break;

            case 'c':
                command_line =0;
                break;

            case '?':
            default :
                fprintf(stderr, "Usage: %s [-s] [-U] [-S] [-v] [-p pid] \n", argv[0]);
                exit(1);
        }
    }
if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        exit(1);
    }
}






/*
if(dir ==NULL){
    DIR *dir;
    dir = opendir("/proc");
    struct dirent *entry;
    long pid;
    FILE *fp;
    char path[6969], cmdline[6969], *endptr;

    if (!dir) {
        perror("Failed to open directory /proc");
        exit(1);
    }
}

while ((entry = readdir(dir)) != NULL) {
        // Check if the entry is a directory and its name is a number (process ID)
        if (entry->d_type == DT_DIR && (pid = strtol(entry->d_name, &endptr, 10)) > 0 && *endptr == '\0') {
            sprintf(path, "/proc/%ld/status", pid); // Construct the path to the status file
            fp = fopen(path, "r"); // Open the status file
            if (fp) {
                // Read the TTY and CMD information from the status file
                
                //Bryant OHallron Computer Systems
                char tty[20] = "", cmd[1024] = "";
                while (fgets(cmdline, sizeof(cmdline), fp)) {
                    //https://man7.org/linux/man-pages/man4/tty.4.html
                    if (strncmp(cmdline, "Tty:", 4) == 0) {
                        cmdline[strcspn(cmdline, "\n")] = 0; // Remove the newline character
                        sprintf(tty, "%s", cmdline+5);
                    }
                    if (strncmp(cmdline, "Name:", 5) == 0) {
                        cmdline[strcspn(cmdline, "\n")] = 0; // Remove the newline character
                        sprintf(cmd, "%s", cmdline+6);
                    }
                }

                fclose(fp);
                //https://www.ibm.com/docs/en/i/7.3?topic=ssw_ibm_i_73/apis/stat.html
                sprintf(path, "/proc/%ld/stat", pid); // Construct the path to the stat file
                fp = fopen(path, "r"); // Open the stat file
                if (fp) {
                    // Read the process command name and process time information from the stat file
                    char cmdname[1024] = "";
                    unsigned long utime = 0, stime = 0;
                    fscanf(fp, "%ld", &pid);
                    fscanf(fp, " %s", cmdname);
                    fscanf(fp, " %*c"); // skip '('
                    while (fscanf(fp, "%lu %lu", &utime, &stime) == 2) {}
                    fclose(fp);
                    //calculate the CPU usage of a process or device in hours
                    //calculate the CPU usage of a process or device in minutes
                    //calculate the CPU usage of a process or device in seconds
                    printf("%-10ld %-10s %02ld:%02ld:%02ld %-s\n", pid, tty, (utime+stime)/3600, (utime+stime)/60%60, (utime+stime)%60, cmd);
                }
            }
        }
    
    closedir(dir);




    return 0;
}
*/