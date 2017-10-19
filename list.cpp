#include <stdlib.h>
#define LIST_INIT_SIZE 1000;
#define LISTINCREMENT 100;
typedef struct {
	char *elem;
	int length;
	int listsize;
}List;

bool InitList(List &L) {
	L.elem = (char *)malloc(LIST_INIT_SIZE * sizeof(char));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return ture;
}

