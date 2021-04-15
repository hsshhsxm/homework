/*
输入
多组数据

每组数据第一行是两个整数 m 和 n ,都不超过 50

第二行是m个不带空格的字符串
第三行是 n个整数
输出
对每组数据
第一行输出所有输入字符串连在一起的结果
第二行输出输入中的每个整数加1的结果
*/

#include <iostream>
#include <string>
using namespace std;
template<class T1, class T2>
void MyForeach(T1 * t1, T1 * t2, void fp(T2 t)){
    while(t1 != t2){
        fp(*t1);
        t1++;                       
    }
}

void Print(string s)
{
	cout << s;
}
void Inc(int & n)
{
	++ n;
}
string array[100];
int a[100];
int main() {
	int m,n;
	while(cin >> m >> n) {
		for(int i = 0;i < m; ++i)
			cin >> array[i];
		for(int j = 0; j < n; ++j)
			cin >> a[j];
		MyForeach(array,array+m,Print);		 
		cout << endl;
		MyForeach(a,a+n,Inc);		 
		for(int i = 0;i < n; ++i)
			cout << a[i] << ",";
		cout << endl;
	}
	return 0;
}
