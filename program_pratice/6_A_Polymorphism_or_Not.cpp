/*
D::Fun
B::Fun
D::Fun
nBVal=2
nBVal=24
nDVal=8
B::Fun
nBVal=12
*/

#include <iostream>
using namespace std;
class B { 
	private: 
		int nBVal; 
	public: 
		void Print() 
		{ cout << "nBVal="<< nBVal << endl; } 
		void Fun() 
		{cout << "B::Fun" << endl; } 
		B ( int n ) { nBVal = n;} 
};

class D:public B{
private:
	int nDVal;
public:
	D(int n):B(3*n),nDVal(n){};
	void Fun() {
		cout << "D::Fun" << endl;
	}
	void Print(){
		B::Print();
		cout << "nDVal="<< nDVal << endl;
	}
};


int main() { 
	B * pb; D * pd; 
	D d(4); 
	//cout << "d.Fun()" << endl;
	d.Fun(); 
	pb = new B(2); pd = new D(8); 
	//cout << "pb -> Fun()" << endl;
	pb -> Fun(); 
	//cout << "pd -> Fun()" << endl;
	pd->Fun(); 
	//cout << "pb->Print ()" << endl;
	pb->Print (); 
	//cout << "pd->Print ()" << endl;
	pd->Print (); 
	pb = & d; 
	//cout << "pb->Fun()" << endl;
	pb->Fun(); 
	//cout << "pb->Print()" << endl;
	pb->Print(); 
	return 0;
}