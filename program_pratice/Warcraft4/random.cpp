#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
using namespace std;
int main()
{
    freopen("in.txt","w",stdout);
    srand((unsigned)time(NULL));
    cout << 100000 << endl;
    for(int i = 0; i < 100000; i++)
    {
        cout << ((rand() % 10000)+1) << " "; 
        cout << ((rand() % 20)+1) << " "; 
        for (int i = 0; i < 2; i++)
            cout << ((rand() % 10000)+1) << " "; 
        cout << ((rand() % 5000)+1) << " "; 
        cout << endl;
        for (int i = 0; i < 5; i++)
            cout << ((rand() % 10000)+1) << " "; 
        cout << endl;
        for (int i = 0; i < 5; i++)
            cout << ((rand() % 10000)+1) << " "; 
        cout << endl;
    }

}