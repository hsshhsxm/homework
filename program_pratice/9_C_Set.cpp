#include <iostream>
#include <set>
using namespace std;

int main(){
    int n;
    cin >> n;
    multiset<int> mySet;
    int judge[10000] = {0};
    while(n){
        --n;
        string s;
        int x,out;
        cin >> s;
        if(s == "add"){
            cin >> x;
            mySet.insert(x);
            judge[x] = 1;
            out = mySet.count(x);
            cout << out << endl;
        }
        if(s == "del"){
            cin >> x;
            out = mySet.count(x);
            cout << out << endl;
            multiset<int>::iterator itl = mySet.lower_bound(x);
            multiset<int>::iterator itu = mySet.upper_bound(x);
            mySet.erase(itl, itu);
        }
        if(s == "ask"){
            cin >> x;
            out = mySet.count(x);
            cout <<  judge[x] << " " << out << endl;
        }
    }
    return 0;
}