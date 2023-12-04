#ifndef STUDENT_H
#define STUDENT_H
#include <stdio.h>
#include <stdlib.h>

enum STUDY_FIELD {
	STUDF_INFORMATYKA,
	STUDF_MATEMATYKA,
	STUDF_FIZYKA,
	STUDF_ARCHITEKTURA,
	STUDF_EKONOMIA,
	STUDF_PRAWO,
	STUDF_HISTORIA,
	STUDF_PSYCHOLOGIA,
	STUDF_TOTAL,
	STUDF_NULL
};



struct STUDENT {
	char *lastName;
	size_t year;
	STUDY_FIELD field;
};

void STUD_Free(void* pStud);
void* STUD_Push(char* lastName_, size_t year_, STUDY_FIELD field_);
void STUD_Print(void* pStud);
void STUD_Upload(void* pStud, FILE** f);
void* STUD_Download(FILE **f);

int STUD_SearchLastName(void* pCurrentData, void* pSearchData);
int STUD_SearchYear(void* pCurrentData, void* pSearchData);
int STUD_SearchField(void* pCurrentData, void* pSearchData);

#endif