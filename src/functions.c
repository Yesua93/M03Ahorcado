#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include "functions.h"

int openFileWords(char *pathFile,char **words){
    FILE * FD;
    int num_words = 0;

    if ((FD = fopen(pathFile,"r"))!=NULL){
        printf("Cargado %s\n",pathFile);

        while(!feof(FD)){
            //Allocate size of buffer
            char* buffer=(char *) malloc(sizeof(char)*MAXBUFFERSIZE);
            //Get Line from File and assign to buffer
            fscanf(FD,"%s",buffer);

            //Prevent memory OVERFLOW in app limiting number of words to save and their length
            if(strlen(buffer)+1 > MAXLENGTHWORD){
                //La palabra supera el limite de caracteres de la app, descartada.\n"
                free(buffer);
                buffer=NULL;
                continue;
            }
            if (num_words==MAXNUMWORDS){
                //Se alcanzan el numero maximo de palabras permitidas en la app
                free(buffer);
                buffer=NULL;
                break;
            }

            //Add word to words array
            //Allocate memory for string
            words[num_words] = (char*) malloc(MAXLENGTHWORD* sizeof(char));
            //Convert buffer string to Uppercase
            int i=0;
            while(buffer[i]){
                buffer[i]=toupper(buffer[i]);
                i++;
            }
            //Dump buffer to array of words
            strcpy(words[num_words],buffer);
            num_words++;
            free(buffer);
            buffer=NULL;

        }
        fclose(FD);
        return num_words;

    } else{
        printf("Fallo al cargar el fichero %s\n%s\n",pathFile,strerror(errno));
        printf("Presiona ENTER para abortar la ejecucion\n");
        while ( getchar() != '\n')
        clean_stdin();
        exit(1);
    }


}

int pickRandomWord(int size){
    //Return a random number in range of num_elements of words[]
    int i, n;
    time_t t;
    /* Intializes random number generator */
    srand((unsigned) time(&t));
    return rand() % size+1;
    
}


void fillSecret(char *secret,int size){
    for(int i=0;i<=size;i++){
        secret[i] = '?';
        if(size-i==0) secret[i]='\0';
    }
}

void mainLoopGame(char *word,char *secret,int longitud){
    int intents = MAXINTENTS;
    int isWin = 0;
    char letter = ' ';
    char auxSecret[longitud];

    while (intents>0){
        headerLogo();
        //copy *secret in auxiliar buffer
        for(int i=0;i<=longitud;i++){
            auxSecret[i]=secret[i];
        }
        printf("Tienes %i intentos\n", intents);

        //Print hanged state and secret buffer
        drawHanged(intents);
        printf("\n%s\n", secret);


        //get for stdin one character and uppercase them
        printf("Dime una letra:\n");
        scanf("%c",&letter);
        clean_stdin();
        letter = toupper(letter);


        //check if letter in word buffer if yes, fill secrect '?' for the letter
        for (int i = 0; i<=longitud; i++) {

            if (secret[i] == '?' && word[i] == letter) {
                secret[i] = word[i];
            }
        }

        //check if auxiliar and secret is equals if yes, the user fail the letter
        if (strcmp(auxSecret,secret)==0){
            printf("\nLastima Fallate\n");
            intents--;
        }

        //Check if word is equal to secret if yes beak loop and win
        if (strcmp(word,secret)==0){
            isWin=-1;
            break;
        }
    }

    if(isWin==-1){

        printf("Has ganado Enhorabuena\n");
        drawHanged(isWin);
        printf("Presiona Enter para abortar la ejecucion\n");
        while ( getchar() != '\n')
        clean_stdin();
    }

    else if(intents==0){
        printf("Has perdido, te has quedado sin intentos y por lo tanto estas muerto\n");
        printf("La palabra era %s\n",word);
        drawHanged(intents);
        printf("\n");
        printf("Presiona Enter para abortar la ejecucion\n");
        while ( getchar() != '\n')
        clean_stdin();
    }

}


