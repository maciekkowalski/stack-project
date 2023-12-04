#include "interface.h"
#include "student.h"
#include "exceptions.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#pragma warning (disable : 4996)
#pragma warning (disable : 6011)
#pragma warning (disable : 6387)

void search_lastName(); 
void search_year();
void search_field();

const char * strArr[] = {
	
    "PUSH - dodaj do stosu",		
	"POP - zdejmij ze stosu (Pokazuje jednoczesnie zdejmowany element)",		
	"ROZMIAR - pokaz ilosc elementow w stosie",		
	"CLEAN - wyczyszczenie stosu",	
	"WYSZUKAJ - wyszukaj osobe",	
	"UPLOAD - uploaduj dane do pliku data.bin",	
	"DOWNLOAD - pobierz z pliku data bin",	
	"STOP - ZAKONCZ DZIALANIE PROGRAMU"		
	
}; 

const char* strArrSt[] = {
   "INFORMATYKA",				
   "MATEMATYKA",			
   "FIZYKA",		
   "ARCHITEKTURA",
   "EKONOMIA",
   "PRAWO",
   "HISTORIA",	
   "PSYCHOLOGIA"			
};

const char* strArrSearch[] = {
	"Nazwisko",  
	"Rok",       
	"Kierunek",      
	
};




void menu() {
	size_t i = 0;
	while (i < INTERF_TOTAL)
		printf("%zu - %s\n", i - 1, strArr[i++]);
}

STUDY_FIELD setStudyField() {
	size_t i = 0;
	while (i < STUDF_TOTAL)
		printf("%zu - %s\n", i - 1 , strArrSt[i++]);
	size_t op;

	while (1) {
		if (!scanf("%zu", &op))
			EXCEPT(1, __LINE__, __FILE__);

		switch (op)
		{
		case STUDF_INFORMATYKA: return STUDF_INFORMATYKA;
			break;
		case STUDF_MATEMATYKA: return STUDF_MATEMATYKA;
			break;
		case STUDF_FIZYKA: return STUDF_FIZYKA;
			break;
		case STUDF_ARCHITEKTURA: return STUDF_ARCHITEKTURA;
			break;
		case STUDF_EKONOMIA: return STUDF_EKONOMIA;
			break;
		case STUDF_PRAWO: return STUDF_PRAWO;
			break;
		case STUDF_HISTORIA: return STUDF_HISTORIA;
			break;
		case STUDF_PSYCHOLOGIA: return STUDF_PSYCHOLOGIA;
			break;
		default:
			printf("Blad. Sprobuj ponownie.\n");
		};
	}
}

void push() {
	char lastName[64]; 
	size_t year;
	STUDY_FIELD field;

	printf("Nazwisko: (wprowadz + enter)\n");
	if (!scanf("%s", lastName)) 
		EXCEPT(1, __LINE__, __FILE__);
	
	int i = 0;

	while (i < 64) 
		if (lastName[i++] == '\0')
			i = 65;
	if(i == 64)
		EXCEPT(5, __LINE__, __FILE__);

	for (int i = 0; i < strlen(lastName); i++)
		if (isdigit(lastName[i]))
			EXCEPT(4, __LINE__, __FILE__);
	

	printf("Rok urodzenia: (wprowadz + enter)\n");
	if (!scanf("%zu", &year)) 
		EXCEPT(1, __LINE__, __FILE__);

	printf("Kierunek: (wybierz z listy)\n");
	field = setStudyField(); 

	void* pStud = STUD_Push(lastName, year, field);

	if (!STACK_Push(pStud))
		EXCEPT(3, __LINE__, __FILE__);
}

void pop() {
	STACK tmp = STACK_Pop();
	if (tmp.pData != NULL) {
		STUD_Print(tmp.pData);
		STUD_Free(tmp.pData);
	}
	else {
		EXCEPT_Light(0);
	}
}

void size() {
	printf("Ilosc elementow stosu: %d\n\n", STACK_Size());
}

void search() {
	size_t i = 0;
	for (size_t i = 0; i < SEARCH_TOTAL; i++)
		printf("%zu - %s\n", i, strArrSearch[i]);
	size_t op;

	if (!scanf("%zu", &op))
		EXCEPT(1, __LINE__, __FILE__);

		switch (op)
		{
		case SEARCH_LASTNAME: search_lastName();
			break;
		case SEARCH_YEAR: search_year();
			break;
		case SEARCH_FIELD: search_field();
			break;
		default:
			printf("Nieznany kod operacji!\n");
	}
}

