/* 
写出函数中缺失的部分，使得函数返回值为一个整数,该整数的第i位是n的第i位取反，其余位和n相同
请使用【一行代码】补全bitManipulation2函数使得程序能达到上述的功能
Please invert the i-th bit of integer n, with other bits unchanged.
You are only allowed to use just one statement to complete function bitManipulation 
to achieve the above goal.
*/

#include <iostream>
using namespace std;

int bitManipulation2(int n, int i) {
// 在此处补充你的代码
}

int main() {
	int t, n, i;
	cin >> t;
	while (t--) {
		cin >> n >> i;
		cout << bitManipulation2(n, i) << endl;
	}
	return 0;
}