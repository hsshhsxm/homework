/*
输入
第一行是整数t，表示有t组数据
每组数据一行，三个整数加两个字符串。字符串是不含空格的
输出
对每组数据，输出二行 
在第一行输出第一个数
第二行原样输出输入的内容
*/

#include <iostream>
#include <string>

using namespace std;
template <class T>
class CMyistream_iterator
{
public:
    T  t;
    istream & input;
    bool s;
    CMyistream_iterator(istream & i):input(i){s = false;}
    T & operator*(){
        if(s)
            return t;
        input >> t;
        s = true;
        return t;
    }
    T & operator++(int){
        input >> t;
        return t;
    }
};



int main()  
{ 
	int t;
	cin >> t;
	while( t -- ) {
		 CMyistream_iterator<int> inputInt(cin);
		 int n1,n2,n3;
		 n1 = * inputInt; //读入 n1
		 int tmp = * inputInt;
		 cout << tmp << endl;
		 inputInt ++;   
		 n2 = * inputInt; //读入 n2
		 inputInt ++;
		 n3 = * inputInt; //读入 n3
		 cout << n1 << " " << n2<< " " << n3 << " ";
		 CMyistream_iterator<string> inputStr(cin);
		 string s1,s2;
		 s1 = * inputStr;
		 inputStr ++;
		 s2 = * inputStr;
		 cout << s1 << " " << s2 << endl;
	}
	 return 0;  
}
