#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class warrior
{
protected:
    int id;
    int lifeValue;//士兵生命值
    string name;
public:
    static string weaponNames[3];
    warrior():id(-1), lifeValue(0), name("") {}
    warrior(int theId, int theLifeValue, string theName):id(theId), lifeValue(theLifeValue), name(theName) {}
    ~warrior(){}
    int getId() {return id;}
    string* getWeaponNames() {return weaponNames;}
    virtual void print(const int times, const string campName, const int certainWarriorCounts) {};//纯虚函数
};
string warrior::weaponNames[3] = {"sword", "bomb", "arrow"};
class dragon : public warrior
{
private:
    float morale;//士气属性
public:
    dragon(int theId, int theLifeValue, int headquarterLifeValue):warrior(theId, theLifeValue, "dragon")
    {
        morale = (float)headquarterLifeValue / theLifeValue;
    }
    ~dragon() {}
    float getMorale() {return morale;}
    string getWeaponName() 
    {
        int index = this->getId() % 3;
        return this->getWeaponNames()[index];
    }
    void print(const int times, const string campName, const int certainWarriorCounts)
    {
        cout << setfill('0') << setw(3) << times << " " << campName << " " << this->name
            << " " << this->id << " born with strength " << this->lifeValue << "," << certainWarriorCounts
            << " " << this->name << " in " << campName << " headquarter" << endl;
        cout << "It has a " << this->getWeaponName() << ",and it's morale is " << setprecision(2) << fixed <<this->getMorale() << endl;
    }
};
class ninja : public warrior
{
private:
public:
    ninja(int theId, int theLifeValue) : warrior(theId, theLifeValue, "ninja") {}
    ~ninja() {}
    string getFirstWeaponName()
    {
        int index = this->getId() % 3;
        return this->getWeaponNames()[index];
    }
    string getSecondWeaponName()
    {
        int index = (this->getId() + 1) % 3;
        return this->getWeaponNames()[index];
    }
    void print(const int times, const string campName, const int certainWarriorCounts)
    {
        cout << setfill('0') << setw(3) << times << " " << campName << " " << this->name
            << " " << this->id << " born with strength " << this->lifeValue << "," << certainWarriorCounts
            << " " << this->name << " in " << campName << " headquarter" << endl;
        cout << "It has a " << this->getFirstWeaponName() << " and a " << this->getSecondWeaponName() << endl;
    }
};
class iceman : public warrior
{

public:
    iceman(int theId, int theLifeValue) : warrior(theId, theLifeValue, "iceman") {}
    ~iceman() {}
    string getWeaponName()
    {
        int index = this->getId() % 3;
        return this->getWeaponNames()[index];
    }
    void print(const int times, const string campName, const int certainWarriorCounts)
    {
        cout << setfill('0') << setw(3) << times << " " << campName << " " << this->name
            << " " << this->id << " born with strength " << this->lifeValue << "," << certainWarriorCounts
            << " " << this->name << " in " << campName << " headquarter" << endl;
        cout << "It has a " << this->getWeaponName() << endl;
    }
};

class lion : public warrior
{
private:
    int loyalty;
public:
    lion(int theId, int theLifeValue, int headquarterLifeValue) : warrior(theId, theLifeValue, "lion")
    {
        loyalty = headquarterLifeValue;
    }
    ~lion() {}
    int getLoyalty() {return loyalty;}
    void print(const int times, const string campName, const int certainWarriorCounts)
    {
        cout << setfill('0') << setw(3) << times << " " << campName << " " << this->name
            << " " << this->id << " born with strength " << this->lifeValue << "," << certainWarriorCounts
            << " " << this->name << " in " << campName << " headquarter" << endl;
        cout << "It's loyalty is " << this->getLoyalty() << endl;
    }
};

