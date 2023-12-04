#include "interface.h"
#include "exceptions.h"
#include <stdlib.h>
#include <stdio.h>

const char* eArr[] = {
	"CLEAR ERROR!", // EX_CLEAR_ERROR - 0
    "Blad wprowadzania", // EX_SCANF_NULL - 1
    "Blad otwierania pliku\n", // EX_FOPEN_NULL - 2
    "Push error", // EX_PUSH - 3
	"Imie nie moze zawierac cyfr!\n", // EX_DIGIT_IN_NAME - 4
	"String error", // EX_STRING_NO_END - 5
	"NULL POINTER" // EX_NULL_POINTER - 6 
};

void EXCEPT(size_t e, int line, const char *file) {
	printf("ERROR!\nFILE: %s\nLINE: %d\nEXCEPTION: %s\n", file, line, eArr[e]);
	if (e)
	clear();
	exit(-1);
}

const char* eLightArr[] = {
	"STOS JEST PUSTY!\n", // EX_L_STACK_EMPTY - 0
	"Nieznany kod operacji!\n" 
};


void EXCEPT_Light(size_t e) {
	printf("%s\n", eLightArr[e]);
}