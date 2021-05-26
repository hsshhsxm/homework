#include <iostream>
using namespace std;

char expr();
char term();
char factor();

char factor(){
    char v;
    while(cin.peek() == ' ')
        cin.get();
    char c = cin.peek();
    if(c == '('){
        cin.get();
        v = expr();
        while(cin.peek() == ' ')
            cin.get();
        cin.get();
    }
    else if(c == '!'){
        cin.get();
        c = cin.peek();
        if(c == '('){
            cin.get();
            v = expr();
            while(cin.peek() == ' ')
                cin.get();
            cin.get();
        }
        else{
            v = cin.get();
        }
        (v == 'V') ? v = 'F' : v = 'V';
    }
    else 
        v = cin.get();
    return v;
}

char term(){
    int v = factor();
    while(true){
        while(cin.peek() == ' ')
            cin.get();
        char c = cin.peek();
        if(c == '&'){
            cin.get();
            char a = factor();
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

char expr(){
    char v = term();
    while(true){
        while(cin.peek() == ' ')
            cin.get();
        char c = cin.peek();
        if(c == '|'){
            cin.get();
            char a = term();
            if(v == 'F' && a == 'F')
                v = 'F';
            else 
                v = 'V';
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
    while(cin.peek() != EOF){
        char r = expr();
        if(r == 'F' || r == 'V')
            cout << "Expression " << i++ << ": " << r << endl;
        else 
            continue;
    }
    return 0;
}