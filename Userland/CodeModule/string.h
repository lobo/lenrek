#ifndef IO_H
#define IO_H

#include <stdint.h>

/* Devuelve la longitud de un string */
int strlen(const char *s);

/* Compara strings */
int strcmp(char* a, char* b);

/* Copia un string de origen a destino */
void strcpy(char * dest, const char * source);

/* Convierte el string a minusculas */
char * lowerString(char * s);

/* Convierte char a minuscula */
unsigned char tolower(unsigned char c);

/* Borra los espacios del comienzo y del fin del string */
void trim(char* str);

#endif
