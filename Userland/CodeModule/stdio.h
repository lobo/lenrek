#ifndef IO_H
#define IO_H

#include <stdint.h>
#include <stdarg.h>
#include "string.h"
#include "lib.h"

#define ON 1
#define OFF 0

#define NO_INPUT 0

#define INPUTERROR 0
#define INPUT_ERROR_EXIT { printString("Input Errado!\n");}

void get_input(char * c);

void getString(char *buffer, const int size);

void printString(const char * str);

int getInt(int * num, const int size);

char getChar();

void putChar(const char );

void printf(const char *, ...);

int scanf(const char *, ...);

int isdigit(unsigned char);

int stoi(char *);

int htoi(const char *, int *);

void change_text_color();

void clearscreen();

void timertick();

void play_sound();

/* Funciones de la catedra */
void saveDec(int * value, char * buf);

void saveHex(int * value, char * buf);

void printDec(int value);

void printHex(int value);

void printBin(int value);

void printBase(int value, int base);

int uintToBase(int value, char * buffer, int base);

#endif
