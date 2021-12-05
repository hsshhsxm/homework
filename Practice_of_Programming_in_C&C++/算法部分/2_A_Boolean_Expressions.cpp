#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string str;
int pos = 0;

char expr();
char term();
char factor();

void removeSpace(){
    int index = 0;
     if( !str.empty())
         while( (index = str.find(' ',index)) != string::npos)
             str.erase(index,1);
}

char factor(){
    char v;
    char c = str[pos];
    if(c == '('){
        pos++;
        v = expr();
        pos++;
    }
    else if(c == '!')
        v = term();
    else 
        v = str[pos++];
    return v;
}

char term(){
    char c = str[pos];
    char v;
    if(c == '!'){
        pos++;
        char a = factor();
        if(a == 'V')
            v = 'F';
        else 
            v = 'V';
    }
    else 
        v = factor();
    return v;
}

char expr(){
    char v = term();
    while(true){
        char c = str[pos];
        if(c == '|'){
            pos++;
            char a = term();
            if(v == 'F' && a == 'F')
                v = 'F';
            else 
                v = 'V';
        }
        else if(c == '&'){
            pos++;
            char a = term();
            if(v == 'V' && a == 'V')
                v = 'V';
            else 
                v = 'F';
        }
        else 
            break;
    }
    return v;
}


int main()
{
    int i = 1;
    char a;
    while(getline(cin,str)){
        removeSpace();
        char r = expr();
        if(r == 'F' || r == 'V')
            cout << "Expression " << i++ << ": " << r << endl;
        else 
            break;
        pos = 0;
    }
    return 0;
}