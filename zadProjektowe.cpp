#define _CRTDBG_MAP_ALLOC

#include "interface.h"
#include "stack.h"
#include "student.h"
#include "exceptions.h"
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>

#pragma warning (disable : 4996)

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	size_t op = 0;
	STACK_Init(STUD_Free);
	while (1) {
		menu();

		if (!scanf("%zu", &op))
			EXCEPT(1, __LINE__, __FILE__);
		printf("\n");
		switch (op)
		{
		case INTERF_PUSH: push();
			break;
		case INTERF_POP: pop();
			break;
		case INTERF_SIZE: size();
			break;
		case INTERF_CLEAR: clear();
			break;
		case INTERF_SEARCH: search();
			break;
		case INTERF_UPLOAD_FILE: upload();
			break;
		case INTERF_DOWNLOAD_FILE: download();
			break;
		case INTERF_STOP: clear();
			return 0;
		default:
			EXCEPT_Light(1);
		};
	}
	return 0; 
}