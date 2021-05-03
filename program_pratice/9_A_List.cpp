#include <iostream>
#include <string>
#include <list>
#include <map>
using namespace std;

int main(){
    map<int, list<int> > myMap;
    int n;
    string judge;
    cin >> n;
    while(n){
        cin >> judge;
        if(judge == "new"){
            int id;
            cin >> id;
            myMap.insert(pair<int, list<int> > (id, list<int>()));
        } else if(judge == "add"){
            int id,num;
            cin >> id >> num;
            myMap[id].push_back(num);
            myMap[id].sort();
        } else if(judge == "merge"){
            int id1,id2;
            cin >> id1 >> id2;
            myMap[id1].merge(myMap[id2]);
            myMap[id2].clear();
        } else if(judge == "unique"){
            int id;
            cin >> id;
            myMap[id].unique();
        } else if(judge == "out"){
            int id;
            cin >> id;
            myMap[id].sort();
            if(myMap.size() > 0){
                list<int>::iterator it;
                for(it = myMap[id].begin(); it != myMap[id].end(); ++it)
                    cout << *it << " ";
                cout << endl;
            }
        } else{}
        --n;
    }
    return 0;
}