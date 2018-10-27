#include <iostream>
using namespace std;


void test2_1_1() {
	/*
	* 类型int、long、long long和short的区别是什么？
	* 无符号类型和带符号类型的区别是什么？float和double的区别是什么？
	*/


	cout << " 练习2.1 " << endl << endl;
	// 首先我们要明白一个知识点，在内存中数据都是以二进制的形式
	// 存放。
	// 在C++中基本类型只有整型（字符和布尔也属于）和浮点型

	// int、long、long long都是一种数据类型说到底区别就是当用来
	// 声明变量的时候，变量在内存中占据的位数是不一样的。
	cout << "sizeof(int) = " << sizeof(int) << endl;
	cout << "sizeof(long) = " << sizeof(long) << endl;
	cout << "sizeof(long long) = " << sizeof(long long) << endl;

	// 首先我们要弄清楚数据类型的概念。
	// 类型决定了数据所占的比特数以及该如何解释这些比特的内容。
	// 以为数据在内存中都是以二进制的形式存放的，计算机并不知道
	// 该数据是文字、图像、视频等。当我们声明一个变量时，机器就
	// 根据这个变量的类型对这块内存进行解释。所以数据类型就是值
	// 的集合，和在这个集合上所进行的一组操作。
	// 比如整型可以进行四则运算，对象可以根据程序员设定的成员函
	// 数进行一些运算。

	// 无符号类型和有符号类型的区别就是对符号位的处理不同。
	// 在计算机中整数是以补码的形式进行存放的，正数的补码
	// 和负数的补码是不一样的，当表示负数是数据位的最高位
	// 要表示符号位，所以整个数据长度所表示的位数就减少了。
	cout << "unsigned char = " << sizeof(unsigned char) << endl;
	cout << "signed char = " << sizeof(signed char) << endl;

	cout << endl << "有符号和无符号对数据的解释是不一样的：" << endl;
	unsigned char a = 0x41;
	signed char b = 0x41;
	printf("%#x, %#x\n", a, b);
}

void test2_1_2() {
	signed char c = 256;

	cout << c + 1 << endl;

	// unsigned == unsigned int
	unsigned u = 10, u2 = 42;
	cout << u2 - u << endl;
	cout << u - u2 << endl;

	int i = 10, i2 = 42;
	cout << i2 - i << endl;
	cout << i - i2 << endl;
	cout << i - u << endl;
	cout << u - i << endl;

	// 如果表达式中既有有符号数又有无符号数，这带符号会自动转换成无符号数。
}

void test2_1_3() {
	char a1 = 'a';
	wchar_t a2 = L'a';
	const char * a3 = "a";
	const wchar_t * a4 = L"a";

	int b1 = 3U;
	cout << b1 << endl;


}

void test2_2_1() {
	// 在C++中对象表示的是具有某种数据类型的内存空间
	// 列表初始化 C++11
	
	// int i{ 3.3 }; error

	// 对象的类型决定了对象所能参与的运算，什么一个变量是告诉编译器
	// 这个变量所能执行的运算，并进行严格的控制。所以一个变量可以重复
	// 的声明，但不能重复的定义。因为定义是对变量分配内存空间和初始化。

}

// 变量的定义包括一个基本类型和一组声明符。
// 面对一条比较复杂的指针和引用的声明语句时，往往从变量名开始从右往左分析。

void test2_4() {
	double dval = 3.14;
	const int &ri = dval;

	using aa = int;
	aa l;

	l = 3;
	cout << l << endl;

	typedef char *pstring;

	const pstring cstr = 0;

	char * const cstr2 = 0;

	char c = 'c';

	// cstr = &c; error
	// cstr2 = cstr; error
}

void test2_5() {
	int a = 3;
	int *b = &a;
	
	decltype(a) c = a;

	++c;

	cout << "c = " << c << endl;

	using my_int = int *&;

	my_int a = b;

}

int main() {
	//test2_1_1();
	//test2_1_2();
	//test2_1_3();


	//test2_2_1();
	//test2_4();
	//test2_5();




	system("pause");
	return 0;
}