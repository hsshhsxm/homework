/*
输入
多组数据，每组数据是两个非负整数s和 n。s最多可能200位， n用int能表示
输出
对每组数据，输出6行，内容分别是：
样例输入
99999999999999999999999999888888888888888812345678901234567789 12
6 6
样例输出
99999999999999999999999999888888888888888812345678901234567801
99999999999999999999999999888888888888888812345678901234567801
99999999999999999999999999888888888888888812345678901234567801
25
25
26
12
12
12
13
13
14
*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int MAX = 110;
class CHugeInt
{
public:
	string s;
	CHugeInt(char *s) : s(s) {}
	CHugeInt(int n){
		s = to_string(n);
	}
	CHugeInt(string s) : s(s) {}
	
char *strrev(char *str)
{
    if (!str || ! *str)
        return str;

    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}

	CHugeInt operator+(const CHugeInt &c){
		int length;
		string result = "";
		//cout << "s,c.s="<< s << "," << c.s << endl;
		if(s.length() > c.s.length()){
			//result = s;
			length = s.length();
		}
		else{
			//result = c.s;
			length = c.s.length();
		}
		int * carry;
		carry = new int[length + 1]();
		//cout << "length="<< s << endl;
		char rev_s[s.length() + 1];
		char rev_cs[c.s.length() + 1];
		strcpy(rev_s, s.c_str());
		strcpy(rev_cs, c.s.c_str());
		strrev(rev_s);
		strrev(rev_cs);
		//cout << "rev_s,rev_cs="<< rev_s << "," << rev_cs << endl;
		for(int i = 0; i < length; i++){
			//cout << "i="<< i << endl;
			int tmp_a,tmp_b;
			//cout << "rev_s[i],rev_cs[i]="<< rev_s[i] << "," << rev_cs[i] << endl;
			if(i > s.length() -1 )
				tmp_a = 0;
			else
				tmp_a = rev_s[i] - 48;
			if(i > c.s.length() - 1)
				tmp_b = 0;
			else
				tmp_b = rev_cs[i] - 48;
			//cout << "tmp_a,tmp_b="<< tmp_a << "," << tmp_b << endl;
			int tmp_added = tmp_a + tmp_b + carry[i];
			//cout << "tmp_added="<< tmp_added << endl;
			string tmp_string = to_string(tmp_added);
			char added[tmp_string.length() + 1];
			strcpy(added, tmp_string.c_str());
			if(tmp_string.length() == 1){
				result =  added[0] + result;
			}
			else{
				result = added[1] + result;
				carry[i+1] = added[0] - 48;
				//cout << "carry i+1=" <<carry[i + 1] << endl;
			}
			//cout << "tmp_result=" << result << endl <<endl;
		}
		//cout << "carry 1:" <<carry[1] << endl;
		//cout << result << endl;
		//cout << "carry max:" <<carry[length + 1] << endl;
		if(carry[length]){
			result = to_string(carry[length]) + result;
		}
		//cout << result << endl;
		CHugeInt tmp_int(result);
		delete [] carry;
		return tmp_int;
	}
	CHugeInt operator+(int n){
		CHugeInt tmpInt_c(n);
		return *this + tmpInt_c;
	}
	friend ostream & operator<<(ostream & output, const CHugeInt & c){
		output << c.s;
		return output;
	}
	void operator+=(int n){
		CHugeInt tmpInt_c(n);
		*this = *this + tmpInt_c;
	}
	CHugeInt & operator++(){
		CHugeInt tmpInt_c(1);
		//cout << this->s << endl;
		*this = *this + 1;
		//cout << this->s << endl;
		return *this;
	}
	CHugeInt operator++(int){
		CHugeInt tmp_return(this->s);
		CHugeInt tmpInt_c(1);
		*this = *this + tmpInt_c;
		return tmp_return;
	}
	friend CHugeInt operator+(int n, const CHugeInt & c){
		CHugeInt tmpInt_c(n);
		return tmpInt_c + c;
	}
};



int main()
{
	//freopen("result.txt","w",stdout);
	char s[210];
	int n;

	while (cin >> s >> n)
	{
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout << ++b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}