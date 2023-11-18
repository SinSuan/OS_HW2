#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DEBUG 0
#define MAX_LEN 1024


void isDefultAddr(char *cwd, char *username){

    char DefultAddr[MAX_LEN] = "/home/";
    strcat(DefultAddr, username);
    int n = strcmp(DefultAddr, cwd);

    if( n == 0){
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

int main() {
    
    while(1){
        prompt();
        char cmd[MAX_LEN];
        fgets(cmd, sizeof(cmd), stdin);
    }

    return 0;
}