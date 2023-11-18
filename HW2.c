#define _POSIX_C_SOURCE 200112L //the functionality from the 2001 edition of the POSIX standard (IEEE Standard 1003.1-2001) is made available.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define DEBUG 0
#define MAX_LEN 1024


void dealDefultAddr(char *cwd, char *username){

    char DefultAddr[MAX_LEN] = "/home/";
    strcat(DefultAddr, username);
    
    if(strcmp(DefultAddr, cwd) == 0){
        strcpy(cwd, "~");
    }

    return;
}

void prompt(){
    
    char *username;
    char hostname[MAX_LEN];
    char cwd[MAX_LEN];
    
    username = getenv("LOGNAME");
    gethostname(hostname, sizeof(hostname));
    getcwd(cwd, sizeof(cwd));

    dealDefultAddr(cwd, username);
    printf("%s@%s:%s$", username, hostname, cwd);

    return;
}

void removeHeadSpace( char *cmd ){

    char *ptr = cmd;
    while(isspace(*ptr)){
        ptr++;
    }
    memmove(cmd,ptr,sizeof(ptr)+1);

}

int main() {
    
    char cmd[MAX_LEN];
    char cmd_arg[MAX_LEN];
    while(1){

        prompt();
        scanf("%s",cmd);

        if(strncmp(cmd, "exit", 4)==0){

            break;

        } else if(strncmp(cmd, "pwd", 3)==0){

            char cwd[MAX_LEN];
            getcwd(cwd, sizeof(cwd));
            printf("%s\n", cwd);

        }else if(strncmp(cmd, "cd",2)==0) {

            scanf("%s",cmd_arg);
            if(strncmp(cmd_arg, "/", 1)==0){
                if (chdir(cmd_arg) != 0) {
                    printf("cd: %s: No such file or directory\n", cmd);
                    }
            }

        } else if(strncmp(cmd, "export", 6)==0){

        } else if(strncmp(cmd, "echo", 4)==0){

        }
        strcpy(cmd,"");
        strcpy(cmd_arg,"");
    }

    return 0;
}