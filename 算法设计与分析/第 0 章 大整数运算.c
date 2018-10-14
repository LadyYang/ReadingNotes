#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

/*
*
* ��1 ���� n! (nΪ�Ǹ�����)
*
*/

// ����һ: ��n�Ĺ�ģ��С��ʱ�� (n < 13)ʱ
void test01() {
	int n;
	printf("������n (n < 13)�� n! ");
	scanf("%d", &n);

	unsigned long long s = 1;
	printf("%d\n", sizeof(s));
	for (int i = 1; i <= n; i++) {
		s *= i;
	}

	printf("%d! = %lld\n", n, s);
}


#define N 1024*10
// ���ζ�: ��n�Ĺ�ģ�ϴ��ʱ��
void test02() {
	// n�Ĺ�ģ�ϴ� n!��λ��Ҳ����Ӧ�Ĵ��������a[]�洢n!�ĸ�λ���֣� a[1]�洢��λ���֣�a[2]�洢ʮλ����,�Դ����ơ�
	// nȷ���� n!��λ�� m Ҳ��ȷ����, �У�
	/*
		  10m-1 �� n! ��10m-1<10m
                    m-1 ��lgn!<m
                    m-1 �� lg2+lg3+��+lgn <m
         ��s=lg2+lg3+��+lgn����n!��λ��m=[s]+1����Ҫʹ������a[]��m��Ԫ�ء�

	*/
	int n;
	printf("������n �� n! ");
	scanf("%u", &n);

	//�� n! ��λ��m
	double s = 0;
	for (int i = 2; i <= n; i++) {
		s += log10(i);
	}
	int m = (int)s + 1;

	int a[N] = { 0 };
	a[1] = 1;

	long long t = 0, g = 0;
	for(int i = 2; i <= n; i++)
		for (int k = 1; k <= m; k++) {
			t = a[k] * i + g;
			a[k] = t % 10;
			g = t / 10;
		}
	printf("m = %d", m);

	printf("%d != ", n);
	for (int k = m; k >= 1; k--) {
		printf("%1d", a[k]);
	}
	printf("\n");
}


/*******************************
*
* ��2 �����������㣨�������㣩
* 
*
********************************/


/**
* Description��
*	���ǽ��ӷ��������Ϊ������
*		��1������������ȵ������
*		��2���������Ȳ���ȵ������
* 
* ���õݹ�ķ�ʽ��������������������ȵ������ ������
*  ����32455	       55
*     +   43   ==>   + 43  
* ��һ�����鱣���������� 324, ����һ�����鱣����ӽ���Ľ�λֵ
* Ȼ����� add([3,2,4], 3, [0], 1, 0)
* �ݹ���ȥ......
*/
// ��ʽһ
//void add(int *a, int a_len, int *b, int b_len, int *c, int *c_len) {
//
//	// �������ĳ���
//	int result_len = 0;
//
//	// ������������
//	int result[1024] = { 0 };
//
//	// ��λֵ
//	int carry = 0;
//
//	// ȡ������С�ĳ���
//	int min = 0;
//
//	// �������λ���ĸ���
//	int distance = abs(a_len - b_len);
//
//
//	// �������λ��������
//	int array_dis[1024] = { 0 };
//	if (a_len > b_len) {
//		min = b_len;
//
//		for (int i = 0; i < distance; i++) {
//			array_dis[i] = a[i];
//		}
//	}
//	else {
//		min = a_len;
//
//		for (int i = 0; i < distance; i++) {
//			array_dis[i] = b[i];
//		}
//	}
//
//	// ʵ�ּӷ�����
//	for (int i = 0; i < min; i++) {
//		result[min - i - 1] = a[a_len - i - 1] + b[b_len - i - 1] + carry;
//		carry = result[min - i - 1] / 10;
//		result[min - i - 1] = result[min - i - 1] % 10;
//	}
//
//	if (distance == 0) {
//
//		// �ж��Ƿ������λֵ
//		if (carry != 0) {
//			c[0] = carry;
//			result_len++;
//
//			for (int i = 1; i <= min; i++) {
//				c[i] = result[i - 1];
//				result_len++;
//			}
//		}
//		else {
//			for (int i = 0; i < min; i++) {
//				c[i] = result[i];
//				result_len++;
//			}
//		}
//
//	}
//	else {
//		
//		if (carry != 0) {
//			int temp_b[1] = { carry };
//			add(array_dis, distance, temp_b, 1, c, &result_len);
//		}
//		else {
//			for (int i = 0; i < distance; i++) {
//				c[i] = array_dis[i];
//				result_len++;
//			}
//		}
//
//		// current_len ����ǰc[] ����ĳ��� !!!
//		int current_len = result_len;
//		for (int i = current_len; i < min + current_len; i++) {
//			c[i] = result[i - current_len];
//			result_len++;
//		}
//	}
//
//	*c_len = result_len;
//}

