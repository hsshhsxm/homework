#include <iostream>
#include <map>
#include <set>
using namespace std;

int main(){
    map<int,int> myMap;
    myMap[1] = 1000000000;
    int n;
    cin >> n;
    while(n){
        --n;
        int id, fi;
        cin >> id >> fi;
        int min = abs(fi - myMap[1]);
        int minID = 1;
        set<int> results;
        results.insert(1);
        map<int,int>::iterator it = myMap.begin();
        for(it = myMap.begin(); it != myMap.end(); ++it){
            if(abs(fi - it->second) < min){
                min = abs(fi - it->second);
                if(results.size() == 1)
                    results.erase(results.begin());
            }
        }
        for(it = myMap.begin(); it != myMap.end(); ++it){
            if(abs(fi - it->second) == min)
                results.insert(it->first);
        }
        set<int>::iterator si = results.begin();
        cout << id << " " << *si << endl;
        myMap[id] = fi;
    }

    return 0;
}
