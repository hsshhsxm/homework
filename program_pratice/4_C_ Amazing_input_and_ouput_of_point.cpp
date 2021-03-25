/*
样例输入
2 3
4 5
样例输出
2,3
4,5
*/

#include <iostream> 
using namespace std;
class Point { 
	private: 
		int x; 
		int y; 
	public: 
		Point() { };

	friend istream & operator>>(istream & input, Point & p){
		input >> p.x;
		input >> p.y;
		return input;
	}

	friend ostream & operator<<(ostream & output, Point &p){
		output << p.x << "," << p.y;
		return output;
	}
}; 
int main() 
{ 
 	Point p;
 	while(cin >> p) {
 		cout << p << endl;
	 }
	return 0;
}