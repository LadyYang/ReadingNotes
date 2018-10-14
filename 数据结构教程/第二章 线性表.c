#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

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

*/

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
