/*
输入
There are multiple cases, and each case occupies a line with a single integer.
输出
For each case, the output contains two same lines with the input integer printed two times seperated by comma in each line.
*/

#include <iostream>
#include <string>
using namespace std;
class Base {
public:
	int k;
	Base(int n):k(n) {}
};
class Big
{
public:
	int v;
	Base b;
	//Base b = 0;
	Big(int n):v(n),b(n){}
};
int main()
{
	int n;
	while(cin >>n) {
		Big a1(n);
		Big a2 = a1;
		cout << a1.v << "," << a1.b.k << endl;
		cout << a2.v << "," << a2.b.k << endl;
	}
}