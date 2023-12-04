#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "exceptions.h"

static STACK* first = NULL; 
long size = 0; 
FreeData freeData;

void STACK_Init(FreeData pFreeData) {
	first = NULL;
	freeData = pFreeData;
};

void STACK_Free() {
	STACK* element = first;
	STACK* tmp = NULL;

	while (element) {
		(*freeData)(element->pData); 
		tmp = element;
		element = element->next; 
		free(tmp); 
	}
	first = NULL;
	size = 0;
}

STACK* STACK_Push(void* pData) {
	size++;
	STACK* current = (STACK*)malloc(sizeof(STACK));
	if (!current)
		return NULL;

	current->next = first;	
	first = current; 
	current->pData = pData; 

	return current;
}

STACK STACK_Pop() {
	STACK current;

	if (!first)  {
		current.next = NULL;
		current.pData = NULL;
	}
	else {
		size--;
		STACK* next = first->next; 
		current.next = NULL;
		current.pData = first->pData;

		free(first);
		first = next; 
	}
	return current;
}

long STACK_Size() {	return size; }

void* STACK_Search(void *searchData, CompareData compare, int FirstEntry)  {
	static STACK* element;
	STACK* tmp = NULL;

	if (FirstEntry)
		element = first;

	while(element) {
		if (!(*compare)(element->pData, searchData)) 
			element = element->next;
		else {
			tmp = element;
			element = element->next;
			return tmp->pData;
		}
	}

	return NULL; 
}