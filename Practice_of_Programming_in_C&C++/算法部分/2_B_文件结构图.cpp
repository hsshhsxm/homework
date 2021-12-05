#include <iostream>
#include <set>
#include <string>
using namespace std;

int draw(int level, string dirname, int num){
    for(int i = 0; i < level; ++i)
        cout << "|     ";
    set<string> fileSet;
    if(level != 0)
        cout << dirname << endl;
    int first = 0;
    while(true){
        string s;
        cin >> s;
        if(s[0] == '#')
            return 0;
        if(level == 0 && first == 0){//root第一次循环
            cout << "DATA SET " << num << ":" << endl << dirname << endl;
            first = 1;
        }   
        if(s[0] == '*')
            break;
        if(s[0] == ']')
            break;
        if(s[0] == 'f')
            fileSet.insert(s);
        if(s[0] == 'd')
            draw(level + 1, s, num);
    }
    set<string>::iterator it = fileSet.begin();
    for( ; it != fileSet.end(); ++it){
        for(int i = 0; i < level; ++i)
            cout << "|     ";
        cout << *it << endl;
    }
    return 1;
}

int main()
{
    //freopen("in.txt", "r", stdin);
    int num = 1;
    while(draw(0, "ROOT", num) != 0){
        ++num;
        cout << endl;
    }
    return 0;
}

