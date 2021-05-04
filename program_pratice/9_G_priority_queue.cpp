#include <iostream>
#include <set>
using namespace std;

bool judgePrime(int a){
    for(int i = 2; i < a; ++i){
        if(a % i == 0)
            return false;
    }
    return true;
}

struct findMax{
    bool operator()(int a, int b){
        int sumA = 0, sumB = 0;
        for(int i = 2; i < a; ++i){
            if(a % i == 0)
                if(judgePrime(i))
                    ++sumA;
        }
        for(int i = 2; i < b; ++i){
            if(b % i == 0)
                if(judgePrime(i))
                    ++sumB;
        }
        if(sumA != sumB)
            return sumA < sumB;
        else 
            return a < b;
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
        int max = *(mySet.begin());
        int min = *(mySet.rbegin());
        cout << max << " " << min << endl;
        mySet.erase(max);
        mySet.erase(min);
    }
    return 0;
}
