#include <iostream>
#include <map>
using namespace std;

int main(){
    map<int,int> myMap;
    myMap[1000000000] = 1;
    int n;
    cin >> n;
    while(n){
        --n;
        int id, fi;
        cin >> id >> fi;
		map<int,int>::iterator it = myMap.lower_bound(fi);
		if(it == myMap.end())
			--it;
		int min = abs(fi - it->first);
		int minid = it->second;
		if(it != myMap.begin()){
			--it;
			if(abs(fi - it->first) < min || (abs(fi - it->first) == min && it->second < minid)){
				minid = it->second;
			}
		}
		cout << id << " " << minid << endl;
		it = myMap.find(fi);
		if(it == myMap.end() || it -> second > id)
			myMap[fi] = id;
    }
    return 0;
}
