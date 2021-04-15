/*
输入
多组数据，每组一行，是两个整数
输出
对每组数据，原样输出 
当碰到输入中出现-1 时，程序结束 
输入中保证会有 -1
*/

#include <iostream>
using namespace std;
class MyCin
{
public:
    bool s;
    MyCin():s(true){}
    MyCin & operator>>(int & n){
        if(!s)
            return *this;
        cin >> n;
        if(n == -1)
            s = false;
        return *this;
    }
    operator bool(){
        return s;
    }
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}
