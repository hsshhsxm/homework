/*
魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市。 
红司令部，City 1，City 2，……，City n，蓝司令部

两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编号、生命值、攻击力这三种属性。 

双方的武士编号都是从1开始计算。红方制造出来的第n个武士，编号就是n。同样，蓝方制造出来的第n个武士，编号也是n。 

武士在刚降生的时候有一个生命值。 

在每个整点，双方的司令部中各有一个武士降生。 

红方司令部按照iceman、lion、wolf、ninja、dragon的顺序循环制造武士。 

蓝方司令部按照lion、dragon、ninja、iceman、wolf的顺序循环制造武士。 

制造武士需要生命元。 

制造一个初始生命值为m的武士，司令部中的生命元就要减少m个。 

如果司令部中的生命元不足以制造某个按顺序应该制造的武士，那么司令部就试图制造下一个。如果所有武士都不能制造了，则司令部停止制造武士。

给定一个时间，和双方司令部的初始生命元数目，要求你将从0点0分开始到双方司令部停止制造武士为止的所有事件按顺序输出。
一共有两种事件，其对应的输出样例如下： 

1) 武士降生 
输出样例： 004 blue lion 5 born with strength 5,2 lion in red headquarter
表示在4点整，编号为5的蓝魔lion武士降生，它降生时生命值为5，降生后蓝魔司令部里共有2个lion武士。（为简单起见，不考虑单词的复数形式）注意，每制造出一个新的武士，都要输出此时司令部里共有多少个该种武士。

2) 司令部停止制造武士
输出样例： 010 red headquarter stops making warriors
表示在10点整，红方司令部停止制造武士

输出事件时： 

首先按时间顺序输出； 

同一时间发生的事件，先输出红司令部的，再输出蓝司令部的。

输入
第一行是一个整数，代表测试数据组数。

每组测试数据共两行。 

第一行：一个整数M。其含义为， 每个司令部一开始都有M个生命元( 1 <= M <= 10000)。

第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000。
输出
对每组测试数据，要求输出从0时0分开始，到双方司令部都停止制造武士为止的所有事件。
对每组测试数据，首先输出"Case:n" n是测试数据的编号，从1开始 。
接下来按恰当的顺序和格式输出所有事件。每个事件都以事件发生的时间开头，时间以小时为单位，有三位。
样例输入
1
20
3 4 5 6 7
样例输出
Case:1
000 red iceman 1 born with strength 5,1 iceman in red headquarter
000 blue lion 1 born with strength 6,1 lion in blue headquarter
001 red lion 2 born with strength 6,1 lion in red headquarter
001 blue dragon 2 born with strength 3,1 dragon in blue headquarter
002 red wolf 3 born with strength 7,1 wolf in red headquarter
002 blue ninja 3 born with strength 4,1 ninja in blue headquarter
003 red headquarter stops making warriors
003 blue iceman 4 born with strength 5,1 iceman in blue headquarter
004 blue headquarter stops making warriors
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int timeCount = 0;
string redWarriorList[] = {"iceman","lion","wolf","ninja","dragon"};
string blueWarriorList[] = {"lion","dragon","ninja","iceman","wolf"};

class Warrior{
public:
    int No;
    int life;
    int attack;
    Warrior(){}
    Warrior(int n, int l):No(n),life(l){}
    Warrior(int n, int l, int a):No(n),life(l),attack(a){}
};
//dragon 、ninja、iceman、lion、wolf
class Dragon:public Warrior{

};

class Ninja:public Warrior{

};

class Iceman:public Warrior{

};

class Lion:public Warrior{

};

class Wolf:public Warrior{

};

class Tribe{
public:
    int currentLife;
    int dragonLife, ninjaLife, icemanLife, lionLife, wolfLife;
    vector<Dragon> dragonList;
    vector<Ninja> ninjaList;
    vector<Iceman> icemanList;
    vector<Lion> lionList;
    vector<Wolf> wolfList;
    Tribe(){}
    Tribe(int c, int d, int n, int i, int l, int w):
        currentLife(c),dragonLife(d),ninjaLife(d),icemanLife(i),lionLife(l),wolfLife(w){}
    virtual void printInfo(){}
    virtual void printFinsih(){}
    int tribeRunOnce(int i, int No);
};

class RedTribe:public Tribe{
public:
    void printInfo(string name, Warrior & currentWarrior, int num){
        cout.setf(ios::right);
        cout.fill('0');
        cout.width(3);
        cout << timeCount;
        cout << " " << "red" << " " << name << " ";
        cout << currentWarrior.No << " " << "born with strength" << " " >>currentWarrior.life << ",";
        cout << num << " " << name << " in red headquarter" << endl;
    }
    void printFinsih(){
    	cout.setf(ios::right);
        cout.fill('0');
        cout.width(3);
        cout << timeCount;
        cout << " " << "red headquarter stops making warriors" << endl;
    }
};

class BlueTribe:public Tribe{
public:
    void printInfo(string name, Warrior & currentWarrior, int num){
    	cout.setf(ios::right);
        cout.fill('0');
        cout.width(3);
        cout << timeCount;
        cout << " " << "blue" << " " << name << " ";
        cout << currentWarrior.No << " " << "born with strength" << " " >>currentWarrior.life << ",";
        cout << num << " " << name << " in blue headquarter" << endl;
    }
    void printFinsih(){
    	cout.setf(ios::right);
        cout.fill('0');
        cout.width(3);
        cout << timeCount;
        cout << " " << "blue headquarter stops making warriors" << endl;
    }
};

int Tribe::tribeRunOnce(int i, int No){
    if(redWarriorList[i] == "iceman"){
        currentLife -= icemanLife;
        if(currentLife < 0){
            printFinsih();
            return -1;
        }
        Iceman iceman(No,icemanLife);
        icemanList.push_back(iceman);
        printInfo(redWarriorList[i], iceman, icemanList.size());
        ++timeCount;
    } else if(redWarriorList[i] == "lion"){
        currentLife -= lionLife;
        if(currentLife < 0){
            printFinsih();
            return -1;
        }
        Lion lion(No, lionLife);
        lionList.push_back(lion);
        printInfo(redWarriorList[i], lion, lionList.size());
        ++timeCount;
    } else if(redWarriorList[i] == "wolf"){
        currentLife -= wolfLife;
        if(currentLife < 0){
            printFinsih();
            return -1;
        }
        Wolf wolf(No, wolfLife);
        wolfList.push_back(wolf);
        printInfo(redWarriorList[i], wolf, wolfList.size());
        ++timeCount;
    } else if(redWarriorList[i] == "ninja"){
        currentLife -= ninjaLife;
        if(currentLife < 0){
            printFinsih();
            return -1;
        }
        Ninja ninja(No, ninjaLife);
        ninjaList.push_back(ninja);
        printInfo(redWarriorList[i], ninja, ninjaList.size());
        ++timeCount;
    } else if(redWarriorList[i] == "dragon"){
        currentLife -= dragonLife;
        if(currentLife < 0){
            printFinsih();
            return -1;
        }
        Dragon dragon(No, dragonLife);
        dragonList.push_back(dragon);
        printInfo(redWarriorList[i], dragon, dragonList.size());
        ++timeCount;
    } else{
        return -1;
    }
    return 0;
}


void runBegin(int totalLife, int dragonLife, int ninjaLife, int icemanLife, int lionLife, int wolfLife){
    RedTribe redTribe(totalLife, dragonLife, ninjaLife, icemanLife, lionLife, wolfLife);
    BlueTribe blueTribe(totalLife, dragonLife, ninjaLife, icemanLife, lionLife, wolfLife);
    int i = 0, j = 1;
    int red_judge = redTribe.tribeRunOnce(i, j);
    int blue_judge = blueTribe.tribeRunOnce(i, j);
    while((red_judge == 0) || (blue_judge == 0)){
        ++i;
        ++j;
        if(red_judge != -1)
            red_judge = redTribe.tribeRunOnce(i, j);
        if(blue_judge != -1)
            blue_judge = blueTribe.tribeRunOnce(i, j);
    }
}

void readInput(){
    int caseNum;
    cin << caseNum;
    for(int i = 0; i < caseNum; ++i){
        int totalLife;
        int dragonLife,ninjaLife,icemanLife,lionLife,wolfLife;
        cin >> totalLife;
        cin >> dragonLife >> ninjaLife >> icemanLife >> lionLife >> wolfLife;
        cout << "case:" << i + 1 >> endl;
        runBegin();
    }
}

int main(){
    readInput();
    return 0;
}