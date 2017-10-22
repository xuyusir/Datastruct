#include <stdlib.h>
#define LIST_INIT_SIZE 1000
#define LISTINCREMENT 100
#define STACK_INIT_SIZE 1000
#define STACKINCREMENT 100
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

void MergeList(List La, List Lb, List &Lc) {
	char* pa;
	char* pb;
	char* pc;
	char* pa_last;
	char* pb_last;
	pa = La.elem;
	pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	pc = Lc.elem = (char *)malloc(Lc.listsize * sizeof(char));
	pa_last = La.elem + La.length - 1;
	pb_last = Lb.elem + Lb.length - 1;
	while (pa<=pa_last&&pb<=pb_last)   //¹é²¢
	{
		if (*pa <= *pb) *pc++ = *pa++;
		else *pc++ = *pb++;
	}
	while (pa<=pa_last) *pc++ = *pa++;
	while (pb <= pb_last) *pc++ = *pb++;
}


typedef struct node {
	char data;
	struct node *next;
}node,*linklist;

bool getnodeelem(linklist l, int i, char &e) {
	linklist p;
	int j;
	p = l->next;
	while (p&&j < i) {
		p = p->next; ++j;
	}
	e = p->data;
	return true;
}

bool nodelistinsert(linklist l, int i, char e) {
	linklist p=l,s;
	int j = 0;
	while (p&&j<=i-1)
	{
		p = p->next; ++j;
	}
	s = (linklist)malloc(sizeof(node));
	s->data = e; s->next = p->next;
	p->next = s;
	return true;
}

bool nodelistdelete(linklist l, int i, char &e) {
	linklist p=l,q;
	int j = 0;
	while (p->next&&j<i-1)
	{
		p = p->next; j++;
	}
	q = p->next; p->next = q->next;
	e = q->data; free(q);
	return true;
}

typedef struct {            //stack
	char* base;
	char* top;
	int stacksize;
}stack;

bool initstack(stack &s) {
	s.base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	return true;
}

bool push(stack &s, char e) {
	if (s.top-s.base>=s.stacksize)
	{
		s.base = (char*)realloc(s.base, (s.stacksize + STACKINCREMENT) * sizeof(char));
	}
	s.top = s.base + s.stacksize;
	s.stacksize += STACKINCREMENT;
	*s.top++ = e;
	return true;
}

bool pop(stack &s, char &e) {
	if (s.top == s.base)return false;
	e = *--s.top;
	return true;
}

typedef struct {
	char data;
	qnodeptr next;
}qnode,*qnodeptr;

typedef struct {
	qnodeptr front;
	qnodeptr rear;
}linkqueue;

bool initqueue(linkqueue &q) {
	q.front = q.rear = (qnodeptr)malloc(sizeof(qnode));
	q.front->next = NULL;
	return true;
}

bool enqueue(linkqueue &q, char e) {
	qnodeptr p;
	p = (qnodeptr)malloc(sizeof(qnode));
	p->data = e; p->next = NULL;
	q.rear->next = p;
	q.rear = p;
	return true;
}

bool dequeue(linkqueue &q, char &e) {
	qnodeptr p;
	p = q.front->next;
	e = p->data;
	q.front->next = p->next;
	if (q.rear == p) q.rear = q.front;
	free(p);
	return true;
}