// ��ʽ��
//void add(int *a, int a_len, int *b, int b_len, int *c, int *c_len) {
//	if (a == NULL || b == NULL || c == NULL)
//		return;
//
//	// ����λ��������differ_array ��
//	int differ_array[1024] = { 0 };
//	int carry[1] = { 0 };
//
//	// ������ӽ��
//	int result_array[1024] = { 0 };
//	int result_len = 0;
//
//	// ȡ������С�ĳ���
//	int min = 0;
//
//	// �������λ���ĸ���
//	int distance = abs(a_len - b_len);
//
//	if (a_len > b_len) {
//		min = b_len;
//
//		for (int i = 0; i < distance; i++) {
//			differ_array[i] = a[i];
//		}
//	}
//	else {
//		min = a_len;
//
//		for (int i = 0; i < distance; i++) {
//			differ_array[i] = b[i];
//		}
//	}
//
//	// �ӷ�����
//	for (int i = 0; i < min; i++) {
//		result_array[min - i - 1] = a[a_len - i - 1] + b[b_len - i - 1] + carry[0];
//		carry[0] = result_array[min - i - 1] / 10;
//		result_array[min - i - 1] = result_array[min - i - 1] % 10;
//	}
//
//	if (distance == 0) {
//		if (carry[0] == 0) {
//			for (int i = 0; i < min; i++) {
//				c[i] = result_array[i];
//				result_len++;
//			}
//		}
//		else {
//			c[0] = carry[0];
//			result_len++;
//
//			for (int i = 1; i <= min; i++) {
//				c[i] = result_array[i - 1];
//				result_len++;
//			}
//		}
//	}
//	else {
//		add(differ_array, distance, carry, 1, c, &result_len);
//
//		int current_len = result_len;
//		for (int i = current_len; i < min + current_len; i++) {
//			c[i] = result_array[i - current_len];
//			result_len++;
//		}
//	}
//
//	if (c_len != NULL)
//		*c_len = result_len;
//}

// ʹ a, b�����������   �� 0 ����
void make_len_equal(int *in_a, int a_len, int *in_b, int b_len, int *out_a, int *out_b, int *out_len) {

	*out_len = 0;

	int distance = abs(a_len - b_len);

	// ���������ȸ�Ϊ���
	if (a_len > b_len) {
		*out_len = a_len;

		for (int i = 0; i < distance; i++) {
			out_b[i] = 0;
		}
		for (int i = distance; i < *out_len; i++) {
			out_b[i] = in_b[i - distance];
		}
		for (int i = 0; i < *out_len; i++) {
			out_a[i] = in_a[i];
		}
	}
	else {
		*out_len = b_len;

		for (int i = 0; i < distance; i++) {
			out_a[i] = 0;
		}

		for (int i = distance; i < *out_len; i++) {
			out_a[i] = in_a[i - distance];
		}

		for (int i = 0; i < *out_len; i++) {
			out_b[i] = in_b[i];
		}
	}
}

// ��ʽ�� Final Version
// ��ת������ȳ��ȵ����������
void add(int *a, int a_len, int *b, int b_len, int *c, int *c_len) {

	int first_number[1024] = { 0 };

	int second_number[1024] = { 0 };

	int result_array[1024] = { 0 };

	int length = 0;

	make_len_equal(a, a_len, b, b_len, first_number, second_number, &length);

	// �ӷ�����
	int carry = 0;
	for (int i = length - 1; i >= 0; i--) {
		result_array[i] = first_number[i] + second_number[i] + carry;
		carry = result_array[i] / 10;
		result_array[i] %= 10;
	}

	if (carry == 0) {
		for (int i = 0; i < length; i++) {
			c[i] = result_array[i];
		}
	}
	else {
		c[0] = carry;
		length++;

		for (int i = 1; i < length; i++) {
			c[i] = result_array[i - 1];
		}
	}


	*c_len = length;
	return;
}

