/*
输入
The input is composed of multiple cases, and each case occupies a single line, which contains two integers m and n.
输出
The first line is 123.
Then for each case, the output contains two lines with m in first line and n in second line.
*/
#include <iostream>
using namespace std;
class A {
public:
	int val;

	A(int n){ val = n;}
	A(){val = 123;}
	A & GetObj(){return (*this);}
};
int main()
{
	int m,n;
	A a;
	cout << a.val << endl;
	while(cin >> m >> n) {
		a.GetObj() = m;
		cout << a.val << endl;
		a.GetObj() = A(n);
		cout << a.val<< endl;
	}
	return 0;
}