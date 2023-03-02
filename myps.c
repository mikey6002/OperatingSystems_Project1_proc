#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include<sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

    char *user;
    int pid;
    int sFlag = 0;
    int UFlag = 1;
    int SFlag = 0;
    int vFlag = 0;
    int cFlag = 1;



int main(int argc, char *argv[]){

    int option;
    
    //https://linux.die.net/man/3/optarg
    while((option=getopt(argc,argv,"sUSvcp:"))!=1){
        switch(option){
            case 'p':
                pid=atoi(optarg);
                break;
                
            case 's':
                sFlag = 1;
                break;
            
            case 'U':
              UFlag = 0;
                 break;

            case 'S':
                SFlag = 1;
                break;
        
            case 'v':
                vFlag = 1;
                break;

            case 'c':
                  cFlag = 0;
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


if(pid ==0){
    user = getenv("USER");
    getProcessList(user);
}else{
    
}
return 0;
}

void getProcessList(){
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    dir = opendir("/proc");
    char path[6969], cmdline[6969], *endptr;
    long process_id;



      if (!dir) {
        perror("Failed to open directory /proc");
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL) {
        if(entry->d_type != DT_DIR) {
            long pid = strtol(entry->d_name, &endptr, 10);
        if(pid > 0 && *endptr == '\0') {
            //Concatenate the path of the entry to the /proc directory
            char path[1024];
            strcpy(path, "/proc/");
            strcat(path, entry->d_name);
            //Get the status of the entry
            if(stat(path, &statbuf) == -1) {
            perror("stat");
            exit(-1);
            }
            //Check if the entry is owned by the current user
            if(statbuf.st_uid == getuid()) {
                parseStat(pid);
                parseStatm(pid);
                }   
            }
        }
    }
    close(dir);
}



void parseStat(int pid){
    FILE *fp;
    char statFile[1024];
    char state;
    int utime;
    int stime;


sprintf(statFile, "/proc/%d/stat", pid);
    FILE *fp = fopen(statFile,"r");

    if(!fp){
        perror("Failed to open file");
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