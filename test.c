#define _POSIX_C_SOURCE 200112L //the functionality from the 2001 edition of the POSIX standard (IEEE Standard 1003.1-2001) is made available.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1024

#define DEBUG 1
#define IS_DEFUALT_ADDR 1
#define PROMPT 1
#define REMOVEHEADSPACE 1
#define DETERMINEWORK 1
#define MAIN 1



void isDefultAddr(char *cwd, char *username){
    #if DEBUG
        printf("enter isDefultAddr\n");
    #endif

    char DefultAddr[MAX_LEN] = "/home/";

    
    strcat(DefultAddr, username);
    int n = strcmp(DefultAddr, cwd);

    #if IS_DEFUALT_ADDR
        printf("DefultAddr=%s\ncwd=%s\nn=%d\n",DefultAddr,cwd,n);
    #endif

    if( n == 0){
        strcpy(cwd, "~");
    }

    #if IS_DEFUALT_ADDR
        printf("DefultAddr=%s\ncwd=%s\nn=%d\n",DefultAddr,cwd,n);
    #endif

    #if DEBUG
        printf("exit isDefultAddr\n");
    #endif 
    return;
}

void prompt(){

    #if DEBUG
        printf("enter prompt\n");
    #endif
    
    char *username;
    char hostname[MAX_LEN];
    char cwd[MAX_LEN];
    
    username = getenv("LOGNAME");
    gethostname(hostname, sizeof(hostname));
    getcwd(cwd, sizeof(cwd));

    #if PROMPT
        printf("%s@%s:%s$\n", username, hostname, cwd);
    #endif

    isDefultAddr(cwd, username);

    #if DEBUG
        printf("exit prompt\n");
    #endif

    printf("%s@%s:%s$", username, hostname, cwd);
    return;
}

void removeHeadSpace( char *cmd ){

    #if DEBUG
        printf("enter removeHeadSpace\n");
    #endif

    char *ptr = cmd;
    
    #if REMOVEHEADSPACE
        printf("ptr=%s\n",ptr);
    #endif

    while(isspace(*ptr)){
        ptr++;
        
        #if REMOVEHEADSPACE
            printf("ptr=%s\n",ptr);
        #endif
    }
    // memmove(cmd,ptr,strlen(ptr));
    strcpy(cmd,ptr);

    #if DEBUG
        printf("exit removeHeadSpace\n");
    #endif

    return;

}

void determineWork( char *cmd ){

    #if DEBUG
        printf("enter determineWork\n");
    #endif

    #if DETERMINEWORK
        printf("%s",cmd);
    #endif

    if(       strncmp(cmd, "export", 6)==0){

    } else if(strncmp(cmd, "echo", 4)==0){

    } else if(strncmp(cmd, "pwd", 3)==0){
        char cwd[MAX_LEN];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
    } else if(strncmp(cmd, "cd",2)==0) {
        // memmove(cmd,cmd+2,strlen(cmd));
        cmd[strlen(cmd)]='\0';
        strcpy(cmd,cmd+2);
        if(strncmp(cmd, " ", 1)){
            printf("can't recognize\n");
        } else {
            removeHeadSpace(cmd);
            #if DETERMINEWORK
                printf("removeHeadSpace(cmd)=%s\n",cmd);
                printf("strncmp(cmd, '/', 1)=%d\n",strncmp(cmd, "/", 1));
            #endif
            if(strncmp(cmd, "/", 1)==0){
                
                #if DETERMINEWORK
                    printf("check first / in cmd=%s\n",cmd);
                    printf("chdir(cmd)=%d\n",chdir(cmd));
                #endif
                if (chdir(cmd) != 0) {
                    printf("cd: %s: No such file or directory\n", cmd);
                    }
            }
        }
    }
        

    #if DEBUG
        printf("exit determineWork\n");
    #endif

    return;
}

int main() {
    char cmd[MAX_LEN];
    while(1){

        #if MAIN
            printf("beginning of loop\n");
        #endif

        prompt();
        fgets(cmd, sizeof(cmd), stdin);
        removeHeadSpace(cmd);

        #if MAIN
            printf("%s\n",cmd);
        #endif

        if(strncmp(cmd, "exit", 4)==0){

            #if MAIN
                printf("%s","enter if\n");
            #endif

            break;
        } else {
            #if MAIN
                printf("%s","enter else\n");
            #endif
            
            determineWork(cmd);

            #if MAIN
                printf("%s","exit else\n");
            #endif
        }        

    strcpy(cmd,"");
    #if MAIN
        printf("end of loop\n\n");
    #endif
        
    }

    // // int a = strcmp("123", "125");

    // char *s1 = "abc";
    // char *s2 = "ab3";
    // // int a = strcmp(s1, s2);

    // // printf("%.*s\n", 2, s1 + 1);

    // printf("%d",strncmp(s1, "ab",2));

    return 0;
}