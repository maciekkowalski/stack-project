#include "student.h"
#include "exceptions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#pragma warning (disable : 6011) 

const char* studyFields[] = {
   "INFORMATYKA",				
   "MATEMATYKA",			
   "FIZYKA",		
   "ARCHITEKTURA",		
   "EKONOMIA",			
   "PRAWO",		
   "HISTORIA",	
   "PSYCHOLOGIA"			
};

void* STUD_Init(char *lastName_, size_t year_, STUDY_FIELD field_) {
	STUDENT* st = (STUDENT*)malloc(sizeof(STUDENT));
	if (!st)
		return NULL;
		char* tmp = (char*)malloc(strlen(lastName_) + 1);
		if (!tmp)
			return NULL;
		strcpy_s(tmp, strlen(lastName_) + 1, lastName_);

		st->lastName = tmp;
		st->year = year_; 
		st->field = field_; 

	return (void*)(st); 
}

void STUD_Free(void * pStud)  {
	STUDENT* tmp = (STUDENT*)pStud;
	char* p = tmp->lastName;  
	if (tmp) {
		free(p);
		free(tmp);
	}
}

void* STUD_Push(char* lastName_, size_t year_, STUDY_FIELD field_) {
	for (int i = 0; i < strlen(lastName_); i++)
		if (isdigit(lastName_[i]))
			EXCEPT(4, __LINE__, __FILE__);

	void* p = STUD_Init(lastName_, year_, field_);
	return p;
}

void STUD_Print(void* pStud) {
	STUDENT* st = (STUDENT*)pStud;
	if (!st)
		return;

		printf("\tNazwisko: %s\n", st->lastName);
		printf("\tRok urodzenia: %zu\n", st->year);
		printf("\tKierunek studiow: %s\n", studyFields[st->field]);
}

void STUD_Upload(void* pStud, FILE** f) {
	STUDENT* st = (STUDENT*)pStud;
	if (!st)
		return;
	size_t l = strlen(st->lastName) + 1;
	char* tmp = st->lastName;

	
	fwrite(&l, sizeof(size_t), 1, *f);
	for (int i = 0; i < l; i++) 
		fwrite(&tmp[i], sizeof(char), 1, *f);
	fwrite(&st->year, sizeof(size_t), 1, *f);
	fwrite(&st->field, sizeof(STUDY_FIELD), 1, *f);
}

void *STUD_Download(FILE **f) {

	
	int i = 0;
	size_t l = NULL;
	fread(&l, sizeof(size_t), 1, *f);
	if (l == NULL)
		return NULL;

	char* lastName = (char*)malloc(l * sizeof(char));

	for (int i = 0; i < l; i++)
		if (!fread(&lastName[i], sizeof(char), 1, *f))
			EXCEPT(6, __LINE__, __FILE__); // warning : 6011

		size_t year;
		fread(&year, sizeof(size_t), 1, *f);
		STUDY_FIELD field;
		fread(&field, sizeof(STUDY_FIELD), 1, *f);
		void* p = STUD_Push(lastName, year, field);
		free(lastName);
		return p;
}

int STUD_SearchLastName(void *pCurrentData, void *pSearchData) {
	STUDENT* pCurrent = (STUDENT*)pCurrentData;
	STUDENT* pSearch = (STUDENT*)pSearchData;
	if (strcmp(pCurrent->lastName, pSearch->lastName) == 0)
		return 1;
	return 0;
}

int STUD_SearchYear(void* pCurrentData, void* pSearchData) {
	STUDENT* pCurrent = (STUDENT*)pCurrentData;
	STUDENT* pSearch = (STUDENT*)pSearchData;
	if (pCurrent->year == pSearch->year) 
		return 1;
	return 0;
}

int STUD_SearchField(void* pCurrentData, void* pSearchData) {
	STUDENT* pCurrent = (STUDENT*)pCurrentData;
	STUDENT* pSearch = (STUDENT*)pSearchData;
	if (pCurrent->field == pSearch->field) 
		return 1;
	return 0;
}