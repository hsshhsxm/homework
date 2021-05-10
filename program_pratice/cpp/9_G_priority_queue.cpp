#include <iostream>
#include <set>
#include <cmath>
using namespace std;

bool judgePrime(int a){
    for(int i = 2; i <= sqrt((float)(a)); ++i){
        if(a % i == 0)
            return false;
    }
    return true;
}

struct findMax{
    bool operator()(int a, int b){
        int sumA = 0, sumB = 0;
        for(int i = 2; i <= sqrt((float)a); ++i){
            if(a % i == 0){
                int k = a / i;
                if(i != k && judgePrime(k))
                    ++sumA;
                if(judgePrime(i))
                    ++sumA;
            }
        }
        for(int i = 2; i < sqrt((float)b); ++i){
            if(b % i == 0){
                int k = b / i;
                if(i != k && judgePrime(k))
                    ++sumB;
                if(judgePrime(i))
                    ++sumB;
            }
        }
        if(sumA != sumB)
            return sumA > sumB;
        else  
            return a > b;
    }
};

int main(){
    int n;
    cin >> n;
    set<int, findMax> mySet;
    while(n){
        --n;
        int a;
        for(int i = 0; i < 10; ++i){
            cin >> a;
            mySet.insert(a);
        }
        int maxNum = *(mySet.begin());
        int minNum = *(mySet.rbegin());
        mySet.erase(maxNum);
        mySet.erase(minNum);
        cout << maxNum << " " << minNum << endl;
    }
    return 0;
}