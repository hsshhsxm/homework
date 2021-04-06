#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

int timeCount = 0;
string redWarriorList[] = {"iceman","lion","wolf","ninja","dragon"};
string blueWarriorList[] = {"lion","dragon","ninja","iceman","wolf"};
string waponList[] = {"sword","bomb","arrow"};
#define MaxWarrior 5

//武士类
class Warrior{
public:
    int No;
    int life;
    int attack;
    virtual void printWarriorInfo(double n){};
};
//dragon 、ninja、iceman、lion、wolf
class Dragon:public Warrior{
public:
    int waponNo;
    double morale;
    void printWarriorInfo(double n){
        cout << "It has a " << waponList[waponNo] << ",and it's morale is ";
        cout<<setiosflags(ios::fixed)<<setprecision(2);
        cout << morale << endl;
    }
};

class Ninja:public Warrior{
public:
    int waponNo[2];
    void printWarriorInfo(double n){
        cout << "It has a " << waponList[waponNo[0]] << " and a " << waponList[waponNo[1]] << endl;
    }
};

class Iceman:public Warrior{
public:
    int waponNo;
    void printWarriorInfo(double n){
        cout << "It has a " << waponList[waponNo] << endl;
    }
};

class Lion:public Warrior{
public:
    int loyalty;
    void printWarriorInfo(double n){
        cout << "It's loyalty is " << (int)n << endl;
    }
};

class Wolf:public Warrior{
public:
};

//红蓝两方的类
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
    ~Tribe(){}
    virtual void printInfo(string name, Warrior & currentWarrior, int num){};
    virtual void printFinsih(){};
    int tribeRunOnce(int i, int No, int listNum);//listNum =0, red; listNum =1, blue
};

//红方类
class RedTribe:public Tribe{
public:
    RedTribe(){}
    RedTribe(int c, int d, int n, int i, int l, int w){
        currentLife = c;
        dragonLife = d;
        ninjaLife = n;
        icemanLife = i;
        lionLife = l;
        wolfLife = w;
    }
    virtual void printInfo(string name, Warrior & currentWarrior, int num){
        cout << setfill('0') << setw(3) << timeCount << setfill(' ');
        cout << " " << "red" << " " << name << " ";
        cout << currentWarrior.No << " born with strength " << currentWarrior.life << ",";
        cout << num << " " << name << " in red headquarter" << endl;
    }
    virtual void printFinsih(){
        cout << setfill('0') << setw(3) << timeCount << setfill(' ');
        cout << " red headquarter stops making warriors" << endl;
    }
};

//蓝方类
class BlueTribe:public Tribe{
public:
    BlueTribe(){}
    BlueTribe(int c, int d, int n, int i, int l, int w){
        currentLife = c;
        dragonLife = d;
        ninjaLife = n;
        icemanLife = i;
        lionLife = l;
        wolfLife = w;
    }
    virtual void printInfo(string name, Warrior & currentWarrior, int num){
        cout << setfill('0') << setw(3) << timeCount << setfill(' ');
        cout << " " << "blue" << " " << name << " ";
        cout << currentWarrior.No << " born with strength " << currentWarrior.life << ",";
        cout << num << " " << name << " in blue headquarter" << endl;
    }
    virtual void printFinsih(){
        cout << setfill('0') << setw(3) << timeCount << setfill(' ');
        cout << " blue headquarter stops making warriors" << endl;
    }
};

//制造一个武士
int Tribe::tribeRunOnce(int i, int No, int listNum){
    //确定是红方还是蓝方，0红1蓝
    string list[MaxWarrior];
    if(listNum == 0){
        for(int j = 0; j < MaxWarrior; j++){
            list[j] = redWarriorList[j];
        }
    } else{
        for(int j = 0; j < MaxWarrior; j++){
            list[j] = blueWarriorList[j];
        }
    }
    //判断怪物类型进行建造
    if(list[i] == "iceman"){
        if(currentLife < icemanLife){
            return 1;
        }
        currentLife -= icemanLife;
        Iceman iceman;
        iceman.No = No;
        iceman.life = icemanLife;
        iceman.waponNo = iceman.No % 3;
        icemanList.push_back(iceman);
        printInfo(list[i], iceman, icemanList.size());
        iceman.printWarriorInfo(0);
    } else if(list[i] == "lion"){
        if(currentLife < lionLife){
            return 1;
        }
        currentLife -= lionLife;
        Lion lion;
        lion.No = No;
        lion.life = lionLife;
        lionList.push_back(lion);
        printInfo(list[i], lion, lionList.size());
        lion.printWarriorInfo(currentLife);
    } else if(list[i] == "wolf"){
        if(currentLife < wolfLife){
            return 1;
        }
        currentLife -= wolfLife;
        Wolf wolf;
        wolf.No = No;
        wolf.life = wolfLife;
        wolfList.push_back(wolf);
        printInfo(list[i], wolf, wolfList.size());
    } else if(list[i] == "ninja"){
        if(currentLife < ninjaLife){
            return 1;
        }
        currentLife -= ninjaLife;
        Ninja ninja;
        ninja.No = No;
        ninja.life = ninjaLife;
        ninja.waponNo[0] = No%3;
        ninja.waponNo[1] = (No+1)%3;
        ninjaList.push_back(ninja);
        printInfo(list[i], ninja, ninjaList.size());
        ninja.printWarriorInfo(0);
    } else if(list[i] == "dragon"){
        if(currentLife < dragonLife){
            return 1;
        }
        currentLife -= dragonLife;
        Dragon dragon;
        dragon.No = No;
        dragon.life = dragonLife;
        dragon.waponNo = dragon.No % 3;
        dragon.morale = (double)currentLife / (double)dragonLife;
        dragonList.push_back(dragon);
        printInfo(list[i], dragon, dragonList.size());
        dragon.printWarriorInfo(0);
    } else{
    }
    return 0;
}

