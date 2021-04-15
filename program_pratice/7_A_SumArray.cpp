//填写模板 PrintArray,使得程序输出结果是： TomJackMaryJohn 10 不得编写SumArray函数

#include <iostream>
#include <string>
using namespace std;
template <class T>
T SumArray(T * t1, T * t2){
	T result;
	while(t1 != t2){
		result += *t1;
		t1 += 1;
	}
	return result;
}

int main() {
	string array[4] = { "Tom","Jack","Mary","John"};
	cout << SumArray(array,array+4) << endl;
	int a[4] = { 1, 2, 3, 4};  //提示：1+2+3+4 = 10
	cout << SumArray(a,a+4) << endl;
	return 0;
}