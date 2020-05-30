#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"


int main() {
    char pathFile[MAXPATHNAME] = "./WORDS.txt";
    char *words[MAXNUMWORDS];
    int num_elements = openFileWords(pathFile,words);


    int selectedIndex = pickRandomWord(num_elements);
    int lenghtSecret = strlen(words[selectedIndex]);
    char secretWord[lenghtSecret];
    fillSecret(&secretWord[0],lenghtSecret);
    mainLoopGame(words[selectedIndex],&secretWord[0],lenghtSecret);



    return 0;
}