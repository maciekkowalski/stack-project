#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

enum EX { // EX - exception 
	EX_CLEAR_ERROR, // 0
	EX_SCANF_NULL, // 1		 warning : 4996
	EX_FOPEN_NULL, // 2
	EX_PUSH, // 3
	EX_DIGIT_IN_NAME, // 4
	EX_STRING_NO_END, // 5 
	EX_NULL_POINTER // 6	warning : 6011		6387
};
enum EX_L_ { 
	EX_L_STACK_EMPTY, // 0
	EX_L_UNKNOWN_OPERATION // 1
};

void EXCEPT(size_t e, int line, const char* file);
void EXCEPT_Light(size_t e);

#endif