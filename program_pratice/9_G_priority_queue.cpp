#include <iostream>
#include <queue>
#include <vector>
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
    vector<int> vectorA;
    vector<int> vectorB;
    for(int i = 2; i < a; ++i){
        if(a % i == 0)
            if(judgePrime(i))
                vectorA.push_back(i);
    }
    for(int i = 2; i < b; ++i){
        if(b % i == 0)
            if(judgePrime(i))
                vectorB.push_back(i);
    }
    if(vectorA.size() != vectorB.size())
        return (vectorA.size() < vectorB.size());
    else 
        return a < b;
}
};

struct findMin{
bool operator()(int a, int b){
    vector<int> vectorA;
    vector<int> vectorB;
    for(int i = 2; i < a; ++i){
        if(a % i == 0)
            if(judgePrime(i))
                vectorA.push_back(i);
    }
    for(int i = 2; i < b; ++i){
        if(b % i == 0)
            if(judgePrime(i))
                vectorB.push_back(i);
    }
    if(vectorA.size() != vectorB.size())
        return (vectorA.size() > vectorB.size());
    else 
        return a > b;
}
};


int main(){
    int n;
    cin >> n;
    while(n){
        --n;
        priority_queue<int, vector<int>, findMax> maxQueue;
        priority_queue<int, vector<int>, findMin> minQueue;
        int a[10];
        for(int i = 0; i < 10; ++i){
            cin >> a[i];
            maxQueue.push(a[i]);
            minQueue.push(a[i]);
        }
        cout << maxQueue.top() << " " << minQueue.top() << endl;
    }
    return 0;
}
