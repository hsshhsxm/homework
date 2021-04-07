#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

int timeHourCount = 0;
int timeMinCount = 0;
int timeCount = 0;
string redWarriorList[] = {"iceman","lion","wolf","ninja","dragon"};
string blueWarriorList[] = {"lion","dragon","ninja","iceman","wolf"};
string waponList[] = {"sword","bomb","arrow"};
#define MaxWarrior 5

//武器类
class Wapon{
public:
    int No;
    int attackPower;
    int durability;
    Wapon(){}
    Wapon(int n,int a, int d):No(n),attackPower(a),durability(d){}
    virtual int usedOnce(){return 1;};
};

class Sword:public Wapon{
public:
    Sword(int n,int a, int d = 1):Wapon(n,a,d){}
    int usedOnce(){return 1;};
};

class Bomb:public Wapon{
public:
    int attackSelf;
    Bomb(int n,int a, int d = 1):Wapon(n,a,d){attackSelf = a/2;}
    int usedOnce(){
        --durability;
        return durability;
    }
};

class Arrow:public Wapon{
public:
    Arrow(int n,int a, int d = 2):Wapon(n,a,d){}
    int usedOnce(){
        --durability;
        return durability;
    }
};
//武器排序函数，倒序，从尾部开始取
bool sortFun(const Wapon & w1, const Wapon &w2){
    if(w1.No == 2 && w2.No == 2){
        return w1.durability > w2.durability;
    }
    return w1.No > w2.No;
}

