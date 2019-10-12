#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h> 
#include <unistd.h> 
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include "commands_fs.h"
#include "fs.h"
#include "directory_structure.h"

int commandREGOK(int numTokens, char** saveTokens, long int numberChar){
    if(numTokens != 2)        
        return FALSE;
    else if(numberChar - 2 != strlen(saveTokens[0])+strlen(saveTokens[1]))        
        return FALSE;
    else if (strlen(saveTokens[1]) != 5)        
        return FALSE;
    else if(!onlyNumbers(saveTokens[1]))        
        return FALSE;
    else
        return TRUE;
}

int commandLTPOK(int numTokens, char** saveTokens, long int numberChar){
    if(numTokens != 1){
        return FALSE; 
    }else if(numberChar - 1 != strlen(saveTokens[0])){
        return FALSE;
    }else
        return TRUE;
}

int commandPTPOK(int numTokens, char** saveTokens, long int numberChar){
    if(numTokens != 3)
        return FALSE;
    else if(numberChar - 3 != strlen(saveTokens[0]) + strlen(saveTokens[1]) + strlen(saveTokens[2])){
        return FALSE;
    }
    else 
        return TRUE;     
}

int commandLQUOK(int numTokens, char** saveTokens, long int numberChar){
    if(numTokens != 2)
        return FALSE; 
    else if(numberChar - 2 != strlen(saveTokens[0]) + strlen(saveTokens[1])){
        return FALSE;
    }
    else
        return TRUE; 
}

//--------------------------------------------------------------------
// TCP CMDS
//--------------------------------------------------------------------
int commandGQUOK(int numTokens, char** saveTokens, long int numberChar){
    if(numTokens != 3)
        return FALSE;
    else if(numberChar - 3 != strlen(saveTokens[0]) + strlen(saveTokens[1]) + strlen(saveTokens[2]))
        return FALSE;
    else if(!strcmp(saveTokens[0], "GQU"))
        return TRUE;
    else 
        return TRUE;
}

int commandQUSOK(int numTokens, char** saveTokens, long int numberChar){
    //Nao sei se nao temos que verificar os ficheiros 
    /*if(numTokens != 4)
        return FALSE;
    else if(numberChar - 4 != (strlen(saveTokens[0]) + strlen(saveTokens[1]) + strlen(saveTokens[2]) + strlen(saveTokens[3])))
        return FALSE;
    else  */
        return TRUE;
}

int commandANSOK(int numTokens, char** saveTokens, long int numberChar){
    //Nao sei se nao temos que verificar os ficheiros 
    if(numTokens != 3)
        return FALSE;
    else if(numberChar - 3 != strlen(saveTokens[0])  + strlen(saveTokens[1]) + strlen(saveTokens[2]))
        return FALSE;
    else 
        return TRUE;
}

//Outras funções
int onlyNumbers(char* message) {
    int i;
    for(i = 0; i < strlen(message);i++){
        if(message[i] < 48 || message[i] > 57){
            return FALSE;
        }
    }
    return TRUE;
}

//TODO: Podemos passar estas funcões para o parse---------------------
//TOPIC LIST
char* checkTopics(){
    char* message = malloc(sizeof (char)* 1024);
    strcpy(message, number_of_topics());
    strcat(message, " ");
    strcat(message, topicList());
    return message;
}

//TOPIC PROPOSE
char* proposeTopic(char** saveTokens){
    char* message = malloc(sizeof (char)* 1024); 
    char* path = malloc (sizeof (char) * 1024);
    sprintf(path, "TOPICS/%s", saveTokens[2]);
    
    if (check_directory_existence(path))
        strcpy(message, "DUP");
    else if (!check_max_directory_size(path))
        strcpy(message, "FUL");
    else {
        create_topic_directory(saveTokens[2], saveTokens[1]);
        strcpy(message, "OK");
    }
    free(path);
    return message;
}

char* checkSubmitQuestion(char** saveTokens){
    char* message = malloc(sizeof (char)* 1024);
    char* path = malloc(sizeof (char)* 1024);
    sprintf(path, "TOPICS/%s/%s", saveTokens[3], saveTokens[4]);

    if(check_directory_existence(path))
        strcpy(message, "DUP");
    else if(!check_max_directory_size(path))
        strcpy(message, "FUL");
    else
        strcpy(message, "OK");
    
    free(path);
    return message;

}


//QUESTION LIST
char* checkQuestions(char** saveTokens){
    char* message = malloc(sizeof (char)* 1024);
    char* path = malloc(sizeof (char)* 1024);
    sprintf(path, "TOPICS/%s/", saveTokens[1]);
    strcpy(message, numberOfdirectories(path));
   
    strcat(message, " ");
    strcat(message, questionList(saveTokens[1]));
    free(path);
    return message;
}