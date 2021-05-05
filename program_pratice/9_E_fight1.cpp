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
			map<int,int>::iterator tmp = it;
			--it;
			if(abs(fi - it->first) < min){
				minid = it->second;
			}
			if(abs(fi - it->first) == min){
				if(tmp->first > it->first)
					minid = it->second;
			}
		}
		cout << id << " " << minid << endl;
		myMap[fi] = id;
    }
    return 0;
}
