/*
Please complete the following program to ensure that the output is 4 5 1.
*/
#include <iostream>
using namespace std;
class Apple {
	public:
    static int nTotalNumber;
    Apple(){++nTotalNumber;}
	~Apple(){--nTotalNumber;}
    //Apple(Apple & a){}


static void PrintTotal() {
		cout << nTotalNumber << endl; 
	}

};
int Apple::nTotalNumber = 0;
Apple Fun(const Apple & a) {
	a.PrintTotal();
	return a;
}
int main()
{
	Apple * p = new Apple[4];
	Fun(p[2]);   // 4
	Apple p1,p2;
	Apple::PrintTotal ();   // 5
	delete [] p;
	p1.PrintTotal ();  // 1
	return 0;
}