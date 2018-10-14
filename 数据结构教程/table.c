#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <Windows.h>



#define TABLE_SIZE 1024
#define error(string)\
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);\
		SetConsoleTextAttribute(hConsole, 0xC);\
		printf("Error: ");\
		SetConsoleTextAttribute(hConsole, 0xF);\
		printf("%s:%d\n", __FILE__,  __LINE__);\
		printf("\t");\
		printf(string);\
		printf("\n\n");\
		abort();

typedef struct Table {
	int * head;
	int capacity;
	int size;
}Table;

int initTable(Table *t);

int findTable(Table *t, int x);

int alterTable(Table *t, int ele, int newEle);

int insertTable(Table *t, int pos, int ele);

static int push_back(Table *t, int ele);

static int push_front(Table *t);

static int pop_back(Table *t);

static int pop_front(Table *t);

static int clear(Table *t);
 
static int pop(Table *t);

static int size(Table *t);

static int capacity(Table *t);

static void display(Table *t);

int main(void) {

	Table *t = (Table*)malloc(sizeof(Table));

	initTable(t);

	push_back(t, 1);
	push_back(t, 2);
	push_back(t, 2);

	display(t);
	printf("%d\n", size(t));
	printf("%d\n", capacity(t));
	
	
	
	pop_back(t);
	pop_back(t);
	display(t);
	printf("%d\n", size(t));
	printf("%d\n", capacity(t));

	system("pause");
	return 0;
}


int initTable(Table *t) {
	if (t == NULL) {
		error("表不能为空");
		return -1;
	}
	
	t->head = (int*)malloc(sizeof(int) * TABLE_SIZE);
	if (t->head == NULL) {
		error("表内空间分配失败");
		return -1;
	}

	t->capacity = TABLE_SIZE;
	t->size = 0;

	return 0;
}

int findTable(Table *t, int x) {
	if (t == NULL) {
		error("表不能为空");
		return -1;
	}

	for (int i = 0; i < t->size; ++i) {
		if (t->head[i] == x) {
			return i;
		}
	}

	return -1;
}

int alterTable(Table *t, int ele, int newEle) {
	if (t == NULL) {
		error("表不能为空");
		return -1;
	}

	int index = findTable(t, ele);

	if (index == -1)
		return -1;

	t->head[index] = newEle;

	return 0;
}

int insertTable(Table *t, int pos, int ele){
	if (t == NULL) {
		error("表不能为空");
		return -1;
	}

	if (pos > t->size + 1 || pos < 1)
		return -1;

	if (t->size == 0) {
		t->head[t->size++] = ele;
		return 0;
	}

	if (t->size == t->capacity) {
		t->head = (int*)realloc(t->head, (t->capacity + TABLE_SIZE) * sizeof(int));
		
		if (t->head == NULL) {
			printf("分配失败\n");
			return -1;
		}

		t->capacity = t->capacity + TABLE_SIZE;
	}

	for (int i = t->size; i >= pos; --i) {
		t->head[i] = t->head[i - 1];
	}

	t->head[pos - 1] = ele;
	t->size++;

	return 0;
}

static int push_back(Table *t, int ele) {
	if (t == NULL) {
		error("表不能为空");
		return -1;
	}

	return insertTable(t, t->size + 1, ele);
}

static int pop_back(Table *t) {
	if (t == NULL) {
		error("表不能为空");
		return -1;
	}

	if (--t->size == -1)
		return -1;

	return t->head[t->size];
}

static int pop(Table *t) {
	if (t == NULL) {
		error("表不能为空");
		return -1;
	}

	return t->head[t->size];
}

static int size(Table *t) {
	if (t == NULL) {
		error("表不能为空");
		return -1;
	}

	return t->size;
}

static int capacity(Table *t) {
	if (t == NULL) {
		error("表不能为空");
		return -1;
	}

	return t->capacity;
}

static void display(Table *t) {
	if (t == NULL)
		return;

	for (int i = 0; i < t->size; ++i) {
		printf("%d ", t->head[i]);
	}

	printf("\n");
}