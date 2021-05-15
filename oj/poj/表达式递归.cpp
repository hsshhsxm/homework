#include <iostream>
#include <string>
using namespace std;

int expr();

int factor(){
    int v;
    char c = cin.peek();
    if(c == '('){
        cin.get();
        v = expr();
        cin.get();
    }
    else 
        cin >> v;
    return v;
}

int term(){
    int v = factor();
    while(true){
        char c = cin.peek();
        if(c == '*'){
            cin.get();
            v *= factor();
        }
        else if(c == '/'){
            cin.get();
            v /= factor();
        }
        else 
            break;
    }
    return v;
}

int expr(){
    int v = term();
    while(true){
        char c = cin.peek();
        if(c == '+'){
            cin.get();
            v += term();
        }
        else if(c == '-'){
            cin.get();
            v -= term();
        }
        else 
            break;
    }
    return v;
}

int main(){
    cout << expr() << endl;
}