//设定初始生命值等参数，开始运行
void runBegin(int totalLife, int dragonLife, int ninjaLife, int icemanLife, int lionLife, int wolfLife){
    //设置初始参数
    RedTribe redTribe(totalLife, dragonLife, ninjaLife, icemanLife, lionLife, wolfLife);
    BlueTribe blueTribe(totalLife, dragonLife, ninjaLife, icemanLife, lionLife, wolfLife);
    int judgeMin[MaxWarrior] = {dragonLife, ninjaLife, icemanLife, lionLife, wolfLife};
    int *min = min_element(judgeMin, judgeMin + 5);
    int i = 0, j = 0, k = 1;//i for red; j for blue
    //红方运行一次，进行检查
    int red_judge = redTribe.tribeRunOnce(i, k, 0);
    while(red_judge == 1){
        if(redTribe.currentLife >= *min){
            if(i<4)
                red_judge = redTribe.tribeRunOnce(++i, k, 0);
            else{
                i = 0;
                red_judge = redTribe.tribeRunOnce(i, k, 0);
            }
        } 
        else{
            red_judge = -1;
            redTribe.printFinsih();
        }
    }
    //蓝方运行一次，进行检查
    int blue_judge = blueTribe.tribeRunOnce(j, k, 1);
    while(blue_judge == 1){
        if(blueTribe.currentLife >= *min){
            if(j < 4)
                blue_judge = blueTribe.tribeRunOnce(++j, k, 1);
            else{
                j = 0;
                blue_judge = blueTribe.tribeRunOnce(j, k, 1);
            }
        } 
        else{
            blueTribe.printFinsih();
            blue_judge = -1;
        }
    }
    ++timeCount;
    //双方循环运行
    while((red_judge != -1) || (blue_judge != -1)){
        ++k;
        if(i < 4)
            ++i;
        else   
            i = 0;
        if(j < 4)
            ++j;
        else   
            j = 0;

        if(red_judge != -1)
            red_judge = redTribe.tribeRunOnce(i, k, 0);
        while(red_judge == 1){
            if(redTribe.currentLife >= *min){
                if(i<4)
                    red_judge = redTribe.tribeRunOnce(++i, k, 0);
                else{
                    i = 0;
                    red_judge = redTribe.tribeRunOnce(i, k, 0);
                }
            } 
            else{
                red_judge = -1;
                redTribe.printFinsih();
            }
        }

        if(blue_judge != -1)
            blue_judge = blueTribe.tribeRunOnce(j, k, 1);
        while(blue_judge == 1){
            if(blueTribe.currentLife >= *min){
                if(j < 4)
                    blue_judge = blueTribe.tribeRunOnce(++j, k, 1);
                else{
                    j = 0;
                    blue_judge = blueTribe.tribeRunOnce(j, k, 1);
                }
            } 
            else{
                blueTribe.printFinsih();
                blue_judge = -1;
            }
        }
        ++timeCount;
    }
}

//读取数据，传递参数
void readInput(){
    int caseNum;
    cin >> caseNum;
    int allTotalLife[caseNum];
    int allLife[caseNum][MaxWarrior];
    for(int i = 0; i < caseNum; ++i){
        cin >> allTotalLife[i];
        for(int j = 0; j < MaxWarrior; ++j){
            cin >> allLife[i][j];
        }
    }
    for(int i = 0; i < caseNum; ++i){
        cout << "Case:" << i + 1 << endl;
        runBegin(allTotalLife[i], allLife[i][0], allLife[i][1], allLife[i][2], allLife[i][3], allLife[i][4]);
        timeCount = 0;
    }
}

int main(){
    freopen("datapub.in","r",stdin);
    freopen("out.out","w",stdout);
    readInput();
    return 0;
}