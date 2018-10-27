#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/******************* 3.2 递推数列 ****************

3.2.1  双关系递推数列
设集合M定义如下:
(1)  1∈M
(2)  x∈M => 2x+1∈M,5x-1∈M
(3)  再无其它的数属于M。
试求集合M元素从小到大排列所得序列的第n（n<10000）项与前n项之和。

*/
void test3_2_1() {
	
	// 枚举实现
	// 枚举变量 k
	int n = 0;
	printf("请输入 n: ");
	scanf("%d", &n);

	/*int i = 1;
	long long m[1024] = { 0 };
	long long k = 1, s = 1;
	m[1] = 1;
	while (i < n) {
		k++;
		for (int j = 1; j <= i; j++)
			if (k == 2 * m[j] + 1 || k == 5 * m[j] - 1) {
				i++;
				m[i] = k;
				s += k;
				break;
			}
	}
	printf("m(%d) = %lld, s=%lld\n", n, m[n], s);*/
	

	// 递推实现
	long long m[10000] = { 0 };
	m[1] = 1;
	int p2 = 1;
	int p5 = 1;
	long long s = 1;
	for (int i = 2; i <= n; i++) {
		long long t2 = 2 * m[p2] + 1;
		long long t5 = 5 * m[p5] - 1;
		if (t2 < t5) {
			m[i] = t2;
			p2++;
		}
		else {
			m[i] = t5;
			if (t2 == t5)
				p2++;
			p5++;
		}

		s += m[i];
	}

	printf("m(%d)=%lld, s = %lld\n", n, m[n], s);
}


int main(void) {
	//test3_2_1();

	system("pause");
	return 0;
}