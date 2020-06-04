#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"


int main() {
    char pathFile[MAXPATHNAME] = "./WORDS.txt";
    char *words[MAXNUMWORDS];
    int retry;
    int num_elements = openFileWords(pathFile,words);

    do{
    	int selectedIndex = pickRandomWord(num_elements);
    	int lenghtSecret = strlen(words[selectedIndex]);
    	char secretWord[lenghtSecret];
    	fillSecret(&secretWord[0],lenghtSecret);
   	mainLoopGame(words[selectedIndex],&secretWord[0],lenghtSecret);
	printf("\n\nQuieres volver a jugar?: 1.SI 2.NO \n");
	scanf("%i",&retry);
   } while(retry!=2);	



    return 0;
}
