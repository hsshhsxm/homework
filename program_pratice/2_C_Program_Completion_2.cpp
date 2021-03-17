/*
The output of the following program is：
3+4i
5+6i
Please complete the member function of class Complex according to the above output.
Note that you are not allowed to add new member variables.
*/
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r,i;
public:
    Complex(){}
    Complex(const char * s){
        string str = string(s);
        int pos = str.find("+");
        string tmp = str.substr(0,1);
        const char * r_str = tmp.c_str();
        r = atof(r_str);
        tmp = str.substr(2,3);
        const char * i_str = tmp.c_str();
        i = atof(i_str);
        
    }
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}