//武士类
class Warrior{
public:
    string name;
    int No;
    int life;
    int attack;
    int waponNo;
    int pos;//当前所在城市
    vector<Wapon> waponOwned;
    virtual void printWarriorInfo(double n){};
    virtual void goAhead(int cityNo){};
    int attackOnce(int i);//返回武器的攻击力
    int attackedOnce(int att){life -= att; return life;}//返回剩余生命值
};
//dragon 、ninja、iceman、lion、wolf
class Dragon:public Warrior{
public:
    double morale;
    void printWarriorInfo(double n){
        cout << "It has a " << waponList[waponNo] << ",and it's morale is ";
        cout<<setiosflags(ios::fixed)<<setprecision(2);
        cout << morale << endl;
    }
    void printDragonYell(string redOrBlue, Warrior & currentWarrior,int cityNo){
        cout << setfill('0') << setw(3) << timeHourCount << setfill(' ');
        cout << ":" ;
        cout << setfill('0') << setw(2) << timeMinCount << setfill(' ');
        cout << " " << redOrBlue << " dragon " << currentWarrior.No << " yelled in city " <<  cityNo <<endl;
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
    void printLionRun(string redOrBlue,Warrior & currentWarrior){
        cout << setfill('0') << setw(3) << timeHourCount << setfill(' ');
        cout << ":" ;
        cout << setfill('0') << setw(2) << timeMinCount << setfill(' ');
        cout << " " << redOrBlue << " lion " << currentWarrior.No << " ran away" << endl;
    }
};

class Wolf:public Warrior{
public:
    void snatchWapon(Warrior & currentWarrior, Warrior & antiWarrior,int cityNo){
        if(antiWarrior.name == "wolf")
            return;
        int minWaponNo = antiWarrior.waponOwned.end()->No;
        if(minWaponNo != 2)//如果对方最小的武器不是arrow，直接抢即可
        {
            for(int i = antiWarrior.waponOwned.size() - 1; i >= 0 ; --i){
                if(antiWarrior.waponOwned[i].No > minWaponNo)
                    break;
                if(currentWarrior.waponOwned.size() > 10)
                    break;
                Wapon tmp(antiWarrior.waponOwned[i].No, antiWarrior.waponOwned[i].attackPower, waponOwned[i].durability);
                currentWarrior.waponOwned.push_back(tmp);
                antiWarrior.waponOwned.pop_back();
            }
        }
        else//如果对方最小的是arrow，先抢没用过的，倒过来抢
        {
            for(int i = 0; i < antiWarrior.waponOwned.size(); ++i){
                if(currentWarrior.waponOwned.size() > 10)
                    break;
                Wapon tmp(antiWarrior.waponOwned[i].No, antiWarrior.waponOwned[i].attackPower, waponOwned[i].durability);
                currentWarrior.waponOwned.push_back(tmp);
                vector<Wapon>::iterator k = antiWarrior.waponOwned.begin();
                antiWarrior.waponOwned.erase(k);
            }
        }
        //对抢到的武器进行排序
        sort(currentWarrior.waponOwned.begin(), currentWarrior.waponOwned.end(), sortFun);
    }
};

//红蓝两方的类
class Tribe{
public:
    int currentLife;
    int dragonLife, ninjaLife, icemanLife, lionLife, wolfLife;
    int dragonAttack, ninjaAttack, icemanAttack, lionAttack, wolfAttack;
    int cityNum,loyaltyMinus,totalTime;
    vector<Dragon> dragonList;
    vector<Ninja> ninjaList;
    vector<Iceman> icemanList;
    vector<Lion> lionList;
    vector<Wolf> wolfList;
    vector<Warrior> warriorList;
    Tribe(){}
    ~Tribe(){}
    virtual void printBornInfo(Warrior & currentWarrior){};
    virtual void printGoAheadInfo(Warrior & currentWarrior, int cityNo){};
    virtual void printFinsih(){};
    int tribeBornOnce(int i, int No, int listNum);//listNum =0, red; listNum =1, blue
    int tribeFightOnce(Warrior & currentWarrior, int waponNo, Warrior & antiWarrior);
    virtual void tribeRun(){};
};

//红方类
class RedTribe:public Tribe{
public:
    RedTribe(){}
    RedTribe(int c, int cm, int lm, int tt, int d, int n, int i, int l, int w,int da,int na, int ia, int la, int wa){
        currentLife = c;
        cityNum = cm;
        loyaltyMinus = lm;
        totalTime = tt;
        dragonLife = d;
        ninjaLife = n;
        icemanLife = i;
        lionLife = l;
        wolfLife = w;
        dragonAttack = da;
        ninjaAttack = na;
        icemanAttack = ia;
        lionAttack = la;
        wolfAttack = wa;
    }
    virtual void printBornInfo(Warrior & currentWarrior){
        cout << setfill('0') << setw(3) << timeHourCount << setfill(' ');
        cout << ":" ;
        cout << setfill('0') << setw(2) << timeMinCount << setfill(' ');
        cout << " red " << currentWarrior.name << " " << currentWarrior.No << " born" << endl;
    }
    virtual void printGoAheadInfo(Warrior & currentWarrior, int cityNo){
        cout << setfill('0') << setw(3) << timeHourCount << setfill(' ');
        cout << ":" ;
        cout << setfill('0') << setw(2) << timeMinCount << setfill(' ');
        cout << " red" << currentWarrior.name << " " << currentWarrior.No << " marched to city " << cityNo 
        << " with " << currentWarrior.life << " elements and force "<< currentWarrior.attack<< endl;
    }
    virtual void printFinsih(){
    }
};

//蓝方类
class BlueTribe:public Tribe{
public:
    BlueTribe(){}
    BlueTribe(int c, int cm, int lm, int tt, int d, int n, int i, int l, int w,int da,int na, int ia, int la, int wa){
        currentLife = c;
        cityNum = cm;
        loyaltyMinus = lm;
        totalTime = tt;
        dragonLife = d;
        ninjaLife = n;
        icemanLife = i;
        lionLife = l;
        wolfLife = w;
        dragonAttack = da;
        ninjaAttack = na;
        icemanAttack = ia;
        lionAttack = la;
        wolfAttack = wa;
    }
    virtual void printBornInfo(Warrior & currentWarrior){
        cout << setfill('0') << setw(3) << timeHourCount << setfill(' ');
        cout << ":" ;
        cout << setfill('0') << setw(2) << timeMinCount << setfill(' ');
        cout << " blue " << currentWarrior.name << " " << currentWarrior.No << " born" << endl;
    }
    virtual void printGoAheadInfo(Warrior & currentWarrior, int cityNo){
        cout << setfill('0') << setw(3) << timeHourCount << setfill(' ');
        cout << ":" ;
        cout << setfill('0') << setw(2) << timeMinCount << setfill(' ');
        cout << " blue" << currentWarrior.name << " " << currentWarrior.No << " marched to city " << cityNo 
        << " with " << currentWarrior.life << " elements and force "<< currentWarrior.attack<< endl;
    }
    virtual void printFinsih(){
    }
};

int Warrior::attackOnce(int i)
{
    if(waponOwned[i].No != 0)
        --waponOwned[i].durability;
    return waponOwned[i].attackPower;
}


//制造一个武士
int Tribe::tribeBornOnce(int i, int No, int listNum){
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
            return -1;
        }
        currentLife -= icemanLife;
        Iceman iceman;
        iceman.name = "iceman";
        iceman.No = No;
        iceman.life = icemanLife;
        iceman.attack = icemanAttack;
        iceman.pos = 0;
        iceman.waponNo = iceman.No % 3;
        if(No % 3 == 0){
            Sword sword(0, iceman.attack/5, 1);
            iceman.waponOwned.push_back(sword);
        } else if(No % 3 == 1){
            Bomb bomb(1, iceman.attack*2/5,1);
            iceman.waponOwned.push_back(bomb);
        } else if(No % 3 == 2){
            Arrow arrow(2, iceman.attack*3/10,2);
            iceman.waponOwned.push_back(arrow);
        }
        sort(iceman.waponOwned.begin(), iceman.waponOwned.end(), sortFun);
        icemanList.push_back(iceman);
        warriorList.push_back(iceman);
        printBornInfo(iceman);
        //iceman.printWarriorInfo(0);
    } else if(list[i] == "lion"){
        if(currentLife < lionLife){
            return -1;
        }
        currentLife -= lionLife;
        Lion lion;
        lion.name = "lion";
        lion.No = No;
        lion.life = lionLife;
        lion.attack = lionAttack;
        lion.pos = 0;
        lion.loyalty = currentLife;
        lion.waponNo = lion.No % 3;
        if(No % 3 == 0){
            Sword sword(0, lion.attack/5, 1);
            lion.waponOwned.push_back(sword);
        } else if(No % 3 == 1){
            Bomb bomb(1, lion.attack*2/5,1);
            lion.waponOwned.push_back(bomb);
        } else if(No % 3 == 2){
            Arrow arrow(2, lion.attack*3/10,2);
            lion.waponOwned.push_back(arrow);
        }
        sort(lion.waponOwned.begin(), lion.waponOwned.end(), sortFun);
        lionList.push_back(lion);
        warriorList.push_back(lion);
        printBornInfo(lion);
        //lion.printWarriorInfo(currentLife);
    } else if(list[i] == "wolf"){
        if(currentLife < wolfLife){
            return -1;
        }
        currentLife -= wolfLife;
        Wolf wolf;
        wolf.name = "wolf";
        wolf.No = No;
        wolf.life = wolfLife;
        wolf.attack = wolfAttack;
        wolf.pos = 0;
        wolfList.push_back(wolf);
        warriorList.push_back(wolf);
        printBornInfo(wolf);
    } else if(list[i] == "ninja"){
        if(currentLife < ninjaLife){
            return -1;
        }
        currentLife -= ninjaLife;
        Ninja ninja;
        ninja.name = "ninja";
        ninja.No = No;
        ninja.life = ninjaLife;
        ninja.attack = ninjaAttack;
        ninja.pos = 0;
        ninja.waponNo[0] = No%3;
        ninja.waponNo[1] = (No+1)%3;
        if(ninja.waponNo[0] == 0){
            Sword sword(0, ninja.attack/5, 1);
            ninja.waponOwned.push_back(sword);
        } else if(ninja.waponNo[0] == 1){
            Bomb bomb(1, ninja.attack*2/5,1);
            ninja.waponOwned.push_back(bomb);
        } else if(ninja.waponNo[0] == 2){
            Arrow arrow(2, ninja.attack*3/10,2);
            ninja.waponOwned.push_back(arrow);
        }
        if(ninja.waponNo[1] == 0){
            Sword sword(0, ninja.attack/5, 1);
            ninja.waponOwned.push_back(sword);
        } else if(ninja.waponNo[1] == 1){
            Bomb bomb(1, ninja.attack*2/5,1);
            ninja.waponOwned.push_back(bomb);
        } else if(ninja.waponNo[1] == 2){
            Arrow arrow(2, ninja.attack*3/10,2);
            ninja.waponOwned.push_back(arrow);
        }
        sort(ninja.waponOwned.begin(), ninja.waponOwned.end(), sortFun);
        ninjaList.push_back(ninja);
        warriorList.push_back(ninja);
        printBornInfo(ninja);
        //ninja.printWarriorInfo(0);
    } else if(list[i] == "dragon"){
        if(currentLife < dragonLife){
            return -1;
        }
        currentLife -= dragonLife;
        Dragon dragon;
        dragon.name = "dragon";
        dragon.No = No;
        dragon.life = dragonLife;
        dragon.attack = dragonAttack;
        dragon.pos = 0;
        dragon.waponNo = dragon.No % 3;
        if(No % 3 == 0){
            Sword sword(0, dragon.attack/5, 1);
            dragon.waponOwned.push_back(sword);
        } else if(No % 3 == 1){
            Bomb bomb(1, dragon.attack*2/5,1);
            dragon.waponOwned.push_back(bomb);
        } else if(No % 3 == 2){
            Arrow arrow(2, dragon.attack*3/10,2);
            dragon.waponOwned.push_back(arrow);
        }
        sort(dragon.waponOwned.begin(), dragon.waponOwned.end(), sortFun);
        dragon.morale = (double)currentLife / (double)dragonLife;
        dragonList.push_back(dragon);
        warriorList.push_back(dragon);
        printBornInfo(dragon);
        //dragon.printWarriorInfo(0);
    } else{
        return -1;
    }
    return 0;
}

