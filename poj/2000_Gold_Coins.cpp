#include <iostream>
#include <string>
using namespace std;

int soultion(int day, int pay){
    if(day <= pay)
        return day * pay;
    return (pay * pay) + soultion(day - pay, pay + 1);
}

int main(){
    int i;
    cin >> i;
    while(i != 0){
        cout << i << " " << soultion(i,1) << endl;
        cin >> i;
    }   
}