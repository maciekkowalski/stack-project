#ifndef STACK_H
#define STACK_H

struct STACK {
    void* pData; 
    STACK*next; 
};

typedef void (*FreeData)(void* pData);
typedef int (CompareData)(void* pCurrentData, void* pSearchData);

void STACK_Init(FreeData pFreeData); 
void STACK_Free(); 
STACK* STACK_Push(void* pData); 
STACK STACK_Pop(); 
long STACK_Size(); 
void* STACK_Search(void* searchData, CompareData compare, int FirstEntry); 

#endif