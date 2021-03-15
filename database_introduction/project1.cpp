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
    if (i == -1)
        return -1;
    student_list.erase(student_list.begin() + i);
    return 0;
}

//修改学生信息
int modifyStudentInfo(string ID, string name, string birthday, string collage, string department)
{
    int i = searchStudentInfo(ID, name);
    if (i == -1)
        return -1;
    student_list[i].name = name;
    student_list[i].birthday = birthday;
    student_list[i].collage = collage;
    student_list[i].department = department;
    return 0;
}

//添加学生成绩
int addStudentScore(string ID, string coursename, int score)
{
    if (ID == "" || coursename == "")
        return -1;
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

//查找学生所修的课程所在位置
vector<int> searchStudentCourseIndex(string ID)
{
    vector<int> course_list;
    for(int i = 0; i < score_list.size(); i++)
    {
        if (score_list[i].ID == ID)
            course_list.push_back(i);
    }
    return course_list;
}

//查找学生某一课程成绩所在的位置
int searchStudentScoreID(string ID, string coursename)
{
    for (int i = 0; i< score_list.size(); i++)
    {
        if(score_list[i].ID == ID && score_list[i].coursename == coursename)
            return i;
    }
    return -1;
}

//删除学生一个课程的成绩
int deleteStudentOneScore(string ID, string coursename)
{
	int i = searchStudentScoreID(ID, coursename);
    if (i == -1)
        return -1;
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

//修改学生某一课程的成绩
int modifyStudentScore(string ID, string coursename, int score)
{
	int i = searchStudentScoreID(ID, coursename);
    if (i == -1)
        return -1;
    score_list[i].score = score;
    return 0;
}

//从文件读取数据
int readFromFile()
{
    cout << "信息读取中" << endl;
    //读取学生信息
    ifstream file_stu_in;
    file_stu_in.open("p1_student.txt");
    string line;
    while(getline(file_stu_in, line)){
        //cout << line <<endl;
        string buf;
        Student temp_stu;
        vector<string> temp;
        stringstream split_string(line);
        while(split_string >> buf){
            temp.push_back(buf);
            //cout << buf <<endl;
        }
        temp_stu.ID = temp[0];
        temp_stu.name = temp[1];
        temp_stu.birthday = temp[2];
        temp_stu.collage = temp[3];
        temp_stu.department = temp[4];
        student_list.push_back(temp_stu);
    }
    //读取成绩信息
    ifstream file_score_in;
    file_score_in.open("p1_score.txt");
    while(getline(file_score_in, line)){
        string buf;
        Score temp_score;
        vector<string> temp;
        stringstream split_string(line);
        while(split_string >> buf){
            temp.push_back(buf);
            //cout << buf <<endl;
        }
        temp_score.ID = temp[0];
        temp_score.coursename = temp[1];
        temp_score.score = stoi(temp[2]);
        score_list.push_back(temp_score);
    }
    cout << "信息读取成功" << endl;
    return 0;
}

//向文件写入数据
int writeToFile()
{
    return 0;
}

//输出学生信息
void printStuInfo(int i)
{
    cout << "学号：" << student_list[i].ID << "  ";
    cout << "姓名：" << student_list[i].name << "  ";
    cout << "出生日期：" << student_list[i].birthday << "  ";
    cout << "学院：" << student_list[i].collage << "  ";
    cout << "系：" << student_list[i].department << endl;
}

//输出成绩信息
void printScoreInfo(int i)
{
    cout << "学号：" << score_list[i].ID << "  ";
    cout << "课程名：" << score_list[i].coursename << "  ";
    cout << "成绩：" << score_list[i].score <<endl;
}

int terminal()
{
    cout << "输入 help 获取帮助" <<endl;
    while(1){
        string str_in;
        cout << ">";
        getline(cin, str_in);
        //cout << (str_in);
        string buf;
        vector<string> str_split;
        stringstream split_string(str_in);
        while(split_string >> buf){
            str_split.push_back(buf);
            //cout << buf <<endl;
        }
        if(str_split[0] == "help"){
            cout << "退出系统：exit" << endl;
            cout << "查看帮助：exit" << endl;
            cout << "添加学生信息：addstuinfo <ID> <name> <birthday> <colleage> <department>" << endl;
            cout << "修改学生信息：modifystuinfo <ID> <name> <birthday> <colleage> <department>" << endl;
            cout << "删除学生信息：deletestuinfo <ID>" << endl;
            cout << "添加成绩信息：addscoreinfo <ID> <coursename> <score>" << endl;
            cout << "修改成绩信息：modifyscoreinfo <ID> <coursename> <score>" << endl;
            cout << "删除单科成绩信息：deleteonescoreinfo <ID> <coursename>" << endl;
            cout << "删除全部成绩信息：deleteallscoreinfo <ID>" << endl;
            cout << "通过学号查询学生信息：searchstubyid <ID>" << endl;
            cout << "通过姓名查询学生信息：searchstubyname <name>" << endl;
            cout << "通过学号和课程名查询学生单科成绩信息：searchonescore <ID> <coursename>" << endl;
            cout << "通过学号查询学生所有成绩信息：searchallscore <ID>" << endl;
        } else if(str_split[0] == "addstuinfo"){
            int i = addStudentInfo(str_split[1], str_split[2], str_split[3], str_split[4], str_split[5]);
            if (i == 0)
                cout << "学生信息添加成功" << endl;
            else
                cout << "学生信息添加失败：请检查输入" << endl;
        } else if(str_split[0] == "modifystuinfo"){
            int i = modifyStudentInfo(str_split[1], str_split[2], str_split[3], str_split[4], str_split[5]);
            if (i == 0)
                cout << "学生信息修改成功" << endl;
            else
                cout << "学生信息修改失败：未找到此学生信息" << endl;
        } else if(str_split[0] == "deletestuinfo"){
            int i = deleteStudentInfo(str_split[1]);
            if (i == 0)
                cout << "学生信息删除成功" << endl;
            else
                cout << "学生信息删除失败：未找到此学生信息" << endl;
        } else if(str_split[0] == "addscoreinfo"){
            int i = addStudentScore(str_split[1], str_split[2], stoi(str_split[3]));
            if (i == 0)
                cout << "成绩信息添加成功" << endl;
            else
                cout << "成绩信息添加失败：请检查输入" << endl;
        } else if(str_split[0] == "modifyscoreinfo"){
            int i = modifyStudentScore(str_split[1], str_split[2], stoi(str_split[3]));
            if (i == 0)
                cout << "成绩信息修改成功" << endl;
            else
                cout << "成绩信息修改失败：未找到此成绩信息" << endl;
        } else if(str_split[0] == "deleteonescoreinfo"){
            int i = deleteStudentOneScore(str_split[1], str_split[2]);
            if (i == 0)
                cout << "成绩信息删除成功" << endl;
            else
                cout << "成绩信息删除失败：未找到此成绩信息" << endl;
        } else if(str_split[0] == "deleteallscoreinfo"){
            deleteStudentAllScore(str_split[1]);
            cout << "该学生的所有成绩信息删除成功" << endl;
        } else if(str_split[0] == "searchstubyid"){
            int i = searchStudentInfo(str_split[1], "");
            if (i >= 0)
                printStuInfo(i);
            else
                cout << "未找到该学生，请检查输入" << endl;
        } else if(str_split[0] == "searchstubyname"){
            int i = searchStudentInfo("", str_split[1]);
            if (i >= 0)
                printStuInfo(i);
            else
                cout << "未找到该学生信息，请检查输入" << endl;
        } else if(str_split[0] == "searchonescore"){
            int i = searchStudentScoreID(str_split[1], str_split[2]);
            if (score_list[i].ID != "")
                printScoreInfo(i);
            else
                cout << "未找到该成绩信息，请检查输入" << endl;
        } else if(str_split[0] == "searchallscore"){
            vector<int> course_list;
            course_list = searchStudentCourseIndex(str_split[1]);
            if(course_list.size() == 0)
                cout << "未找到该学生的成绩信息，请检查输入" <<endl;
            for(int i = 0; i < course_list.size(); i++)
                printScoreInfo(course_list[i]);
        } else if(str_split[0] == "exit"){
            break;
        } else{
            cout << "无效命令，请检查输入" << endl;
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    readFromFile();
    terminal();
    return 0;
}