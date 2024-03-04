#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{   
    char* fileName = argv[1];
    int keepRunning = 1;
    while(keepRunning){
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
            case 0:
                printf("Exiting the code....\n");
                keepRunning = 0;
                break;
            case 1:
                removeComments(fileName);
                break;
            case 2:
                printLexemes(fileName);
                break;
            case 3:
                break;
            case 4:
                //timeTaken(fileName);
                break;
            default:
                break;
        }
        if(keepRunning == 0){
            break;
        }
    }
}