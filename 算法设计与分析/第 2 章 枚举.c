#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

/**
*
* 枚举：其基本思想就是逐一列举问题的所有情形，
*		并根据问题提出的条件逐一检验哪些问题的解。
*
* 枚举的模式：（1）区间枚举
*					n = 0;
*　　				for(k=<区间下限>; k<=<区间上限>; k++)
*					{
*						<运算操作序列>;
*　　　　				if(<约束条件>){
*							printf(<满足要求的解>);
*							n++;
*						}
*　　				}
*					printf(<解的个数>);
*			  （2）递增枚举
*					k = 0;
*					while(1) {
*						k++;
*						<运算操作序列>;
*						if(<序列约束>) {
*							printf(<满足要求的解>);
*							return;
*						}
*					}
*		
*
*
*/


/*********** 2.2 统计求和 *************/

// 2.2.1 同码小数 
// 整数部分为零，小数部分各位数字相同的小数称为同码小数。
// 例如0.3，0.33，0.333，...是同数码3的小数。
// 记：
//	s(d,n)= 0.d+0.dd+0.ddd+…+0.dd…d
//	w(d,n)=0.d+2×0.dd+3×0.ddd+…+n×0.dd…d
//	两和式为n项之和，其中第k项小数点后有k个数字d，加权和第k项的权系数为k
// Q&A:
//	依次输入整数d(1≤d≤9)，n(1≤n<10000)
//	(1)求s(d,n)与w(d,n)（四舍五入精确到小数点后6位）。
//  (2)试精确求和s(d,n)与w(d,n)。
void test2_2_1() {
	int d = 0, n = 0;

	printf("输入整数d, n ");
	scanf("%d %d", &d, &n);

	double s = 0;
	double w = 0;
	double t = 0;

	for (int i = 1; i <= n; i++) {

		// t为s的第i项
		t = t/10 + 0.1*d;
		s += t;
		w += t * i;
	}

	printf("四舍五入精确到小数点后6位的结果是: \n");
	printf("s(%d, %d) = %.6f\n", d, n, s);
	printf("w(%d, %d) = %.6f\n", d, n, w);

	// 问题2
	// 用数组来保存结果
	long t2 = 0, s2[1024] = { 0 }, w2[1024] = { 0 };

	for (int i = n; i >= 1; i--) {
		t2 = t2 + i;
		s2[i] = (n - i + 1) * d;
		w2[i] = t2 * d;
	}

	for (int i = n; i >= 1; i--) {
		s2[i - 1] = s2[i - 1] + s2[i] / 10;
		s2[i] = s2[i] % 10;
		w2[i - 1] = w2[i - 1] + w2[i] / 10;
		w2[i] = w2[i] % 10;
	}

	int m = 10; // 比较相应小数位上相等的位数
	for (int i = 1; i <= n; i++) {
		if (w2[i] == s2[i])
			m++;
	}

	printf("精确结果：\n");
	printf("s2(%d, %d) = %ld.", d, n, s2[0]);
	for (int i = 1; i <= n; i++)
		printf("%ld", s2[i]);
	
	printf("\nw2(%d, %d) = %ld.", d, n, w2[0]);
	for (int i = 1; i <= n; i++)
		printf("%ld", w2[i]);

	return;
}

// 2.2.2 三角网格
// 把一个正三角形的三边分成 n 等分，分别与各边平行连接各分点，得 n-三角网格。
// 对指定正整数 n，试求 n-三角网格中所有不同三角形（大小不同或方位不同）的个数，
// 以及所有这些三角形的面积之和（约定网格中最小的单位三角形的面积为 1）。
void test2_2_2() {

	int n = 0;
	printf(" 输入正整数 n：");
	scanf("%d", &n);

	int p[1000] = { 0 };
	for (int t = 0, k = 1; k <= n; k++) {
		t = t + (2 * k - 1);
		p[k] = t;
	}

	int t1 = 0, s1 = 0, ss1 = 0;
	for (int k = 1; k <= n; k++) {
		t1 = t1 + k;
		s1 = s1 + t1;
		ss1 = ss1 + t1 * p[n + 1 - k];
	}

	int m = (n % 2 == 0 ? 1 : 2);
	int t2 = 0, u = 0, s2 = 0, ss2 = 0;
	for (int k = m; k <= n - 1; k = k + 2) {
		t2 = t2 + (k - 1) + k;
		u = (n + 1 - k) / 2;
		s2 = s2 + t2;
		ss2 = ss2 + t2 * p[u];
	}

	printf("三角网格中共有三角形个数为：%ld \n", s1 + s2);
	printf("三角网格中所有三角面积之和为：%ld\n", ss1 + ss2);

}


/************ 2.3 整数搜索 ***************/

// 2.3.1 整数对
// 设b是正整数a去掉一个数字后的正整数，
// 对于给出的正整数n，寻求满足和式a+b=n的所有正整数对a,b。
// 例如，n = 34, 则满足的有（27,7）、（31,3）、（32,2）
void test2_3_1() {
	int n = 0;
	printf("输入整数 n: ");
	scanf("%d", &n);

	// a = n - b;
	int a = 0,
		b = 0,
		d = 0,
		t = 0,
		k = 0;
	for (a = n / 2; a <= n - 1; a++) {
		b = n - a;
		k = 1;

		while (a > t) {
			d = a / (t * 10)*t + a % t;

			if (d == b) {
				k++;
				printf("(%ld, %ld)", a, b);
				break;
			}

			t *= 10;
		}
	}

	printf("\n %ld 共有以上%\d个解\n", n, k);
}

// 佩尔方程求解
void test2_4_1() {
	double x = 0, y = 0;
	int n;
	printf("输入 n: ");
	scanf("%d", &n);

	while (1) {
		y++;
		double t = n * y * y + 1;
		x = floor(sqrt(t));
		if (x*x == t) {
			printf("方程 x^2 - %dy^2 = 1 的基本解为 x = %f, y = %f\n", n, x, y);
			break;
		}

		if (x > 1000000000) {
			printf("没有解\n");
			return;
		}
	}
}
/**************************************/
int main() {

	//test2_3_1();
	test2_4_1();


	getch();
	return 0;
}
