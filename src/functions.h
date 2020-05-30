#ifndef AHORCADO_FUNCTIONS_H
#define AHORCADO_FUNCTIONS_H

/******************CONSTANTS*****************/
//Protect app from memory overflow
#define MAXNUMWORDS 60
#define MAXLENGTHWORD 25+1
#define MAXPATHNAME 200
#define MAXBUFFERSIZE 255
#define MAXINTENTS 7
/******************CONSTANTS*****************/


/******************FUNCTIONS*****************/

//Load words file and populate words like array of strings, and return number of elements in array
int openFileWords(char *pathFile, char **words);

//Pick a random word from array, need to pass size of array and return  random index
int pickRandomWord(int size);

//Fill *secret with '?'*size
void fillSecret(char *secret,int size);

//MainLoopGame, in this method is implemented all logic of the game
void mainLoopGame(char *word,char *secret,int longitud);

//Print logo of a game
void headerLogo();

//draw hanged in function of int x (intents)
void drawHanged(int x);

void clean_stdin(void);

/******************FUNCTIONS*****************/

#endif //AHORCADO_FUNCTIONS_H
