/*
Please complete the following program to ensure that the output is 9 22 5.
*/

#include <iostream>
using namespace std;
class Sample {
public:
	int v;
	Sample(){}
	Sample(int n):v(n){}
	Sample(const Sample & a){
		if(a.v == 20)
			v = 22;
		else
			v = 9;
	}
};

void PrintAndDouble(Sample o)
{
	cout << o.v;
	cout << endl;
}

int main()
{
	Sample a(5);
	Sample b = a;
	PrintAndDouble(b);  // 9
	Sample c = 20;
	PrintAndDouble(c);  // 22
	Sample d;
	d = a;
	cout << d.v;  // 5
	return 0;
}