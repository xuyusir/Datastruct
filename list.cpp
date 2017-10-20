#include <stdlib.h>
#define LIST_INIT_SIZE 1000
#define LISTINCREMENT 100
typedef struct {
	char *elem;
	int length;
	int listsize;
}List;

bool InitList(List &L) {
	L.elem = (char *)malloc(LIST_INIT_SIZE*sizeof(char));
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return true;
}

bool ListInsert(List &L, int i, char e) {
	if (i<1 || i>L.length + 1) return false;
	if (L.length >= L.listsize) {
		L.elem = (char*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(char));
		L.listsize += LISTINCREMENT;
	}
	char* q;
	char* p;
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; --p) *(p + 1) = *p;
	*q = e;
	++L.length;
	return true;
}

bool ListDelete(List &L, int i, char &e) {
	if (i<1 || i>L.length + 1) return false;
	char* p;
	char* q;
	p = &(L.elem[i - 1]);
	e = *p;
	q = L.elem + L.length - 1;
	for (++p; p <= q; ++p) *(p - 1) = *p;
	--L.length;
	return true;
}
