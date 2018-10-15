#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

/*
*
* 例1 计算 n! (n为非负整数)
*
*/

// 情形一: 当n的规模较小的时候 (n < 13)时
void test01() {
	int n;
	printf("请输入n (n < 13)求 n! ");
	scanf("%d", &n);

	unsigned long long s = 1;
	printf("%d\n", sizeof(s));
	for (int i = 1; i <= n; i++) {
		s *= i;
	}

	printf("%d! = %lld\n", n, s);
}


#define N 1024*10
// 情形二: 当n的规模较大的时候
void test02() {
	// n的规模较大， n!的位数也就相应的大，设计数组a[]存储n!的各位数字， a[1]存储各位数字，a[2]存储十位数字,以此类推。
	// n确定后 n!的位数 m 也就确定了, 有：
	/*
		  10m-1 ≤ n! ≤10m-1<10m
                    m-1 ≤lgn!<m
                    m-1 ≤ lg2+lg3+…+lgn <m
         令s=lg2+lg3+…+lgn，则n!的位数m=[s]+1，即要使用数组a[]的m个元素。

	*/
	int n;
	printf("请输入n 求 n! ");
	scanf("%u", &n);

	//求 n! 的位数m
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
* 例2 超长整数运算（大数运算）
* 
*
********************************/


/**
* Description：
*	我们将加法的情况分为了四种
*		（1）两个长度相等的数相加
*		（2）两个长度不相等的数相加
* 
* 采用递归的方式，出口条件就是两个相等的数相加 ！！！
*  例：32455	       55
*     +   43   ==>   + 43  
* 用一个数组保存多余出来的 324, 用另一个数组保存相加结果的进位值
* 然后调用 add([3,2,4], 3, [0], 1, 0)
* 递归下去......
*/
// 方式一
//void add(int *a, int a_len, int *b, int b_len, int *c, int *c_len) {
//
//	// 结果数组的长度
//	int result_len = 0;
//
//	// 保存结果的数组
//	int result[1024] = { 0 };
//
//	// 进位值
//	int carry = 0;
//
//	// 取两数最小的长度
//	int min = 0;
//
//	// 两数相差位数的个数
//	int distance = abs(a_len - b_len);
//
//
//	// 保存相差位数的数组
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
//	// 实现加法运算
//	for (int i = 0; i < min; i++) {
//		result[min - i - 1] = a[a_len - i - 1] + b[b_len - i - 1] + carry;
//		carry = result[min - i - 1] / 10;
//		result[min - i - 1] = result[min - i - 1] % 10;
//	}
//
//	if (distance == 0) {
//
//		// 判断是否产生进位值
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
//		// current_len 代表当前c[] 数组的长度 !!!
//		int current_len = result_len;
//		for (int i = current_len; i < min + current_len; i++) {
//			c[i] = result[i - current_len];
//			result_len++;
//		}
//	}
//
//	*c_len = result_len;
//}

// 方式二
//void add(int *a, int a_len, int *b, int b_len, int *c, int *c_len) {
//	if (a == NULL || b == NULL || c == NULL)
//		return;
//
//	// 相差的位数保存在differ_array 中
//	int differ_array[1024] = { 0 };
//	int carry[1] = { 0 };
//
//	// 保存相加结果
//	int result_array[1024] = { 0 };
//	int result_len = 0;
//
//	// 取两数最小的长度
//	int min = 0;
//
//	// 两数相差位数的个数
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
//	// 加法运算
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

// 使 a, b两数长度相等   用 0 补齐
void make_len_equal(int *in_a, int a_len, int *in_b, int b_len, int *out_a, int *out_b, int *out_len) {

	*out_len = 0;

	int distance = abs(a_len - b_len);

	// 将两数长度改为相等
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

// 方式三 Final Version
// 都转换成相等长度的两个数相加
void add(int *a, int a_len, int *b, int b_len, int *c, int *c_len) {

	int first_number[1024] = { 0 };

	int second_number[1024] = { 0 };

	int result_array[1024] = { 0 };

	int length = 0;

	make_len_equal(a, a_len, b, b_len, first_number, second_number, &length);

	// 加法运算
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
// 方式一 以相等与不相等来划分
//int sub(int *a, int a_len, int *b, int b_len, int *c, int *c_len) {
//	if (a == NULL || b == NULL || c == NULL)
//		return;
//
//	int flag = 1;
//
//	// 相差的位数保存在differ_array 中
//	int differ_array[1024] = { 0 };
//	int borrow[1] = { 0 };
//
//	// 保存相加结果
//	int result_array[1024] = { 0 };
//	int result_len = 0;
//
//	// 取两数最小的长度
//	int min = 0;
//
//	// 两数相差位数的个数
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
//	// 减法运算
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
//			// 将c[0] = 0 这个数一直 去除: a[] = {0, 0, 1} ==>  a[] = {1}
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
* Description：
* 以相等数来划分  最满意的！！！
* 
*	我们将减法的情况分为了两种
*		（1）两个长度相等的数相减
*		（2）两个长度不相等的数相减
* 我们将两数长度设置成相等
* 例： 3112         3112
      -  32  =>  -  0032

	    124		   00124
	 -32454  =>  - 32454

	 转换成这种形式之后 我们就按照减法的运算法则 进行相减   
	 最后我们只要判断  相减之后我们要判断 borrow[0] == 1 ? 
	 （1）如果为 0 则说明相减结果为正数 函数结束
	 （2）如果为 1 则说明相减结果为负数， 这时我们要用一个数组，differ_array[]
		  并且differ_array[0] = 1
		  然后调用 sub(differ_array, length + 1, result_array, length, c_len)
		  其中 length 为二个相减数的长度，result_array 为相减的结果， c_len 为结果的长度
* 例：  0032		
      - 1123
	-------------
		8909    最高位要借 1  所以调用 
									   sub( differ_array,   length + 1, result_array, length, c_len)
												|			   |			   |		  |		  |
												|			   |			   |		  |		  |
									   sub( [1, 0, 0, 0, 0], 4 + 1,     [8, 9, 0, 9],     4,      0  )

	==>
	   10000
	-   8909
   -------------
		1091	
	
	最终 sub() 函数返回 0， 标志是负数。 所以最终结果为 -1091

*
*/
int sub(int *a, int a_len, int *b, int b_len, int *c, int *c_len) {
	if (a == NULL || b == NULL || c == NULL)
		return;
		
	int flag = 1;

	// 减数
	int reduction[1024] = { 0 };
		
	// 被减数
	int subtrahend[1024] = { 0 };

	// 保存相加结果
	int result_array[1024] = { 0 };
	
	int length = 0;

	make_len_equal(a, a_len, b, b_len, subtrahend, reduction, &length);

	// 减法运算
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

		// 将c[0] = 0 这个数一直 去除: a[] = {0, 0, 1} ==>  a[] = {1}
		int result_length = length;
		while (c[0] == 0) {
			for (int i = 0; i < result_length - 1; i++) {
				c[i] = c[i + 1];
			}

			// 防止死循环
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

		// 左移 i  位
		temp[result_len + i] = 0;

		add(c, result_len, temp, a_len + 1 + i, c, &result_len);
	}

	while (c[0] == 0) {
		for (int i = 0; i < result_len - 1; i++) {
			c[i] = c[i + 1];
		}

		// 防止死循环
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

	// 输入第一个数
	printf("输入a: ");
	scanf("%[0-9]", a);

	// 刷新缓冲区、
	// 第一种方式
	//scanf("%*[^\n]");
	//scanf("%*c");
	// 第二种方式
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	// 输入第二个数
	printf("输入b: ");
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

	// 加法
	int add_len = 0;
	add(array_a, a_len, array_b, b_len, c, &add_len);
	printf("a + b = ");
	for (int i = 0; i < add_len; i++) {
		printf("%d", c[i]);
	}
	printf("\n");

	// 减法
	int sub_len = 0;
	printf("a - b = ");
	if (sub(array_a, a_len, array_b, b_len, c, &sub_len) == 0)
		printf("-");
	for (int i = 0; i < sub_len; i++) {
		printf("%d", c[i]);
	}
	printf("\n");

	// 乘法
	printf("a * b = ");
	int mul_len = 0;
	mul(array_a, a_len, array_b, b_len, c, &mul_len);
	for (int i = 0; i < mul_len; i++) {
		printf("%d", c[i]);
	}
	printf("\n");
	// 除法
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