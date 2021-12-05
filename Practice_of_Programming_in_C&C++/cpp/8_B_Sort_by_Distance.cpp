#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;
template <class T1,class T2>
struct Closer {
    T1 judge;
    T2 fp;
    Closer(T1 t1, T2 dis ) {
        judge = t1;
        fp = dis;
    }
    bool operator()(T1 & i, T1 & j){
        if(fp(judge,i) < fp(judge,j))
            return true;
        else if(fp(judge,i) == fp(judge,j))
            return i < j;
        else 
            return false;
    }
};

int Distance1(int n1,int n2) {
	return abs(n1-n2);
}
int Distance2(const string & s1, const string & s2)
{
	return abs((int)s1.length()- (int) s2.length());
}
int a[10] = { 0,3,1,4,7,9,20,8,10,15};
string b[6] = {"American","Jack","To","Peking","abcdefghijklmnop","123456789"};
int main()
{
	int n;string s;
	while( cin >> n >> s ) {
		sort(a,a+10,Closer<int ,int (*)(int ,int)> (n,Distance1));
		for(int i = 0;i < 10; ++i)
			cout << a[i] << "," ;
		cout << endl;
		sort(b,b+6,Closer<string,int (*)(const string &,const string &  )> (s,Distance2)); 
		for(int i = 0;i < 6; ++i)
			cout << b[i] << "," ;
		cout << endl;
	}
	return 0;
}
