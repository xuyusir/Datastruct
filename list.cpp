#include <stdlib.h>
#include <stdio.h>

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
	while (pa<=pa_last&&pb<=pb_last)   //归并
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
	int j=0;
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

typedef struct queuenode{
	char data;
	struct queuenode *next;
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

typedef struct TreeNode
{
	char ch;                  //数据域  
	struct TreeNode *lchild;  //左孩子  
	struct TreeNode *rchild;  //右孩子  
}BTNode, *PBTNode;

void createBTree(PBTNode *root)
{
	char ch;
	ch = getchar();
	if (ch == '#')
	{
		*root = NULL;
	}
	else {
		*root = (PBTNode)malloc(sizeof(BTNode));
		(*root)->ch = ch;
		(*root)->lchild = NULL;
		(*root)->rchild = NULL;
			createBTree(&(*root)->lchild);
			createBTree(&(*root)->rchild);
	}
}

void preOrder(PBTNode root)
{
	if (root == NULL)
		return;
	printf("%-3c", root->ch);
	preOrder(root->lchild);
	preOrder(root->rchild);
}

//中序遍历二叉树  
void inOrder(PBTNode root)
{
	if (root == NULL)
		return;
	preOrder(root->lchild);
	printf("%-3c", root->ch);
	preOrder(root->rchild);
}

//后序遍历二叉树  
void postOrder(PBTNode root)
{
	if (root == NULL)
		return;
	preOrder(root->lchild);
	preOrder(root->rchild);
	printf("%-3c", root->ch);
}

//输出叶子结点  
void displyLeaf(PBTNode root)
{
	if (root == NULL)
		return;
	if (root->lchild == NULL&&root->rchild == NULL)
		printf("%-3c", root->ch);
	else {
		displyLeaf(root->lchild);
		displyLeaf(root->rchild);
	}
}

//左结点插入  
void inseartLeftNode(PBTNode root, char ch)
{
	PBTNode p, newNode;
	if (root == NULL)
		return;
	p = root->lchild;
	newNode = (PBTNode)malloc(sizeof(BTNode));
	newNode->ch = ch;
	newNode->rchild = NULL;
	newNode->lchild = p;
	root->lchild = newNode;
}

//右结点插入  
void inseartRightNode(PBTNode root, char ch)
{
	PBTNode p, newNode;
	if (root == NULL)
		return;
	p = root->rchild;
	newNode = (PBTNode)malloc(sizeof(BTNode));
	newNode->ch = ch;
	newNode->lchild = NULL;
	newNode->rchild = p;
	root->rchild = newNode;
}

//销毁一颗二叉树  
void clear(PBTNode* root)
{
	PBTNode pl, pr;
	if (*root == NULL)
		return;
	pl = (*root)->lchild;
	pr = (*root)->rchild;
	(*root)->lchild = NULL;
	(*root)->rchild = NULL;
	free((*root));
	*root = NULL;
	clear(&pl);
	clear(&pr);
}

//删除左子树  
void deleteLeftTree(PBTNode root)
{
	if (root == NULL)
		return;
	clear(&root->lchild);
	root->lchild = NULL;
}

//删除右子树  
void deleteRightTree(PBTNode root)
{
	if (root == NULL)
		return;
	clear(&root->rchild);
	root->rchild = NULL;
}

//查找结点  
PBTNode   search(PBTNode root, char ch)
{
	PBTNode p;
	if (root == NULL)
		return NULL;
	if (root->ch == ch)
		return root;
	else {
		if ((p = search(root->lchild, ch)) != NULL)
			return p;
		else
			return  search(root->rchild, ch);
	}
}

//求二叉树的高度  
int BTreeHeight(PBTNode root)
{
	int lchildHeight, rchildHeight;
	if (root == NULL)
		return 0;
	lchildHeight = BTreeHeight(root->lchild);
	rchildHeight = BTreeHeight(root->rchild);
	return (lchildHeight>rchildHeight) ? (1 + lchildHeight) : (1 + rchildHeight);
}

//求叶子结点的个数  
int countLeaf(PBTNode root)
{
	if (root == NULL)
		return 0;
	if (root->lchild == NULL&&root->rchild == NULL)
		return 1;
	else {
		return countLeaf(root->lchild) + countLeaf(root->rchild);
	}
}

//求所有结点的个数  
int countAll(PBTNode root)
{
	if (root == NULL)
		return 0;
	return countAll(root->lchild) + countAll(root->rchild) + 1;
}

//复制二叉树  
PBTNode copyBTree(PBTNode root)
{
	PBTNode p, lchild, rchild;
	if (root == NULL)
		return NULL;
	lchild = copyBTree(root->lchild);
	rchild = copyBTree(root->rchild);
	p = (PBTNode)malloc(sizeof(BTNode));
	p->ch = root->ch;
	p->lchild = lchild;
	p->rchild = rchild;
	return p;
}

int main() {
	PBTNode tree;
	createBTree(&tree);
	preOrder(tree);
	



}