// return 0 is minus, return others is positive number
// ��ʽһ ������벻���������
//int sub(int *a, int a_len, int *b, int b_len, int *c, int *c_len) {
//	if (a == NULL || b == NULL || c == NULL)
//		return;
//
//	int flag = 1;
//
//	// ����λ��������differ_array ��
//	int differ_array[1024] = { 0 };
//	int borrow[1] = { 0 };
//
//	// ������ӽ��
//	int result_array[1024] = { 0 };
//	int result_len = 0;
//
//	// ȡ������С�ĳ���
//	int min = 0;
//
//	// �������λ���ĸ���
//	int distance = abs(a_len - b_len);
//
//	if (a_len > b_len) {
//		min = b_len;
//
//		for (int i = 0; i < distance; i++) {
//			differ_array[i] = a[i];
//		}
//	}
//	else {
//		min = a_len;
//		flag = 0;
//
//		for (int i = 0; i < distance; i++) {
//			differ_array[i] = b[i];
//		}
//	}
//
//	// ��������
//	for (int i = 0; i < min; i++) {
//		result_array[min - i - 1] = a[a_len - i - 1] - b[b_len - i - 1] - borrow[0];
//
//		if (result_array[min - i - 1] < 0) {
//			borrow[0] = 1;
//			result_array[min - i - 1] = result_array[min - i - 1] + 10;
//		}
//		else {
//			borrow[0] = 0;
//		}
//	}
//
//	if (distance == 0) {
//		if (borrow[0] == 0) {
//			flag = 1;
//
//			for (int i = 0; i < min; i++) {
//				c[i] = result_array[i];
//				result_len++;
//			}
//
//			// ��c[0] = 0 �����һֱ ȥ��: a[] = {0, 0, 1} ==>  a[] = {1}
//			while (c[0] == 0) {
//				for (int i = 0; i < min - 1; i++) {
//					c[i] = c[i + 1];
//				}
//				if (--result_len == 0)
//					break;
//			}
//			
//		}
//		else {
//			flag = 0;
//
//			differ_array[0] = 1;
//			for (int i = 1; i <= min; i++) {
//				differ_array[i] = 0;
//			}
//			sub(differ_array, min + 1, result_array, min, c, &result_len);
//		}
//	}
//	else {
//		
//		if (a_len > b_len) {
//			sub(differ_array, distance, borrow, 1, c, &result_len);
//
//			int current_len = result_len;
//			for (int i = current_len; i < min + current_len; i++) {
//				c[i] = result_array[i - current_len];
//				result_len++;
//			}
//		}
//		else {
//			flag = 0;
//			int differ_len = distance;
//
//
//			add(differ_array, distance, borrow, 1, differ_array, &differ_len);
//
//			for (int i = differ_len, temp_len = differ_len; i < min + temp_len; i++) {
//				differ_array[i] = 0;
//				differ_len++;
//			}
//
//			
//			sub(differ_array, differ_len, result_array, min, c, &result_len);
//		}
//	}
//
//	*c_len = result_len;
//	return flag;
//}

// Final Version
/**
* Description��
* �������������  ������ģ�����
* 
*	���ǽ������������Ϊ������
*		��1������������ȵ������
*		��2���������Ȳ���ȵ������
* ���ǽ������������ó����
* ���� 3112         3112
      -  32  =>  -  0032

	    124		   00124
	 -32454  =>  - 32454

	 ת����������ʽ֮�� ���ǾͰ��ռ��������㷨�� �������   
	 �������ֻҪ�ж�  ���֮������Ҫ�ж� borrow[0] == 1 ? 
	 ��1�����Ϊ 0 ��˵��������Ϊ���� ��������
	 ��2�����Ϊ 1 ��˵��������Ϊ������ ��ʱ����Ҫ��һ�����飬differ_array[]
		  ����differ_array[0] = 1
		  Ȼ����� sub(differ_array, length + 1, result_array, length, c_len)
		  ���� length Ϊ����������ĳ��ȣ�result_array Ϊ����Ľ���� c_len Ϊ����ĳ���
* ����  0032		
      - 1123
	-------------
		8909    ���λҪ�� 1  ���Ե��� 
									   sub( differ_array,   length + 1, result_array, length, c_len)
												|			   |			   |		  |		  |
												|			   |			   |		  |		  |
									   sub( [1, 0, 0, 0, 0], 4 + 1,     [8, 9, 0, 9],     4,      0  )

	==>
	   10000
	-   8909
   -------------
		1091	
	
	���� sub() �������� 0�� ��־�Ǹ����� �������ս��Ϊ -1091

*
*/
int sub(int *a, int a_len, int *b, int b_len, int *c, int *c_len) {
	if (a == NULL || b == NULL || c == NULL)
		return;
		
	int flag = 1;

	// ����
	int reduction[1024] = { 0 };
		
	// ������
	int subtrahend[1024] = { 0 };

	// ������ӽ��
	int result_array[1024] = { 0 };
	
	int length = 0;

	make_len_equal(a, a_len, b, b_len, subtrahend, reduction, &length);

	// ��������
	int borrow = 0;
	for (int i = length - 1; i >= 0; i--) {
		result_array[i] = subtrahend[i] - reduction[i] - borrow;
		
		if (result_array[i] < 0) {
			borrow = 1;
			result_array[i] += 10;
		}
		else {
			borrow = 0;
		}
	}
		
	if (borrow == 0) {
		flag = 1;

		for (int i = 0; i < length; i++) {
			c[i] = result_array[i];
		}

		// ��c[0] = 0 �����һֱ ȥ��: a[] = {0, 0, 1} ==>  a[] = {1}
		int result_length = length;
		while (c[0] == 0) {
			for (int i = 0; i < result_length - 1; i++) {
				c[i] = c[i + 1];
			}

			// ��ֹ��ѭ��
			if (result_length == 1)
				break;

			result_length--;
		}

		*c_len = result_length;
	}
	else {
		flag = 0;

		int differ_array[1024] = { 1 };
		
		sub(differ_array, length + 1, result_array, length, c, c_len);
	}

	return flag;
}

