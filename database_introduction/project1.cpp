#include <iostream>
#include <string>
#include <vector>
using namespace std;

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

int count = 0
vector<Student>student_list;
vector<Score>score_list;

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

int searchStudentInfo(string ID = "", string name = "")
{
    if (ID != "")
    {
        for(int i = 0; i < count; i++)
        {
            if (student_list[i].ID == ID)
                return i;
        }
    }
    else if (name != "")
    {
        for(int i = 0; i < count; i++)
        {
            if (student_list[i].name == name)
                return i;
        }

    }
    else{
        return -1;
    }
}

int deleteStudentInfo(string ID)
{
    int i = searchStudentInfo(ID,);
    return 0;
}

int modifyStudentInfo(string ID, string name, string birthday, string collage, string department)
{
    int i = searchStudentInfo(ID, name);
    student_list[i].birthday = birthday;
    student_list[i].collage = collage;
    student_list[i].department = department;
    return 0;
}

int addStudentScore(string ID, string coursename, int score)
{
    Score temp_score;
    temp_score.ID = ID;
    temp_score.coursename = coursename;
    temp_score.score = score;
    score_list.push_back(temp_score);
    return 0;
}

int deleteStudentScore(string ID)
{
    return 0;
}

int modifyStudentScore(string ID, string coursename, int score)
{
    return 0;
}

int readFromFile(file* fp)
{
    return 0;
}

int main()
{
    
    return 0;
}