int Tribe::tribeFightOnce(Warrior & currentWarrior, int waponNo, Warrior & antiWarrior){
    int att = currentWarrior.attackOnce(waponNo);
    int restLife = antiWarrior.attackedOnce(att);
    if(restLife <= 0){
        vector<Warrior>::iterator it;
    }

}

//设定初始生命值等参数，开始运行
void runBegin(int totalLife, int cityNum, int loyaltyMinus, int totalTime, int dragonLife, int ninjaLife, int icemanLife, int lionLife, int wolfLife,int dragonAttack,int ninjaAttack, int icemanAttack, int lionAttack, int wolfAttack){
    //设置初始参数
    RedTribe redTribe(totalLife, cityNum, loyaltyMinus, totalTime, 
    dragonLife, ninjaLife, icemanLife, lionLife, wolfLife,
    dragonAttack,ninjaAttack,icemanAttack,lionAttack,wolfAttack);

    BlueTribe blueTribe(totalLife, cityNum, loyaltyMinus, totalTime, 
    dragonLife, ninjaLife, icemanLife, lionLife, wolfLife,
    dragonAttack,ninjaAttack,icemanAttack,lionAttack,wolfAttack);
    
    int i=0,j=0,k=1;//i for red, j for blue,k for No
    //第一次运行武士出生
    int redJudge = redTribe.tribeBornOnce(i,k,0);
    int blueJudge = blueTribe.tribeBornOnce(j,k,0);
    timeMinCount += 5;
    ++k;

    while(redJudge != -1 || blueJudge != -1){
        if(timeMinCount == 0)//每个小时的第0分， 双方的司令部中各有一个武士降生
        {
            if(redJudge != -1)
                redJudge = redTribe.tribeBornOnce(i,k,0);
            if(blueJudge != -1)
                blueJudge = blueTribe.tribeBornOnce(j,k,0);
            ++k;
        }
        if(timeMinCount == 5)//在每个小时的第5分，该逃跑的lion就在这一时刻逃跑了
        {

        }
        if(timeMinCount == 10)//在每个小时的第10分：所有的武士朝敌人司令部方向前进一步。即从己方司令部走到相邻城市，或从一个城市走到下一个城市。或从和敌军司令部相邻的城市到达敌军司令部
        {

        }
        if(timeMinCount == 35)//在每个小时的第35分：在有wolf及其敌人的城市，wolf要抢夺对方的武器
        {

        }
        if(timeMinCount == 40)//在每个小时的第40分：在有两个武士的城市，会发生战斗
        {
            
        }
        if(timeMinCount == 50)//在每个小时的第50分，司令部报告它拥有的生命元数量
        {
            
        }
        if(timeMinCount == 55)//在每个小时的第55分，每个武士报告其拥有的武器情况
        {
            
        }
        
        //时间计数
        timeMinCount += 5;
        if(timeMinCount == 60)
        {
            timeHourCount += 1;
            timeMinCount = 0;
        }
        //如果时间耗尽，停止
        if(timeMinCount + timeHourCount * 60 > totalTime)
            break;
    }
    

}

