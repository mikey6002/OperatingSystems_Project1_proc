#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include<sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include<errno.h>
#include <sys/stat.h>


//decalre functions
    void getProcessList();
    void parseStat(int pid);
    void parseStatm(int pid);


//global variables
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
    while((option=getopt(argc,argv,"sUSvcp:"))!=-1){
        switch(option){
            case 'p':
                pid=atoi(optarg);
                printf("-p %d\n", pid);
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

if(pid ==0){
    user = getenv("USER");
    getProcessList(user);
}else{
    
}
return 0;
}

void getProcessList() {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    //Open the /proc directory
    dir = opendir("/proc");
    if(dir == NULL) {
        perror("opendir");
        exit(-1);
    }
    //Loop through all the entries in the /proc directory
    while((entry = readdir(dir)) != NULL) {
        //Ignore all entries which are not directories and don't match the specified criteria
        if(entry->d_type == DT_DIR) {
            char *endptr;
            long pid = strtol(entry->d_name, &endptr, 10);
        if(pid > 0 && *endptr == '\0') {
            //Concatenate the path of the entry to the /proc directory
            char pathline[1024];
            strcpy(pathline, "/proc/");
            strcat(pathline, entry->d_name);
            //Get the status of the entry
        if(stat(pathline, &statbuf) == -1) {
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
    closedir(dir);
}

// modified from the reading https://mentorembedded.github.io/advancedlinuxprogramming/alp-folder/alp-ch07-proc-filesystem.pdf
void parseStat(int pid){
    char statFile[6969];
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char state;
    unsigned long utime, stime, cutime, cstime;
    

    sprintf(statFile, "/proc/%d/stat", pid);
    FILE *fp = fopen(statFile,"r");

    if(!fp){
        perror("Failed to open file");
        exit(1);
    }

    if((read = getline(&line, &len, fp)) == -1) {
        perror("getline error");
        exit(-1);
    }

    //https://www.gnu.org/gnu/gnu.html
    if(sscanf(line, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %lu %lu %lu", &state, &utime, &stime, &cutime, &cstime) != 5) {
        fprintf(stderr, "Error: Failed to parse %s\n", statFile);
        exit(-1);
    }

    printf("%d\t %c\t", pid, state);

    if(UFlag == 1) {
        printf("%lu\t", utime);
    }
    if(SFlag == 1) {
        printf("%lu\t", stime);
    }

    if(vFlag == 1) {
        printf("%lu\t", cutime+cstime);
    }

    free(line);
    fclose(fp);
}

void parseStatm(int pid) {
    char statmFile[6969];
    int size;
    char cmdlineFile[6969];
    char *cmdline = NULL;
    size_t len = 0;
    ssize_t read;
    //Open the statm file
    sprintf(statmFile, "/proc/%d/statm", pid);
    FILE *fp = fopen(statmFile, "r");
    if(fp == NULL) {
        perror("open");
        exit(-1);
    }
    //Parse the file
    if(fscanf(fp, "%d", &size) != 1) {
        fprintf(stderr, "Error: Failed to parse %s\n", statmFile);
        exit(-1);
    }
    //Print the output
    if(vFlag == 1) {
        printf("%d\t", size);
    }
    if(cFlag == 1) {
        sprintf(cmdlineFile, "/proc/%d/cmdline", pid);
        FILE *fp_cmdline = fopen(cmdlineFile, "r");
        if(fp_cmdline == NULL) {
            perror("open");
            exit(-1);
        }
        if((read = getline(&cmdline, &len, fp_cmdline)) != -1) {
            printf("%s\t", cmdline);
        } else {
            printf("\t");
        }
        free(cmdline);
        fclose(fp_cmdline);
    }
    printf("\n");
    fclose(fp);
}











