#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cctype>
using namespace std;

/********* 3.2 ��׼������ string ***************/
void test3_2() {

	// ����ͳ�ʼ��
	{
		int n = 10;
		string s1;
		string s2 = s1;
		string s3 = "value";
		string s4(n, 'c');
	}

	// string �����ϵĲ���
	// ���;���һ��ֵ�ü��ϣ��������ֵ�ü����������Ĳ���
	{

		//string s;
		//cin >> s;
		//cout << s << endl;


		//string s1, s2;
		//cin >> s1 >> s2;
		//cout << s1 << s2 << endl;

		//string word;
		//while (cin >> word)
		//	cout << word << endl;

		// getline ��ȡһ�� �������з�����
		//string line;
		//while (getline(cin, line))
		//	cout << line << endl;

		//string line;
		//while (getline(cin, line))
		//	if (!line.empty())
		//		cout << line << endl;

		//string s;
		//auto a = s.size();


		//string s = "Hello world ! !";
		//decltype(s.size()) num = 0;
		//for (auto c : s) {
		//	if (ispunct(c))
		//		num++;
		//}
		//cout << num << endl;

		//string s("hello World!@!!");
		//for (auto &c : s)
		//	c = toupper(c);
		//cout << s << endl;

		//string s = "hello World";
		//for (decltype(s.size()) index = 0; index != s.size() && !isspace(s[index]); ++index) {
		//	s[index] = toupper(s[index]);
		//}
		//cout << s << endl;

		const string hexdigits = "0123456789ABCDEF";
		string result;
		string::size_type n;
		while (cin >> n)
			if (n < hexdigits.size())
				result += hexdigits[n];
		cout << result << endl;
	}




}

/*********** 3.3 ��׼������ vector **************/
void test3_3() {
	vector<int> ivec(10);
	vector<string> svec(10);

}

int main() {

	//test3_2();

	test3_3();

	system("pause");
	return 0;
}