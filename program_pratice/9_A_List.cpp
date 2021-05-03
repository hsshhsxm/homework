#include <iostream>
#include <string>
#include <list>
using namespace std;

int main(){
    list<int> myList[10000];
    int n;
    cin >> n;
    while(n){
        string judge;
        cin >> judge;
        if(judge == "new"){
            int id;
            cin >> id;
        } else if(judge == "add"){
            int id,num;
            cin >> id >> num;
            myList[id].push_back(num);
            myList[id].sort();
        } else if(judge == "merge"){
            int id1,id2;
            cin >> id1 >> id2;
            myList[id1].merge(myList[id2]);
        } else if(judge == "unique"){
            int id;
            cin >> id;
            //unique之前要sort
            myList[id].sort();
            myList[id].unique();
        } else if(judge == "out"){
            int id;
            cin >> id;
            myList[id].sort();
            list<int>::iterator it;
            for(it = myList[id].begin(); it != myList[id].end(); ++it)
                cout << *it << " ";
            cout << endl;
        } else{}
        --n;
    }
    return 0;
}