//读取数据，传递参数
void readInput(){
    int caseNum;
    cin >> caseNum;
    int allTotalLife[caseNum];
    int cityNum[caseNum];
    int loyaltyMinus[caseNum];
    int totalTime[caseNum];
    int allLife[caseNum][MaxWarrior];
    int allAttack[caseNum][MaxWarrior];
    for(int i = 0; i < caseNum; ++i){
        cin >> allTotalLife[i] >> cityNum[i] >> loyaltyMinus[i] >> totalTime[i];
        for(int j = 0; j < MaxWarrior; ++j){
            cin >> allLife[i][j];
        }
        for(int j = 0; j < MaxWarrior; ++j){
            cin >> allAttack[i][j];
        }
    }
    for(int i = 0; i < caseNum; ++i){
        cout << "Case:" << i + 1 << endl;
        runBegin(allTotalLife[i], cityNum[i], loyaltyMinus[i] , totalTime[i] , 
        allLife[i][0], allLife[i][1], allLife[i][2], allLife[i][3], allLife[i][4],
        allAttack[i][0],allAttack[i][1],allAttack[i][2],allAttack[i][3],allAttack[i][4]);
        timeHourCount = 0;
        timeMinCount = 0;
    }
}

int main(){
    freopen("datapub.in","r",stdin);
    freopen("out.out","w",stdout);
    readInput();
    return 0;
}