//Print logo of a game
void headerLogo(){
    printf("    ______  _                                   _      _\n");
    printf("    | ___ %c(_)                                 (_)    | |\n",92);
    printf("    | |_/ / _   ___  _ __  __   __  ___  _ __   _   __| |  ___\n");
    printf("    | ___ %c| | / _ %c| '_ %c %c %c / / / _ %c| '_ %c | | / _` |/ _ %c\n",92,92,92,92,92,92,92,92);
    printf("    | |_/ /| ||  __/| | | | %c V / |  __/| | | || || (_| || (_) |%c\n",92,92);
    printf("    %c____/ |_| %c___||_| |_|  %c_/   %c___||_| |_||_| %c__,_| %c___/%c\n",92,92,92,92,92,92,92);
    printf("                                                       \n");
    printf("                                                                \n");
    printf("                              ___   _                           \n");
    printf("                             / _ %c | |\n",92);
    printf("                            / /_%c %c| |\n",92,92);
    printf("                            |  _  || |\n");
    printf("                            | | | || |\n");
    printf("                            %c_| |_/|_|\n",92);

    printf("                                        \n");
    printf("      ___   _                                    _\n");
    printf("     / _ %c | |                                  | |\n",92);
    printf("    / /_%c %c| |__    ___   _ __   ___   __ _   __| |  ___\n",92,92);
    printf("    |  _  || '_ %c  / _ %c | '__| / __| / _` | / _` | / _ %c\n",92,92,92);
    printf("    | | | || | | || (_) || |   | (__ | (_| || (_| || (_) |\n");
    printf("    %c_| |_/|_| |_| %c___/ |_|    %c___| %c__,_| %c__,_| %c___/\n",92,92,92,92,92,92);
    printf("    \n");
    printf("    \n");
    printf("    \n");
    printf("    \n");

}

void drawHanged(int x){
    if(x==6) {
        printf("________________\n");
        printf("| /\n");
        printf("|/\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|_______________\n");
    }

    else if(x==5){
        printf("________________\n");
        printf("| /           |\n");
        printf("|/            |\n");
        printf("|            ( )\n");
        printf("|             |\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|______________\n");



    }


    else if(x==4){
        printf("________________\n");
        printf("| /           |\n");
        printf("|/            |\n");
        printf("|            ( )\n");
        printf("|             |\n");
        printf("|             |\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|______________\n");



    }


    else if(x==3){
        printf("________________\n");
        printf("| /           |\n");
        printf("|/            |\n");
        printf("|            ( )\n");
        printf("|           / |\n");
        printf("|             |\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|______________\n");



    }

    else if(x==2){
        printf("________________\n");
        printf("| /           |\n");
        printf("|/            |\n");
        printf("|            ( )\n");
        printf("|           / | %c\n",92); //  92=\ En ASCII
        printf("|             |\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|______________\n");



    }

    else if(x==1){
        printf("________________\n");
        printf("| /           |\n");
        printf("|/            |\n");
        printf("|            ( )\n");
        printf("|           / | %c\n",92);
        printf("|             |\n");
        printf("|            / \n");
        printf("|\n");
        printf("|\n");
        printf("|______________\n");



    }

    else if(x==0){
        printf("________________\n");
        printf("| /           |\n");
        printf("|/            |\n");
        printf("|            ( )\n");
        printf("|           / | %c\n",92);
        printf("|             |\n");
        printf("|            / %c\n",92);
        printf("|\n");
        printf("|\n");
        printf("|______________\n");



    }
        //Lose the game
    else if(x==-1){

        printf("\n");
        printf("\n");
        printf("              (**)\n");
        printf("             //||%c%c\n",92,92);
        printf("               ||\n");
        printf("              // %c%c\n",92,92);
        printf("_______________________________________");
        printf("\n");
        printf("\n");


    }
}

//fflush() dont work in linux
void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

