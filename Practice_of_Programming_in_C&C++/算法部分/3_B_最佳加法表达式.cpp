#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct myInt{
    int num[100];
    int len;
    myInt(){
        len = 1;
        memset(num, 0, sizeof(num));
    }
    myInt(const char * str, int l){
        memset(num, 0, sizeof(num));
        len = l;
        for(int i = 0; str[i] ; ++i)
            num[len - i - 1] = str[i] - '0';
    }
    myInt operator+(const myInt & a){
        int tmpLen = max(len, a.len);
        int carry = 0;
        myInt res;
        for(int i = 0; i < tmpLen; ++i){
            res.num[i] = num[i] + a.num[i] + carry;
            if(res.num[i] >= 10){
                carry = 1;
                res.num[i] -= 10;
            } 
            else 
                carry = 0;
        }
        if(carry == 1){
            res.len = tmpLen + 1;
            res.num[tmpLen] = 1;
        }
        else 
            res.len = tmpLen;
        return res;
    }
    bool operator<(const myInt & a){
        if(len < a.len)
            return true;
        if(len > a.len)
            return false;
        for(int i = len - 1; i >= 0; --i){
            if(num[i] > a.num[i])
                return false;
            if(num[i] < a.num[i])
                return true;
        }
        return false;
    }
    friend ostream &operator<<(ostream & o, myInt & a){
        for(int i = a.len - 1; i >= 0; --i)
            o << a.num[i];
        return o;
    }
};

char inputStr[55];
myInt num[55][55];
myInt addRes[55][55];
myInt bigNum;

int main()
{
    bigNum.len = 100 - 1;
    bigNum.num[100 - 2] = 1;
    int m,n;
    while(cin >> m){
        cin >> inputStr;
        n = strlen(inputStr);
        for(int i = 1; i <= n; ++i)
            for(int j = i; j <= n; ++j)
                num[i][j] = myInt(inputStr + i - 1, j - i + 1);
        for(int i = 1; i <= n; ++i)
            addRes[0][i] = myInt(inputStr, i);
        for(int i = 1; i <= m; ++i){
            for(int j = i; j <= n; ++j){
                if(j - 1 < i)
                    addRes[i][j] = bigNum;
                else{
                    myInt tmpMin = bigNum;
                    for(int k = i; k < j; ++k){
                        myInt tmp = addRes[i - 1][k] + num[k + 1][j];
                        if(tmp < tmpMin)
                            tmpMin = tmp;
                    }
                    addRes[i][j] = tmpMin;
                }
            }
        }
        cout << addRes[m][n] << endl;
    }
    return 0;
}

