#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

/*------------------------*/

void input_command(int argc, char *argv[], int *port, char *ip);
int parse_input_action();
void input_action(int numTokens, char** saveTokens);

/*------------------------*/


int main(int argc, char *argv[]) {
    int port = 58041;
    char ip[50]; /*getadrrinfo();*/
    input_command(argc, argv, &port, ip);
    printf("ip: %s\n", ip);
    printf("port: %d\n", port);
    while(1){
        parse_input_action();
    }
}

void input_command(int argc, char *argv[], int *port, char *ip) {
    if(argc == 1){
        return;
    }
    else if(argc == 3 && (strcmp(argv[1],"-n") == 0)) {
        strcpy(ip,argv[2]);
    }
    else if(argc == 3 && (strcmp(argv[1],"-p") == 0)) {
        (*port) = atoi(argv[2]);
    }
    else if(argc == 5 && (strcmp(argv[1],"-n") == 0) && (strcmp(argv[3],"-p") == 0)) {
        strcpy(ip, argv[2]);
        (*port) = atoi(argv[4]);
    }
    else{
        fprintf(stderr, "Invalid syntax!\n");
        exit(-1);
    }
}


int parse_input_action() {
    int numTokens = 0;
    char *saveTokens[7];
    char input[50];
    
    if(fgets(input, 50, stdin) == NULL){
        return -1;
    }    
    
    input[strcspn(input, "\n")] = 0; /*remove the \n added by fgets*/
    char *token = strtok(input, " ");

    while(token != NULL) {
        saveTokens[numTokens] = token;
        numTokens++;
        token = strtok(NULL, " ");
    }
    input_action(numTokens, saveTokens);
}

void input_action(int numTokens, char** saveTokens) {

    if((strcmp(saveTokens[0], "register") == 0) || (strcmp(saveTokens[0],"reg") == 0)) {
        printf("register or reg\n");
    }
    else if((strcmp(saveTokens[0],"topic_list") == 0) || (strcmp(saveTokens[0], "tl") == 0)) {
        printf("topic list or tl\n");
    }
    else if((strcmp(saveTokens[0], "topic_propose") == 0) || (strcmp(saveTokens[0], "tp") == 0)){
        printf("topic propose or tp\n");
    }
    else if((strcmp(saveTokens[0], "question_list") == 0) || (strcmp(saveTokens[0], "ql") == 0)){
        printf("question list or ql\n");
    }
    else if((strcmp(saveTokens[0], "question_submit") == 0) || (strcmp(saveTokens[0], "qs") == 0)){
        printf("question submit or qs\n");
    }
    else if((strcmp(saveTokens[0], "answer_submit") == 0) || (strcmp(saveTokens[0], "as") == 0)){
        printf("answer submit\n");
    }
    else if(strcmp(saveTokens[0], "topic_select") == 0){
        printf("topic select\n");    
    }
    else if(strcmp(saveTokens[0], "ts") == 0){
            printf("ts\n");
    }
    else if(strcmp(saveTokens[0], "question_get") == 0){
        printf("question get\n");
    }
    else if(strcmp(saveTokens[0], "qg") == 0){
        printf("qg\n");
    }
    else if(strcmp(saveTokens[0], "exit") == 0){
        exit(0);
    }
    else{
        printf("Invalid syntax!"); 
        exit(-1);
    }
}
