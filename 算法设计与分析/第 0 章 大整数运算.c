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
void factorial(int n, int *a, int *len) {
	// n的规模较大， n!的位数也就相应的大，设计数组a[]存储n!的各位数字， a[1]存储各位数字，a[2]存储十位数字,以此类推。
	// n确定后 n!的位数 m 也就确定了, 有：
	/*
		  10m-1 ≤ n! ≤10m-1<10m
                    m-1 ≤lgn!<m
                    m-1 ≤ lg2+lg3+…+lgn <m
         令s=lg2+lg3+…+lgn，则n!的位数m=[s]+1，即要使用数组a[]的m个元素。

	*/
	//求 n! 的位数m
	double s = 0;
	for (int i = 2; i <= n; i++) {
		s += log10(i);
	}
	int m = (int)s + 1;

	for (int i = 0; i <= m; i++)
		a[i] = 0;

	a[1] = 1;

	long long t = 0, g = 0;
	for(int i = 2; i <= n; i++)
		for (int k = 1; k <= m; k++) {
			t = a[k] * i + g;
			a[k] = t % 10;
			g = t / 10;
		}
	
	*len = m;
}

void test02() {

	int n;

	printf("输入正整数n,求n! ");
	scanf("%d", &n);

	int a[1024] = { 0 };
	int m = 0;

	// 求阶乘
	factorial(n, a, &m);

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

// Final Version
/**
* Description：
* 以相等数来划分  最满意的！！！
*	return 1 代表是正数， return 0 代表是负数
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
	if (a == NULL || b == NULL || c == NULL)
		return;

	// 临时
	int temp[1024] = { 0 };
	int temp_len = 0;

	// 保存结果
	int result[1024] = { 0 };
	int result_len = 0;

	// 被除数
	int divi[1024] = { 0 };
	int divi_len = 0;

	while (1) {
		divi[divi_len] = a[divi_len];
		if (sub(divi, divi_len + 1, b, b_len, temp, &temp_len) == 0) {
			divi_len++;

		}
		else {
			divi[divi_len] = 0;
			divi_len--;
		}

		int k = 1;
		int i = 0;
		for (; i <= 9; i++) {
			result[k - 1] = i;
			mul(b, b_len, result, 1, temp, &temp_len);

			if (sub(divi, divi_len + 1, temp, temp_len, temp, &temp_len) == 0) {
				result[k - 1] = i - 1;
				mul(b, b_len, result, 1, temp, &temp_len);
				sub(b, b_len, temp, temp_len, temp, &temp_len);

				break;
			}
		}


	}



	
}

void display(int *a, int len) {
	for (int i = 0; i < len; i++) {
		printf("%d", a[i]);
	}
	printf("\n");
}

// 任意长度的两个数 + - * / 四则运算
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

// 1. 输入一个int型正整数，将其转换成八进制整数
void homework1() {
	int n;

	printf("输入n：");
	scanf("%d", &n);
	printf("十进制数 %d 的八进制表示为：", n);

	int remainder = 0;
	int result[1024] = { 0 };
	int i = 0;

	while (n / 8) {
		result[i++] = n % 8;
		n /= 8;
	}

	result[i] = n;

	
	for (int j = i; j >= 0; j--) {
		printf("%d", result[j]);
	}
	
	printf("\n");

}

// 2. 统计n!中数字为 0 的个数，及尾部数字 0 的个数
void homework2() {
	int n;

	printf("输入正整数n: ");
	scanf("%d", &n);
	int a[1024] = { 0 };
	int m = 0;

	factorial(n, a, &m);

	int num = 0;
	int tailNum = 0;

	printf("\n%d\n", m);

	for (int i = 1; i <= m; i++) {
		if (a[i] == 0)
			num++;
	}

	for (int i = m; i >= 1; i++) {
		if (a[i] == 0) {
			tailNum++;
		}
		else {
			break;
		}
	}

	printf("n!中的数字 0 的个数为： %d 尾部数字为 0 的个数为: %d\n", num, tailNum);

}

// 3.输入一个int型十进制正整数，将其分解为质因素的幂的积，要求表示为质因数从小到大顺序排列的乘积形式。例如：90=2*3ˆ2*5
void homework3() {
	
}

// 4.编程删除数组中的重复元素，即数组中相同的元素只保留一个。示例数组： a[]={45,33,23,33,33,88,66,77,66,66}
void homework4() {
	char data[1024] = { 0 };

	scanf("%[0-9]", data);
	int len = strlen(data);

	// 刷新输入缓冲区
	scanf("%*[^\n]");
	scanf("%*c");

	int a[1024] = { 0 };

	for (int i = 0; i < len; i++) {
		a[i] = (int)data[i] - 48;
	}

	// 先排序
	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j < len; j++) {
			if (a[i] > a[j]) {
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}

	// eg:  a[]={45,33,23,33,33,88,66,77,66,66}
	int k = 0;
	while(k < len-1){

		if (a[k] == a[k + 1]) {
			for (int i = k; i < len - 1; i++) {
				a[i] = a[i + 1];
			}
			len -= 1;
		}
		else {
			k++;
		}

	}
	
		
	for (int i = 0; i < len; i++) {
		printf("%d",  a[i]);
	}
	

	printf("\n");
	
}


int main() {

	//test01();
	//test02();
	test03();
	

	//homework1();
	//homework2();
	//homework3();
	//homework4();


	system("pause");
	return 0;
}