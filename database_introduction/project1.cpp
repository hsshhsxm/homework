#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//定义数据结构Student和Score
struct Student
{
    string ID;
    string name;
    string birthday;
    string collage;
    string department;

};
struct Score
{
    string ID;
    string coursename;
    int score;
};

//用vector存储student和score
vector<Student> student_list;
vector<Score> score_list;

//添加学生信息
int addStudentInfo(string ID = "", string name = "", string birthday = "", string collage = "", string department = "")
{
    if (ID == "" || name == "")
        return -1;
    Student temp_student_info;
    temp_student_info.ID = ID;
    temp_student_info.name = name;
    temp_student_info.birthday = birthday;
    temp_student_info.collage = collage;
    temp_student_info.department = department;
    student_list.push_back(temp_student_info);
    return 0;
}

//搜索学生信息
int searchStudentInfo(string ID = "", string name = "")
{
    if (ID != "")
    {
        for(int i = 0; i < student_list.size(); i++)
        {
            if (student_list[i].ID == ID)
                return i;
        }
    }
    else if (name != "")
    {
        for(int i = 0; i < student_list.size(); i++)
        {
            if (student_list[i].name == name)
                return i;
        }

    }
    return -1;
}

//删除学生信息
int deleteStudentInfo(string ID)
{
    int i = searchStudentInfo(ID,"");
    student_list.erase(student_list.begin() + i);
    return 0;
}

//修改学生信息
int modifyStudentInfo(string ID, string name, string birthday, string collage, string department)
{
    int i = searchStudentInfo(ID, name);
    student_list[i].name = name;
    student_list[i].birthday = birthday;
    student_list[i].collage = collage;
    student_list[i].department = department;
    return 0;
}

//添加学生成绩
int addStudentScore(string ID, string coursename, int score)
{
    Score temp_score;
    temp_score.ID = ID;
    temp_score.coursename = coursename;
    temp_score.score = score;
    score_list.push_back(temp_score);
    return 0;
}

//查找学生所修的课程
vector<string> searchStudentCourse(string ID)
{
    vector<string> course_list;
    for(int i = 0; i < score_list.size(); i++)
    {
        if (score_list[i].ID == ID)
            course_list.push_back(score_list[i].coursename);
    }
    return course_list;
}

//查找学生某一刻课程成绩所在的位置
int searchStudentScoreID(string ID, string coursename)
{
    for (int i = 0; i< score_list.size(); i++)
    {
        if(score_list[i].ID == ID && score_list[i].coursename == coursename)
            return i;
    }
    return -1;
}

//查找学生的所有成绩
void searchStudentAllScore(string ID, map<string, int> &one_course_score_map)
{
    vector<string> course_list;
    course_list = searchStudentCourse(ID);
    for(int i = 0; i < course_list.size(); i++)
    {
        int j = searchStudentScoreID(ID,course_list[i]);
        one_course_score_map[course_list[i]]=score_list[j].score;
    }
}

//删除学生一个课程的成绩
int deleteStudentOneScore(string ID, string coursename)
{
	int i = searchStudentScoreID(ID, coursename);
    score_list.erase(score_list.begin() + i);
    return 0;
}

//删除学生的所有成绩
int deleteStudentAllScore(string ID)
{
    vector<string> course_list;
    course_list = searchStudentCourse(ID);
    for(int i = 0; i < course_list.size(); i++)
        deleteStudentOneScore(ID,course_list[i]);
    return 0;
}

//修该学生某一课程的成绩
int modifyStudentScore(string ID, string coursename, int score)
{
	int i = searchStudentScoreID(ID, coursename);
    score_list[i].score = score;
    return 0;
}

//从文件读取数据
int readFromFile()
{
    ifstream file_stu_in;
    ifstream file_score_in;
    file_stu_in.open("p1_student.txt");
    string line;
    char * temp_string_for_split;
    while(getline(file_stu_in, line)){
        cout << line <<endl;
        
    }
        
    file_score_in.open("p1_score.txt");

    
    return 0;
}

//向文件写入数据
int writeToFile()
{
    return 0;
}

int main(int argc, char* argv[])
{
    readFromFile();
    return 0;
}