void search_lastName() {
	int found = 0;
	char tmp[64]; 

	printf("Nazwisko:\n\n");
	if (!scanf_s("%s", tmp, (unsigned int)sizeof(tmp))) 
		EXCEPT(1, __LINE__, __FILE__);

	int i = 0;
	while (i < 64) 
		if (tmp[i++] == '\0')
			i = 65;

	if (i == 64)
		EXCEPT(5, __LINE__, __FILE__);

	for (int i = 0; i < strlen(tmp); i++)
		if (isdigit(tmp[i])) {
			printf("Nazwisko nie moze zawierac cyfr.\n");
			return;
		}


	size_t l = strlen(tmp) + 1;
	char *str = (char*)malloc(l * sizeof(*tmp));
	if (!str)
		EXCEPT(6, __LINE__, __FILE__);

		strcpy_s(str, strlen(tmp) + 1, tmp);

		STUDENT* searchD = (STUDENT*)malloc(sizeof(STUDENT));
		if (!searchD)
			EXCEPT(6, __LINE__, __FILE__); // warning : 6011

		searchD->lastName = str;

		void* pData = STACK_Search(searchD, STUD_SearchLastName, 1);

		if (pData) {
			printf("Znaleziono:\n");
			STUD_Print(pData);
			found = 1;
		}

		while (pData) {
			pData = STACK_Search(searchD, STUD_SearchLastName, 0);
			if (pData) {
				printf("Znaleziono:\n");
				STUD_Print(pData);
			}
		}
		free(str);
		free(searchD);
		if (!found)
			printf("Nie znaleziono szukanej osoby\n");
	
}

void search_year() {
	int found = 0;
	size_t year;

	printf("Rok urodzenia:\n");
	if (!scanf("%zu", &year)) 
		EXCEPT(1, __LINE__, __FILE__);

	STUDENT* searchD = (STUDENT*)malloc(sizeof(STUDENT));
		if (!searchD)
		EXCEPT(6, __LINE__, __FILE__); // warning : 6011

	searchD->year = year;

	void* pData = STACK_Search(searchD, STUD_SearchYear, 1);

	if (pData) {
		printf("Znaleziono:\n");
		STUD_Print(pData);
		found = 1;
	}

	while (pData) {
		pData = STACK_Search(searchD, STUD_SearchYear, 0);
		if (pData) {
			printf("Znaleziono:\n");
			STUD_Print(pData);
		}
	}
	free(searchD);
	if (!found)
		printf("Nie znaleziono szukanej osoby\n");

}

void search_field() {
	int found = 0;
	printf("Kierunek studiow:\n");
	STUDY_FIELD field = setStudyField(); 

	STUDENT* searchD = (STUDENT*)malloc(sizeof(STUDENT));
	if (!searchD)
		EXCEPT(6, __LINE__, __FILE__); 

	searchD->field = field;

	void* pData = STACK_Search(searchD, STUD_SearchField, 1);

	if (pData) {
		printf("Znaleziono:\n");
		STUD_Print(pData);
		found = 1;
	}

	while (pData) {
		pData = STACK_Search(searchD, STUD_SearchField, 0);
		if (pData) {
			printf("Znaleziono:\n");
			STUD_Print(pData);
		}
	}
	free(searchD);
	if (!found)
		printf("Nie znaleziono szukanej osoby\n");

}

void clear() {
	STACK_Free();
	printf("Czyszczenie zakonczone\n");
}

void upload() {
	STACK s;
	void* pData;
	FILE* f;
	f = fopen("data.bin", "wb");
	if (!f)
		EXCEPT(2, __LINE__, __FILE__);
	else {
		s = STACK_Pop(); 
		pData = s.pData;
		while (pData != NULL) {
			STUD_Upload(pData, &f);
			STUD_Print(pData);
			STUD_Free(s.pData);  
			s = STACK_Pop();
			pData = s.pData;
		}

		fclose(f);
		printf("Uploadowanie zakonczone pomyslnie\n");
	}
}

void download() {
	void* pSt;
	FILE* f;
	f = fopen("data.bin", "rb");
	if(!f) 
		EXCEPT(2, __LINE__, __FILE__);
	
	pSt = STUD_Download(&f);

	while(pSt != NULL) {
		if (!STACK_Push(pSt))
			EXCEPT(3, __LINE__, __FILE__);
		pSt = STUD_Download(&f);
	} 

	fclose(f);
	printf("Pobieranie zakonczone pomyslnie\n");
}