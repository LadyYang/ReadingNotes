#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

/******************* 2.1 ���Ա����߼��ṹ ********************

2.1.1 ���Ա��壺������ͬ���Ե�����Ԫ�ص�һ����������
	eg: (a1��a2������ai��ai+1������an)

2.1.2 ���Ա�ĳ�����������
	ADT List
	{
		���ݶ���:
			D = { ai | 1<=i<=n, n>=0, aiΪElemTpe���� }
		���ݹ�ϵ:
			R = { <ai, ai+1> | ai��ai+1��D , i=1,...,n-1 }
		��������:
			InitList(&L): ��ʼ�����Ա�����һ���յ����Ա� L��
			DestoryList(&L): �������Ա��ͷ����Ա� L ռ�õ��ڴ�ռ䡣
			ListEmpty(L): �ж����Ա��Ƿ�ձ��� L Ϊ�ձ��򷵻��棬���򷵻ؼ١�
			ListLength(L): �����Ա�ĳ��ȣ����� L ��Ԫ�صĸ�����
			DispList(L): ������Ա��� L ��Ϊ��ʱ˳����ʾ L �и�����ֵ��
			GetElem(L, i, &e): �����ĳ������Ԫ��ֵ���� e ����L�е�i(1<=i<=n)��Ԫ�ص�ֵ��
			LocateElem(L, e): ��Ԫ��ֵ���ң�����L�е�һ��ֵ����e��ȵ�Ԫ�ص���ţ���������Ԫ�ز����ڣ��򷵻�ֵΪ0��
			ListInsert(&L, i, e): ��������Ԫ�أ���L�ĵ�i��1<=i<=n+1)��λ�ò���һ���µ�Ԫ��e��L�ĳ�����1��
			ListDelete(&L, i, &e): ɾ������Ԫ�أ�ɾ��L�ĵ�i(i<=i<=n)��Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1��

	}


	// ���� LA, LB �Ĳ������뵽�� LC ��
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


void test2_1() {
	printf(" 2.1 ���Ա����߼��ṹ\n");
	
}



/******************** 2.2 ���Ա��˳��洢�ṹ ********************

���Ա��˳��洢�ṹ����õĴ洢��ʽ����ֱ�ӽ����Ա���߼��ṹӳ�䵽�洢�ṹ�ϡ�

2.2.1 ���Ա��˳��洢�ṹ--˳���
	���Ա��˳��洢�ṹ���Ϊ˳���(sequential list)

2.2.2 ˳�����������ʵ��


	
*/
#define MaxSize 50
typedef int ElemType;

typedef struct {
	ElemType data[MaxSize];
	int length;
}SqList;

// 1. ����˳���
// ��a�е�n��Ԫ�ؽ���˳���
void CreateList(SqList * &L, ElemType a[], int n) {
	int i = 0, k = 0;

	L = (SqList*)malloc(sizeof(SqList));
	while (i < n) {
		L->data[k] = a[i];
		k++;
		i++;
	}

	L->length = k;
}

// 2. ˳�����������㷨
// ��ʼ�����Ա�
void InitList(SqList* &L) {
	L = (SqList*)malloc(sizeof(SqList));
	L->length = 0;
}

// �������Ա�
void DestoryList(SqList* &L) {
	free(L);
}

// �ж����Ա��Ƿ�Ϊ�ձ�
bool ListEmpty(SqList* L) {
	return (L->length == 0);
}

// �����Ա�ĳ���
int ListLength(SqList * L) {
	return (L->length);
}

// ������Ա�
void DispList(SqList * L) {
	for (int i = 0; i < L->length; i++) {
		printf("%d", L->data[i]);
	}

	printf("\n");
}

// �����Ա��е�ĳ������Ԫ��ֵ
bool GetElem(SqList *L, int i, ElemType & e) {
	if (i < 1 || i > L->length)
		return false;

	e = L->data[i - 1];
	return true;
}


// ��Ԫ��ֵ����
int LocateElem(SqList * L, ElemType e) {
	int i = 0;

	while (i < L->length && L->data[i] != e)
		i++;

	if (i >= L->length)
		return 0;
	else
		return i + 1;
}

// ��������Ԫ��
bool ListInsert(SqList * &L, int i, ElemType e) {
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





void test2_2() {
	printf("\n 2.2 ���Ա��˳��洢�ṹ\n");



}

/********************************************************/
int main(void) {

	//test2_1();
	test2_2();



	getch();
	return 0;
}
