#include <iostream>
#include <string>
#include <vector>
#include <map>
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

int count = 0;
vector<Student> student_list;
vector<Score> score_list;

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
    else
        return -1;
}

int deleteStudentInfo(string ID)
{
    int i = searchStudentInfo(ID,"");
    student_list.erase(student_list.begin() + i);
    return 0;
}

int modifyStudentInfo(string ID, string name, string birthday, string collage, string department)
{
    int i = searchStudentInfo(ID, name);
    student_list[i].name = name;
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

vector<string> searchStudentCourse(string ID)
{
    vector<string> course_list;
    for(int i = 0; i < count; i++)
    {
        if (score_list[i].ID == ID)
            course_list.push_back(score_list[i].coursename);
    }
    return course_list;
}

int searchStudentScoreID(string ID, string coursename)
{
    for (int i = 0; i<count; i++)
    {
        if(score_list[i].ID == ID && score_list[i].coursename == coursename)
            return i;
    }
}

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

int deleteStudentOneScore(string ID, string coursename)
{
	int i = searchStudentScoreID(ID, coursename);
    score_list.erase(score_list.begin() + i);
    return 0;
}

int deleteStudentAllScore(string ID)
{
    vector<string> course_list;
    course_list = searchStudentCourse(ID);
    for(int i = 0; i < course_list.size(); i++)
        deleteStudentOneScore(ID,course_list[i]);
    return 0;
}

int modifyStudentScore(string ID, string coursename, int score)
{
	int i = searchStudentScoreID(ID, coursename);
    score_list[i].score = score;
    return 0;
}

int readFromFile()
{
    return 0;
}

int writeToFile()
{
    return 0;
}

int main(int argc, char* argv[])
{
    
    return 0;
}