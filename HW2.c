#define _POSIX_C_SOURCE 200112L //the functionality from the 2001 edition of the POSIX standard (IEEE Standard 1003.1-2001) is made available.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

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
    if(strncmp(cmd_arg, "/", 1)!=0){
        char cwd[MAX_LEN] = "";
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        strcat(cwd, cmd_arg);
        strcpy(cmd_arg, cwd);
    }
    return;
}

void getVar( char *cmd_arg){
    if(cmd_arg != NULL && strncmp(cmd_arg, "$", 1)==0){
        //把 "$" 去掉, 並取出該變數代表的值
        char temp[MAX_LEN]="";
        char var[MAX_LEN]="";
        strcpy(temp, cmd_arg+1);
        strcpy(cmd_arg, temp);
        if(getenv(cmd_arg)!=NULL){
            strcpy(var, getenv(cmd_arg));
        }
        strcpy(cmd_arg, var);
    }
    return;
}

void changeUnixVar(char *cmd_arg){
    char temp[MAX_LEN]="";
    char *var;
    char var_name[MAX_LEN]="";
    char var_value[MAX_LEN]="";
    char add_value[MAX_LEN]="";

    if( cmd_arg != NULL){
        strcpy(temp, cmd_arg);
    }
    var = strtok(temp, "=");
    if( var != NULL){
        strcpy(var_name, var);
    }
    var = strtok(NULL, ":");
    if( var != NULL){
        strcpy(var_value, var);
    }
    var = strtok(NULL, "\0");
    if( var != NULL){
        strcpy(add_value, var);
    }

    if( strcmp(var_name, "")!=0 && strchr(cmd_arg, '=') != NULL){
        getVar(var_value);
        if(strchr(cmd_arg, ':') != NULL){
            strcat(var_value, ":");
            strcat(var_value, add_value);
        }
        setenv(var_name, var_value, 1);
    }
    return;
}

void external_command(char *cmd_ttl){
    if(fork()==0){
        char *args[MAX_LEN];
        int i=0;
        args[0] = strtok(cmd_ttl, " \n");
        while(args[i++]!=NULL && i<10 ){
            args[i]=strtok(NULL, " ");
        }

        execvp(args[0], args);
    } else {
        wait(NULL); 
    }
    return;
}

int main() {

    init();
    
    char cmd_ttl[MAX_LEN];
    char cmd[MAX_LEN];
    char cmd_arg[MAX_LEN];
    char temp[MAX_LEN];
    char *token;
    while(1){
        strcpy(cmd_ttl,"");
        strcpy(cmd,"");
        strcpy(cmd_arg,"");
        strcpy(temp,"");
        
        prompt();
        fgets(cmd_ttl, MAX_LEN, stdin);
        cmd_ttl[strcspn(cmd_ttl, "\n")]='\0';
        if(cmd_ttl!=NULL){
            strcpy(temp, cmd_ttl);
        }

        token = strtok(temp, " ");
        if(token!=NULL){
            strcpy(cmd, token);
        }
        token = strtok(NULL, "\0");
        if(token!=NULL){
            strcpy(cmd_arg, token);
        }

        if(strcmp(cmd, "exit")==0){
            break;
        } else if(strcmp(cmd, "pwd")==0){
            char cwd[MAX_LEN] = "";
            getcwd(cwd, sizeof(cwd));
            printf("%s\n", cwd);
        } else if(strcmp(cmd, "cd")==0) {
            getAbsolutePath(cmd_arg);
            if (chdir(cmd_arg) != 0) {
                printf("cd: %s: No such file or directory\n", cmd_arg);
            }
        } else if(strcmp(cmd, "export")==0){
            changeUnixVar(cmd_arg);
        } else if(strcmp(cmd, "echo")==0){
            getVar(cmd_arg);
            printf("%s\n",cmd_arg);
        } else {
            external_command(cmd_ttl);
        }
    }
    return 0;
}