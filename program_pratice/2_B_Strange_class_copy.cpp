/*
Please complete the following program to ensure that the output is 9 22 5.
*/

#include <iostream>
using namespace std;
class Sample {
public:
	int v;
    void PrintAndDouble(Sample a){
        
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
	PrintAndDouble(b);
	Sample c = 20;
	PrintAndDouble(c);
	Sample d;
	d = a;
	cout << d.v;
	return 0;
}