#ifndef INTERFACE_H
#define INTERFACE_H

enum INTERF {
	INTERF_PUSH,
	INTERF_POP,
	INTERF_SIZE,
	INTERF_CLEAR, 
	INTERF_SEARCH,
	INTERF_UPLOAD_FILE,
	INTERF_DOWNLOAD_FILE,
	INTERF_STOP,
	INTERF_TOTAL
};

void menu();
void push();
void size();
void pop();
void clear();
void search();
void upload();
void download();

enum INTERF_SEARCH {
	SEARCH_LASTNAME,
	SEARCH_YEAR,
	SEARCH_FIELD,
	SEARCH_TOTAL
};



#endif