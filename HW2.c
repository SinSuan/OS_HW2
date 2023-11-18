#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define DEBUG 0
#define MAX_LEN 1024


void isDefultAddr(char *cwd, char *username){

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

    isDefultAddr(cwd, username);
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

void determineWork( char *cmd ){

    removeHeadSpace(cmd);

    if(strncmp(cmd, "export", 6)==0){

    } else if(strncmp(cmd, "echo", 4)==0){

    } else if(strncmp(cmd, "pwd", 3)==0){
        char cwd[MAX_LEN];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
    } else if(strncmp(cmd, "cd",2)==0) {

    }

    return;
}

int main() {
    
    while(1){
        prompt();
        char cmd[MAX_LEN];
        fgets(cmd, sizeof(cmd), stdin);
        determineWork(cmd);
    }

    return 0;
}