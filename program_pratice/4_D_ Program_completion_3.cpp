/*
Please design a class Array2 to implement a two-dimension array to make the output of the following program as follow:
0,1,2,3,
4,5,6,7,
8,9,10,11,
next
0,1,2,3,
4,5,6,7,
8,9,10,11,
*/

#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
public:
    int *p;
    int x,y;

    Array2(){
        x = 0;
        y = 0;
        p = NULL;
    }

    Array2(int m, int n){
        x = m;
        y = n;
        p = new int[x*y];
    }

    Array2(Array2 & b){
        x = b.x;
        y = b.y;
        if(b.p){
            p = new int[x*y];
            memcpy(p, b.p, sizeof(int)*x*y);
        }
        else
            p = NULL;
    }

    ~Array2(){
        if(p)
            delete [] p;
    }

    int * operator[](int i){
        return p + y*i;
    }

    int & operator()(int i, int j){
        return p[y*i + j];
    }

    Array2 & operator=(const Array2 & b){
        x = b.x;
        y = b.y;
        if(b.p){
            p = new int[x*y];
            memcpy(p, b.p, sizeof(int)*x*y);
            return *this;
        }
        else{
            p = NULL;
            return *this;
        }
    }
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i ){
        for(  j = 0; j < 4; j ++ ){
            a[i][j] = i * 4 + j;
            //cout << a[i][j] << endl;
        }
    }
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}
