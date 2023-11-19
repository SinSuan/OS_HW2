#define _POSIX_C_SOURCE 200112L //the functionality from the 2001 edition of the POSIX standard (IEEE Standard 1003.1-2001) is made available.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1024

char *username;
char hostname[MAX_LEN] = "";
char DefultAddr[MAX_LEN] = "/home/";
int DefultAddr_len;

void init(){
    username = getenv("LOGNAME");
    gethostname(hostname, sizeof(hostname));
    strcat(DefultAddr, username);
    DefultAddr_len = strlen(DefultAddr);
    return;
}


void dealDefultAddr(char *cwd){

    char ptr[MAX_LEN] = "";     //不init的話，好像會記錄到其他東西
    int cwd_len = strlen(cwd);
    
    if(strncmp(DefultAddr, cwd, DefultAddr_len) == 0){
        memcpy(ptr,cwd+DefultAddr_len,cwd_len-DefultAddr_len);
        strcpy(cwd, "~");
        strcat(cwd, ptr);
    }
    
    return;
}

void prompt(){
    
    char cwd[MAX_LEN] = "";
    getcwd(cwd, sizeof(cwd));

    dealDefultAddr(cwd);
    printf("%s@%s:%s$ ", username, hostname, cwd);

    return;
}

void getAbsolutePath(char *cmd_arg){
    
    char cwd[MAX_LEN] = "";
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/");
    strcat(cwd, cmd_arg);
    strcpy(cmd_arg, cwd);

    return;
}

int main() {

    init();
    
    char cmd[MAX_LEN] = "";
    char cmd_arg[MAX_LEN] = "";
    while(1){

        prompt();
        scanf("%s",cmd);

        if(strcmp(cmd, "exit")==0){
            break;
        } else if(strcmp(cmd, "pwd")==0){

            char cwd[MAX_LEN] = "";
            getcwd(cwd, sizeof(cwd));
            printf("%s\n", cwd);

        } else if(strcmp(cmd, "cd")==0) {

            scanf("%s",cmd_arg);
            if(strncmp(cmd_arg, "/", 1)!=0){
                getAbsolutePath(cmd_arg);
            }
            if (chdir(cmd_arg) != 0) {
                printf("cd: %s: No such file or directory\n", cmd_arg);
            }

        } else if(strcmp(cmd, "export")==0){

        } else if(strcmp(cmd, "echo")==0){
            scanf("%s",cmd_arg);
            printf("%s\n",cmd_arg);
        } else {
            printf("%s is not supported\n", cmd);
        }
    }

    return 0;
}