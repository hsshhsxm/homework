#include <iostream>
#include <cmath>
using namespace std;

//bailian
//ac
double expr(){
    char s[10];
    cin >> s;
    switch (s[0])
    {
    case '+':
        return expr() + expr();
    case '-':
        return expr() - expr();
    case '*':
        return expr() * expr();
    case '/':
        return expr() / expr();
    default:
        return atof(s);
    }
}

int main(){
    cout << expr() << endl;

}