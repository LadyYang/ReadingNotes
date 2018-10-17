#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

/******************* 2.1 线性表及其逻辑结构 ********************
2.1.1 线性表定义：具有相同特性的数据元素的一个有限序列
	eg: (a1，a2，…，ai，ai+1，…，an)
2.1.2 线性表的抽象数据类型
	ADT List
	{
		数据对象:
			D = { ai | 1<=i<=n, n>=0, ai为ElemTpe类型 }
		数据关系:
			R = { <ai, ai+1> | ai、ai+1∈D , i=1,...,n-1 }
		基本运算:
			InitList(&L): 初始化线性表，构造一个空的线性表 L。
			DestoryList(&L): 销毁线性表，释放线性表 L 占用的内存空间。
			ListEmpty(L): 判断线性表是否空表，若 L 为空表，则返回真，否则返回假。
			ListLength(L): 求线性表的长度，返回 L 中元素的个数。
			DispList(L): 输出线性表，当 L 不为空时顺序显示 L 中各结点的值域。
			GetElem(L, i, &e): 求表中某个数据元素值，用 e 返回L中第i(1<=i<=n)个元素的值。
			LocateElem(L, e): 按元素值查找，返回L中第一个值域与e相等的元素的序号，若这样的元素不存在，则返回值为0。
			ListInsert(&L, i, e): 插入数据元素，在L的第i（1<=i<=n+1)个位置插入一个新的元素e，L的长度增1。
			ListDelete(&L, i, &e): 删除数据元素，删除L的第i(i<=i<=n)个元素，并用e返回其值，L的长度减1。
	}
	// 将表 LA, LB 的并集放入到表 LC 中
	void unionList(List LA, List LB, List &LC){
		int lena, i;
		ElemType e;
		InitList(LC);
		for(i = 1; i <= ListLength(LA); i++){
			GetElem(LA, i, e);
			ListInsert(LC, i, e);
		}
		lena = ListLength(LA);
		for(i = 1; i <= ListLength(LB); i++){
			GetElem(LB, i, e);
			if(!LocateElem(LA, e))
				ListInsert(LC, ++lena, e);
		}
	}
*/

void test2_1()
{
	printf(" 2.1 线性表及其逻辑结构\n");
}

/******************** 2.2 线性表的顺序存储结构 ********************
线性表的顺序存储结构是最常用的存储方式，它直接将线性表的逻辑结构映射到存储结构上。
2.2.1 线性表的顺序存储结构--顺序表
	线性表的顺序存储结构简称为顺序表(sequential list)
2.2.2 顺序表基本运算的实现
	
*/
#define MaxSize 50
typedef int ElemType;

typedef struct
{
	ElemType data[MaxSize];
	int length;
} SqList;

// 1. 建立顺序表
// 由a中的n个元素建立顺序表
void CreateList(SqList *&L, ElemType a[], int n)
{
	int i = 0, k = 0;

	L = (SqList *)malloc(sizeof(SqList));
	while (i < n)
	{
		L->data[k] = a[i];
		k++;
		i++;
	}

	L->length = k;
}

// 2. 顺序表基本运算算法
// 初始化线性表
void InitList(SqList *&L)
{
	L = (SqList *)malloc(sizeof(SqList));
	L->length = 0;
}

// 销毁线性表
void DestoryList(SqList *&L)
{
	free(L);
}

// 判断线性表是否为空表
bool ListEmpty(SqList *L)
{
	return (L->length == 0);
}

// 求线性表的长度
int ListLength(SqList *L)
{
	return (L->length);
}

// 输出线性表
void DispList(SqList *L)
{
	for (int i = 0; i < L->length; i++)
	{
		printf("%d", L->data[i]);
	}

	printf("\n");
}

// 求线性表中的某个数据元素值
bool GetElem(SqList *L, int i, ElemType &e)
{
	if (i < 1 || i > L->length)
		return false;

	e = L->data[i - 1];
	return true;
}

// 按元素值查找
int LocateElem(SqList *L, ElemType e)
{
	int i = 0;

	while (i < L->length && L->data[i] != e)
		i++;

	if (i >= L->length)
		return 0;
	else
		return i + 1;
}

// 插入数据元素
bool ListI76nsert(SqList *&L, int i, ElemType e)
{
	int j;

	if (i < 1 || i > L->length + 1)
		return false;

	i--;

	for (j = L->length; j > i; j--)
		L->data[j] = L->data[j - 1];

	L->data[i] = e;
	L->length++;

	return true;
}

void test2_2()
{
	printf("\n 2.2 线性表的顺序存储结构\n");
}

/********************************************************/
int main(void)
{

	//test2_1();
	test2_2();

	getch();
	return 0;
}