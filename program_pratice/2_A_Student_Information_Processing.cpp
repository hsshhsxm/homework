/*
Please wirte a program to calculate the average score during four years for a student.
You are required to implement a class to represent student, and all member variables in this class are private.
Please complete Class Student in the following program to achieve the above goal.
*/

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
    private:
    string name;
    int age;
    string ID;
    int score[4];
    float average_score;
    
    public:
    void input(){
        string input_str;
        getline(cin, input_str);
        stringstream ss(input_str);
        string buf;
        getline(ss, buf, ',');
        name = buf;
        getline(ss, buf, ',');
        age = stoi(buf);
        getline(ss, buf, ',');
        ID = buf;
        for(int i = 0; i < 4; i++){
            getline(ss, buf, ',');
            score[i] = stoi(buf);
        }
    }

    void calculate(){
        int sum = 0;
        for(int i = 0; i < 4; i++){
            sum += score[i];
        }
        average_score = float(sum) / 4;
    }
    
    void output(){
        cout << name <<  "," << age << "," << ID << "," << average_score;
    }
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
}