class wolf : public warrior
{
public:
    wolf(int theId, int theLifeValue) : warrior(theId, theLifeValue, "wolf") {}
    ~wolf() {}
    void print(const int times, const string campName, const int certainWarriorCounts)
    {
        cout << setfill('0') << setw(3) << times << " " << campName << " " << this->name
            << " " << this->id << " born with strength " << this->lifeValue << "," << certainWarriorCounts
            << " " << this->name << " in " << campName << " headquarter" << endl;
    }
};
class militarycamp
{
private:
    string name;
    int lifeValue;//部落生命值
    int counts;//士兵数量
//  int ptrsize;
//  warrior* ptr;//指向动态分配的武士的数组
    int currentPosition;//记录产生战士类别的当前位置
    int minWarriorValue;//计算出战士中的最小生命值  
    int warriorValues[5];//记录每种战士生命值的数组
    string warriorNames[5];//记录每种战士名字的数组
    int warriorCounts[5];//记录每种战士数量的数组
public:
    static string priorNames[5];//记录战士名字的数组
    static int times;//产生战士的次数
    bool hadStop;//是否停止出兵
    militarycamp(const int theLifeValue, string theName, const int theWarriorValue[],
        const int theWarriorOrder[]);
    ~militarycamp() 
    {
/*
        if(ptr) 
        {
            delete[] ptr;
        }
*/
    }
    void push_back(warrior* w);
    void warriorManufacture();//制造武士
};
string militarycamp::priorNames[5] = {"dragon", "ninja", "iceman" ,"lion" ,"wolf"};
int militarycamp::times = 0;
militarycamp::militarycamp(const int theLifeValue, string theName, const int theWarriorValue[],
    const int theWarriorOrder[]):hadStop(false),currentPosition(0),counts(0),lifeValue(theLifeValue),name(theName)//,ptr(NULL),ptrsize(0)
{
    for (int i = 0; i < 5; i++)
    {
        warriorCounts[i] = 0;
        warriorNames[i] = priorNames[theWarriorOrder[i]];//由给定的顺序和原始战士名字的数组，得到该总部战士名字的数组
        warriorValues[i] = theWarriorValue[theWarriorOrder[i]];//由给定的顺序和原始战士名字的数组，得到该总部战士生命值的数组
    }

    minWarriorValue = warriorValues[0];
    for (int i = 1; i < 5; i++)
    {
        if (warriorValues[i] < minWarriorValue)
        {
            minWarriorValue = warriorValues[i];
        }
    }
}
/*
制造武士
*/
void militarycamp::warriorManufacture()
{
    //生命值小于最小战士生命值，停止出兵，打印命令
    if (lifeValue < minWarriorValue)
    {
        cout << setfill('0') << setw(3) << times << ' ' << name << " headquarter stops making warriors" << endl;
        hadStop = true;
    }
    else
    {
        //从上面的判断句筛选后，现在一定能出兵
        //从当前position开始增加，到某个位置出兵了停止
        while(true)
        {
            if (lifeValue >= warriorValues[currentPosition])
            {
                counts++;
                warriorCounts[currentPosition]++;
                lifeValue -= warriorValues[currentPosition];
                if (warriorNames[currentPosition] == "dragon")
                {
                    dragon theDragon(counts, warriorValues[currentPosition], lifeValue);
//                  push_back(&theDragon);
                    theDragon.print(times, name, warriorCounts[currentPosition]);
                } 
                else if(warriorNames[currentPosition] == "ninja")
                {
                    ninja theNinja(counts, warriorValues[currentPosition]);
//                  push_back(&theNinja);
                    theNinja.print(times, name, warriorCounts[currentPosition]);
                }
                else if (warriorNames[currentPosition] == "iceman")
                {
                    iceman theIceman(counts, warriorValues[currentPosition]);
//                  push_back(&theIceman);
                    theIceman.print(times, name, warriorCounts[currentPosition]);
                }
                else if (warriorNames[currentPosition] == "lion")
                {
                    lion theLion(counts, warriorValues[currentPosition], lifeValue);
//                  push_back(&theLion);
                    theLion.print(times, name, warriorCounts[currentPosition]);
                }
                else if (warriorNames[currentPosition] == "wolf")
                {
                    wolf theWolf(counts, warriorValues[currentPosition]);
//                  push_back(&theWolf);
                    theWolf.print(times, name, warriorCounts[currentPosition]);
                }           

                currentPosition == 4 ? currentPosition = 0 : currentPosition++;
                break;
            } 
            else
            {
                currentPosition == 4 ? currentPosition = 0 : currentPosition++;
            }
        }
    }
}
/*
//加上此部分发生内存泄漏问题，尚未解决
void militarycamp::push_back(warrior* w)//在数组尾部添加一个元素
{
    if (ptr)
    {
        warrior* tmpPtr = new warrior[ptrsize+1];//重新分配空间
        memcpy(tmpPtr, ptr, sizeof(warrior)*(ptrsize));
        delete[] ptr;
        ptr = tmpPtr;
    }
    else//数组本来就是空的
    {
        ptr = new warrior[1];
    }

    ptr[ptrsize++] = *w;//加入新的数组元素

}
*/
int main()
{
	    freopen("in.txt","r",stdin);
    freopen("stdout.txt","w",stdout);
    const int redOrder[5] = {2, 3, 4, 1, 0};//红色总部的出兵顺序
    const int blueOrder[5] = {3, 0, 1, 2, 4};//蓝色总部的出兵顺序
    int n = 0;//测试数
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int priorValue[5], headquartersValue;
        cin >> headquartersValue; //获取总部生命值
        //获取每种战士的生命值
        for (int j = 0; j < 5; j++)
        {
            cin >> priorValue[j];
        }
        cout << "Case:" << i << endl;       

        //初始化红军总部和蓝军总部
        militarycamp redOne = militarycamp(headquartersValue, "red", priorValue, redOrder);
        militarycamp blueOne = militarycamp(headquartersValue, "blue", priorValue, blueOrder);
        militarycamp::times = 0;//派兵次数置零
        while(!redOne.hadStop || !blueOne.hadStop)
        {
            if (!redOne.hadStop)
            {
                redOne.warriorManufacture();
            }
            if (!blueOne.hadStop)
            {
                blueOne.warriorManufacture();
            }
            militarycamp::times++;
        }
    }
    return 0;
}