void mul(int *a, int a_len, int *b, int b_len, int *c, int *c_len) {

	int result_len = a_len + 1;

	for (int i = 0; i < a_len + 1; i++) {
		c[i] = 0;
	}

	for (int i = 0; i < b_len; i++) {
		int temp[1024] = { 0 };
		int carry = 0;

		for (int j = 0; j < a_len; j++) {
			temp[a_len - j] = a[a_len - j - 1] * b[b_len - i - 1] + carry;
			carry = temp[a_len - j] / 10;
			temp[a_len - j] %= 10;
		}

		temp[0] = carry;

		// ���� i  λ
		temp[result_len + i] = 0;

		add(c, result_len, temp, a_len + 1 + i, c, &result_len);
	}

	while (c[0] == 0) {
		for (int i = 0; i < result_len - 1; i++) {
			c[i] = c[i + 1];
		}

		// ��ֹ��ѭ��
		if (result_len == 1)
			break;

		result_len--;
	}

	*c_len = result_len;

}

void div(int *a, int a_len, int *b, int b_len, int *c, int *c_len) {

}

void display(int *a, int len) {
	for (int i = 0; i < len; i++) {
		printf("%d", a[i]);
	}
	printf("\n");
}

void test03() {
	// 
	/*int a[] = { 1234, 345, 2367, 98 };
	int b[] = { 213, 6543, 576, 9786 };
	int c[1024] = { 0 };*/
	char a[1024] = { 0 };
	char b[1024] = { 0 };

	// �����һ����
	printf("����a: ");
	scanf("%[0-9]", a);

	// ˢ�»�������
	// ��һ�ַ�ʽ
	//scanf("%*[^\n]");
	//scanf("%*c");
	// �ڶ��ַ�ʽ
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	// ����ڶ�����
	printf("����b: ");
	scanf("%[0-9]", b);
	
	int a_len = strlen(a);
	int b_len = strlen(b);

	int *array_a = (int*)malloc(a_len * sizeof(int));
	int *array_b = (int*)malloc(b_len * sizeof(int));

	for (int i = 0; i < a_len; i++)
		*(array_a + i) = (int)a[i] - 48;

	for (int i = 0; i < b_len; i++)
		*(array_b + i) = (int)b[i] - 48;



	int c[1024] = { 0 };

	// �ӷ�
	int add_len = 0;
	add(array_a, a_len, array_b, b_len, c, &add_len);
	printf("a + b = ");
	for (int i = 0; i < add_len; i++) {
		printf("%d", c[i]);
	}
	printf("\n");

	// ����
	int sub_len = 0;
	printf("a - b = ");
	if (sub(array_a, a_len, array_b, b_len, c, &sub_len) == 0)
		printf("-");
	for (int i = 0; i < sub_len; i++) {
		printf("%d", c[i]);
	}
	printf("\n");

	// �˷�
	printf("a * b = ");
	int mul_len = 0;
	mul(array_a, a_len, array_b, b_len, c, &mul_len);
	for (int i = 0; i < mul_len; i++) {
		printf("%d", c[i]);
	}
	printf("\n");
	// ����
	printf("a / b = ");
	int div_len = 0;
	div(array_a, a_len, array_b, b_len, c, &div_len);
	for (int i = 0; i < div_len; i++) {
		printf("%d", c[i]);
	}
	printf("\n");


	free(array_a);
	free(array_b);
}

int main() {

	//test01();
	//test02();
	test03();

	system("pause");
	return 0;
}