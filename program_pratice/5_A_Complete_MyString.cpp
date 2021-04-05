/*
输入
None
输出
1. abcd-efgh-abcd-
2. abcd-
3. 
4. abcd-efgh-
5. efgh-
6. c
7. abcd-
8. ijAl-
9. ijAl-mnop
10. qrst-abcd-
11. abcd-qrst-abcd- uvw xyz
about
big
me
take
abcd
qrst-abcd-
*/

#include <cstdlib>
#include <iostream>
using namespace std;
int strcmp(const char * s1,const char * s2)
{
	for(int i = 0; s1[i] && s2[i] ; ++i) {
		if( s1[i] < s2[i] )
			return -1;
		else if( s1[i] > s2[i])
			return 1;
	}
	return 0;
}

class MyString
{
public:
	char * str;
	MyString(const char * s = NULL){
		if(s){
			str = new char[strlen(s) + 1];
			strcpy(str,s);
		} 
		else{
			str = new char[1];
			str[0] = '\0';
		}
			
	}
	MyString(const MyString & s){
		if(str) 
			delete[] str;
		if(s.str){
			str = new char[strlen(s.str) + 1];
			strcpy(str,s.str);
		}
		else{
			str = new char[1];
			str[0] = '\0';
		}
	}
	~MyString(){
		if(str)
			delete [] str;
	}
	friend ostream & operator<<(ostream & output, const MyString & s){
		if(s.str)
			output << s.str;
		return output;
	}
	MyString operator+(const MyString & s){
		char * tmp;
		if(str){
			tmp = new char[strlen(str) + strlen(s.str) + 1];
			strcpy(tmp,str);
		}
		else
			tmp = new char[strlen(s.str) + 1];
		strcat(tmp,s.str);
		MyString tmp_str = tmp;
		delete[] tmp;
		return tmp_str;
	}
	//重要，没有这个重载就会runtime error
	MyString operator+(const char * s){
		char * tmp;
		if(str){
			tmp = new char[strlen(str) + strlen(s) + 1];
			strcpy(tmp,str);
		}
		else
			tmp = new char[strlen(s) + 1];
		strcat(tmp,s);
		MyString tmp_str = tmp;
		delete[] tmp;
		return tmp_str;
	}
	
	MyString & operator+=(const char * s){
		char * tmp = new char[strlen(str) + 1];
		strcpy(tmp,str);
		delete[] str;
		str = new char[strlen(tmp) + strlen(s) + 1];
		strcpy(str,tmp);
		strcat(str,s);
		return *this;
	}
	friend MyString operator+(const char * s1, const MyString & s2){
		char * s;
		s = new char[strlen(s1) + strlen(s2.str) + 1];
		strcpy(s,s1);
		strcat(s,s2.str);
		MyString tmp = s;
		delete[] s;
		return tmp;
	}
	char & operator[](int i){
		return str[i];
	}
	char * operator()(int i, int j){
		char * tmp;
		tmp = new char[j + 1];
		int k = 0;
		for(k = 0; k < j; ++k){
			tmp[k] = str[k + i];
		}
		tmp[k] = 0;
		return tmp;
	}
	MyString & operator=(const MyString & s){
		if(str) 
			delete[] str;
		if(s.str){
			str = new char[strlen(s.str) + 1];
			strcpy(str,s.str);
		}
		else{
			str = new char[1];
			str[0] = '\0';
		}
		return *this;
	}
	int operator>(const MyString & s){
		if(strcmp(str, s.str) == 1)
			return 1;
		else
			return 0;
	}
	int operator<(const MyString & s){
		if(strcmp(str, s.str) == -1)
			return 1;
		else
			return 0;
	}
	int operator==(const MyString & s){
		if(strcmp(str, s.str) == 0)
			return 1;
		else
			return 0;
	}
};

int CompareString( const void * e1, const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( * s1 < *s2 )
	return -1;
	else if( *s1 == *s2)
	return 0;
	else if( *s1 > *s2 )
	return 1;
}

int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}