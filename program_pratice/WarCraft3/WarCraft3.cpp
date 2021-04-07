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

void printCurrentTime(){
    cout << setfill('0') << setw(3) << timeHourCount << setfill(' ');
    cout << ":" ;
    cout << setfill('0') << setw(2) << timeMinCount << setfill(' ');
}

//武器类
class Wapon{
public:
    int No;
    int attackPower;
    int durability;
    int attackSelf;
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
    int posChanged;
    int loyalty; //for lion
    Warrior(){posChanged = 0;}
    vector<Wapon> waponOwned;
    virtual void printWarriorInfo(double n){};
    virtual void goAhead(){pos++;};
    virtual void wolfSnatchWapon(Warrior & antiWarrior, int currentTribe){};
    int attackOnce(int i);//返回武器的攻击力
    int hurtedOnce(int att);//返回剩余生命值
    void snatchWapon(Warrior & antiWarrior);
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
    virtual void goAhead(){
        pos++;
        life = life - (life / 10);
    }
};

class Lion:public Warrior{
public:
    void printWarriorInfo(double n){
        cout << "Its loyalty is " << loyalty << endl;
    }
    void printLionRun(string redOrBlue,Warrior & currentWarrior){
    }
};

class Wolf:public Warrior{
public:
    virtual void wolfSnatchWapon(Warrior & antiWarrior, int currentTribe){
        string twoTribe[] = {"red", "blue"};
        if(antiWarrior.name == "wolf")
            return;
        int minWaponNo = antiWarrior.waponOwned.end()->No;
        if(minWaponNo != 2)//如果对方最小的武器不是arrow，直接抢即可
        {
            
            int tmpCount = 0;
            for(int i = antiWarrior.waponOwned.size() - 1; i >= 0 ; --i){
                if(antiWarrior.waponOwned[i].No > minWaponNo)
                    break;
                if(waponOwned.size() > 10)
                    break;
                Wapon tmp(antiWarrior.waponOwned[i].No, antiWarrior.waponOwned[i].attackPower, waponOwned[i].durability);
                waponOwned.push_back(tmp);
                ++tmpCount;
                antiWarrior.waponOwned.pop_back();
            }
            if(minWaponNo == 0){
                printCurrentTime();
                cout << " "  << twoTribe[currentTribe] << " wolf " <<  No << " took " << tmpCount << " sword from " << twoTribe[1-currentTribe] << " " 
                << antiWarrior.name << " "<< antiWarrior.No << " in city " << pos << endl;
            }
            if(minWaponNo == 1){
                printCurrentTime();
                cout << " "  << twoTribe[currentTribe] << " wolf " <<  No << " took " << tmpCount << " bomb from " << twoTribe[1-currentTribe] << " " 
                << antiWarrior.name << " "<< antiWarrior.No << " in city " << pos << endl;             
            }
        }
        else//如果对方最小的是arrow，先抢没用过的，倒过来抢
        {
            int tmpCount = 0;
            for(int i = 0; i < antiWarrior.waponOwned.size(); ++i){
                if(waponOwned.size() > 10)
                    break;
                Wapon tmp(antiWarrior.waponOwned[i].No, antiWarrior.waponOwned[i].attackPower, waponOwned[i].durability);
                waponOwned.push_back(tmp);
                ++tmpCount;
                antiWarrior.waponOwned.erase(antiWarrior.waponOwned.begin());
            }
            cout << " "  << twoTribe[currentTribe] << " wolf " <<  No << " took " << tmpCount << " arrow from " << twoTribe[1-currentTribe] << " " 
            << antiWarrior.name << " "<< antiWarrior.No << " in city " << pos << endl; 
            
        }
        //对抢到的武器进行排序
        sort(waponOwned.begin(), waponOwned.end(), sortFun);
    }
};

//红蓝两方的类
class Tribe{
public:
    int currentLife;
    int dragonLife, ninjaLife, icemanLife, lionLife, wolfLife;
    int dragonAttack, ninjaAttack, icemanAttack, lionAttack, wolfAttack;
    int cityNum,loyaltyMinus,totalTime;
    int *cityArray;//代表城市里是否有己方人员
    vector<Dragon> dragonList;
    vector<Ninja> ninjaList;
    vector<Iceman> icemanList;
    vector<Lion> lionList;
    vector<Wolf> wolfList;
    vector<Warrior> warriorList;
    Tribe(){}
    ~Tribe(){}
    virtual void printBornInfo(Warrior & currentWarrior){};
    virtual void printGoAheadInfo(Warrior & currentWarrior){};
    virtual void printTribeInfo(){};
    virtual void printAllWarriorInfo(){};
    virtual void printFinsih(){};
    virtual int tribeBornOnce(int i, int No){return 0;};//listNum =0, red; listNum =1, blue
    void lionRunAway(Tribe & RedTribe, Tribe & BlueTribe);
    void wolfSnatchWapon(Tribe & redTribe, Tribe & blueTribe);
    void allFightOnce(Tribe & redTribe, Tribe & blueTribe);
    void allGoAhead(Tribe & redTribe, Tribe & blueTribe);
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
        cityArray = new int[cityNum + 2]();
    }
    ~RedTribe(){delete[] cityArray;}
    virtual int tribeBornOnce(int i, int No);
    virtual void printBornInfo(Warrior & currentWarrior){
        printCurrentTime();
        cout << " red " << currentWarrior.name << " " << currentWarrior.No << " born" << endl;
    }
    virtual void printGoAheadInfo(Warrior & currentWarrior){
        printCurrentTime();
        cout << " red " << currentWarrior.name << " " << currentWarrior.No << " marched to city " << currentWarrior.pos 
        << " with " << currentWarrior.life << " elements and force "<< currentWarrior.attack<< endl;
    }
    virtual void printTribeInfo(){
        printCurrentTime();
        cout << " " << currentLife << " elements in red headquarter" << endl;
    }
    virtual void printAllWarriorInfo(){
        for(int k = 0; k < cityNum + 2; ++k){
            if(cityArray[k] == 1){
                int i = 0;
                for(i = 0; i < warriorList.size(); ++i){
                    //cout << warriorList[i].name << endl;
                    if(warriorList[i].pos == k)
                        break;
                }
                int swNum=0,boNum=0,arNum=0;
                for(int j = 0; j < warriorList[i].waponOwned.size(); ++j){
                    if(warriorList[i].waponOwned[j].No == 0)
                        ++swNum;
                    else if(warriorList[i].waponOwned[j].No == 1)
                        ++boNum;
                    else if(warriorList[i].waponOwned[j].No == 2)
                        ++arNum;
                }
                printCurrentTime();
                cout << " " << "red " <<  warriorList[i].name << " " << warriorList[i].No
                << " has " << swNum << " sword " << boNum << " bomb " << arNum << " arrow and " 
                << warriorList[i].life << " elements" << endl;
            }
        }
    }
    virtual void printFinsih(){
        printCurrentTime();
        cout << " red headquarter was taken" <<endl;
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
        cityArray = new int[cityNum + 2]();
    }
    ~BlueTribe(){delete[] cityArray;}
    virtual int tribeBornOnce(int i, int No);
    virtual void printBornInfo(Warrior & currentWarrior){
        printCurrentTime();
        cout << " blue " << currentWarrior.name << " " << currentWarrior.No << " born" << endl;
    }
    virtual void printGoAheadInfo(Warrior & currentWarrior){
        printCurrentTime();
        cout << " blue " << currentWarrior.name << " " << currentWarrior.No << " marched to city " << currentWarrior.pos
        << " with " << currentWarrior.life << " elements and force "<< currentWarrior.attack<< endl;
    }
    virtual void printTribeInfo(){
        printCurrentTime();
        cout << " " << currentLife << " elements in blue headquarter" << endl;
    }
    virtual void printAllWarriorInfo(){
        for(int k = 0; k < cityNum + 2; ++k){
            if(cityArray[k] == 1){
                int i = 0;
                for(i = 0; i < warriorList.size(); ++i){
                    if(warriorList[i].pos == k)
                        break;
                }
                //cout << warriorList[i].name << endl;
                int swNum=0,boNum=0,arNum=0;
                for(int j = 0; j < warriorList[i].waponOwned.size(); ++j){
                    if(warriorList[i].waponOwned[j].No == 0)
                        ++swNum;
                    else if(warriorList[i].waponOwned[j].No == 1)
                        ++boNum;
                    else if(warriorList[i].waponOwned[j].No == 2)
                        ++arNum;
                }
                printCurrentTime();
                cout << " " << "blue " <<  warriorList[i].name << " " << warriorList[i].No
                << " has " << swNum << " sword " << boNum << " bomb " << arNum << " arrow and " 
                << warriorList[i].life << " elements" << endl;
            }
        }
    }
    virtual void printFinsih(){
        printCurrentTime();
        cout << " blue headquarter was taken" <<endl;
    }
};


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
    int redJudge = redTribe.tribeBornOnce(i,k);
    int blueJudge = blueTribe.tribeBornOnce(j,k);
    timeMinCount += 5;
    ++k; ++i; ++j;

    while(1){
        if(timeMinCount == 0)//每个小时的第0分， 双方的司令部中各有一个武士降生
        {
            if(redJudge != -1)
                redJudge = redTribe.tribeBornOnce(i%5,k);
            if(blueJudge != -1)
                blueJudge = blueTribe.tribeBornOnce(j%5,k);
            ++k; ++i; ++j;
        }
        if(timeMinCount == 5)//在每个小时的第5分，该逃跑的lion就在这一时刻逃跑了
        {
            redTribe.lionRunAway(redTribe,blueTribe);
        }
        if(timeMinCount == 10)//在每个小时的第10分：所有的武士朝敌人司令部方向前进一步。即从己方司令部走到相邻城市，或从一个城市走到下一个城市。或从和敌军司令部相邻的城市到达敌军司令部
        {
            redTribe.allGoAhead(redTribe,blueTribe);
            if(redTribe.cityArray[cityNum + 1] == 1)
                break;
            if(blueTribe.cityArray[0] == 1)
                break;
        }
        if(timeMinCount == 35)//在每个小时的第35分：在有wolf及其敌人的城市，wolf要抢夺对方的武器
        {
            redTribe.wolfSnatchWapon(redTribe,blueTribe);
        }
        if(timeMinCount == 40)//在每个小时的第40分：在有两个武士的城市，会发生战斗
        {
            redTribe.allFightOnce(redTribe,blueTribe);
        }
        if(timeMinCount == 50)//在每个小时的第50分，司令部报告它拥有的生命元数量
        {
            redTribe.printTribeInfo();
            blueTribe.printTribeInfo();
        }
        if(timeMinCount == 55)//在每个小时的第55分，每个武士报告其拥有的武器情况
        {
            redTribe.printAllWarriorInfo();
            blueTribe.printAllWarriorInfo();
        }
        //时间计数
        timeMinCount += 5;
        if(timeMinCount == 60)
        {
            timeHourCount += 1;
            timeMinCount = 0;
        }
        //如果时间耗尽，停止
        if(timeMinCount + timeHourCount * 60 > totalTime){
            break;
        }
            
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


int Warrior::attackOnce(int i)
{
    int att = waponOwned[i].attackPower;
    if(waponOwned[i].No == 1){
        life -= waponOwned[i].attackSelf;
    }
    waponOwned[i].usedOnce();
    if(waponOwned[i].durability == 0){
        waponOwned.erase(waponOwned.begin() + i);
    }
    return att;
}

int Warrior::hurtedOnce(int att){
    life -= att; 
    return life;
}

void Warrior::snatchWapon(Warrior & antiWarrior){
    int minWaponNo = antiWarrior.waponOwned.end()->No;
    if(minWaponNo < 2){
        //snatch sword and bomb
        for(int i = antiWarrior.waponOwned.size() - 1; i >= 0 ; --i){
            if(antiWarrior.waponOwned.end()->No == 2)
                break;
            if(waponOwned.size() > 10)
                break;
            Wapon tmp(antiWarrior.waponOwned[i].No, antiWarrior.waponOwned[i].attackPower, waponOwned[i].durability);
            waponOwned.push_back(tmp);
            antiWarrior.waponOwned.pop_back();
        }
        //snatch arrow
        for(int i = 0; i < antiWarrior.waponOwned.size(); ++i){
            if(waponOwned.size() > 10)
                break;
            Wapon tmp(antiWarrior.waponOwned[i].No, antiWarrior.waponOwned[i].attackPower, waponOwned[i].durability);
            waponOwned.push_back(tmp);
            antiWarrior.waponOwned.erase(antiWarrior.waponOwned.begin());
        }
    }
    else if(minWaponNo == 2){
        //snatch arrow
        for(int i = 0; i < antiWarrior.waponOwned.size(); ++i){
            if(waponOwned.size() > 10)
                break;
            Wapon tmp(antiWarrior.waponOwned[i].No, antiWarrior.waponOwned[i].attackPower, waponOwned[i].durability);
            waponOwned.push_back(tmp);
            antiWarrior.waponOwned.erase(antiWarrior.waponOwned.begin());
        }
    }
}

//制造一个武士
int RedTribe::tribeBornOnce(int i, int No){
    //判断怪物类型进行建造
    if(redWarriorList[i] == "iceman"){
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
        cityArray[0] = 1;
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
    } else if(redWarriorList[i] == "lion"){
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
        cityArray[0] = 1;
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
        lion.printWarriorInfo(0);
        //lion.printWarriorInfo(currentLife);
    } else if(redWarriorList[i] == "wolf"){
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
        cityArray[0] = 1;
        wolfList.push_back(wolf);
        warriorList.push_back(wolf);
        printBornInfo(wolf);
    } else if(redWarriorList[i] == "ninja"){
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
        cityArray[0] = 1;
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
    } else if(redWarriorList[i] == "dragon"){
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
        cityArray[0] = 1;
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

int BlueTribe::tribeBornOnce(int i, int No){
    //判断怪物类型进行建造
    if(blueWarriorList[i] == "iceman"){
        if(currentLife < icemanLife){
            return -1;
        }
        currentLife -= icemanLife;
        Iceman iceman;
        iceman.name = "iceman";
        iceman.No = No;
        iceman.life = icemanLife;
        iceman.attack = icemanAttack;
        iceman.pos = cityNum + 1;
        cityArray[cityNum + 1] = 1;
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
    } else if(blueWarriorList[i] == "lion"){
        if(currentLife < lionLife){
            return -1;
        }
        currentLife -= lionLife;
        Lion lion;
        lion.name = "lion";
        lion.No = No;
        lion.life = lionLife;
        lion.attack = lionAttack;
        lion.pos = cityNum + 1;
        cityArray[cityNum + 1] = 1;
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
        lion.printWarriorInfo(0);
        //lion.printWarriorInfo(currentLife);
    } else if(blueWarriorList[i] == "wolf"){
        if(currentLife < wolfLife){
            return -1;
        }
        currentLife -= wolfLife;
        Wolf wolf;
        wolf.name = "wolf";
        wolf.No = No;
        wolf.life = wolfLife;
        wolf.attack = wolfAttack;
        wolf.pos = cityNum + 1;
        cityArray[cityNum + 1] = 1;
        wolfList.push_back(wolf);
        warriorList.push_back(wolf);
        printBornInfo(wolf);
    } else if(blueWarriorList[i] == "ninja"){
        if(currentLife < ninjaLife){
            return -1;
        }
        currentLife -= ninjaLife;
        Ninja ninja;
        ninja.name = "ninja";
        ninja.No = No;
        ninja.life = ninjaLife;
        ninja.attack = ninjaAttack;
        ninja.pos = cityNum + 1;
        cityArray[cityNum + 1] = 1;
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
    } else if(blueWarriorList[i] == "dragon"){
        if(currentLife < dragonLife){
            return -1;
        }
        currentLife -= dragonLife;
        Dragon dragon;
        dragon.name = "dragon";
        dragon.No = No;
        dragon.life = dragonLife;
        dragon.attack = dragonAttack;
        dragon.pos = cityNum + 1;
        cityArray[cityNum + 1] = 1;
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

void Tribe::lionRunAway(Tribe & redTribe, Tribe & blueTribe){
    for(int i = 0; i < cityNum + 2; ++i){
        if(redTribe.cityArray[i] == 1){
            int j = 0;
            for(j = 0; j < redTribe.warriorList.size(); ++j){
                if(redTribe.warriorList[j].pos == i)
                    break;
            }
            if(redTribe.warriorList[j].name == "lion" && redTribe.warriorList[j].loyalty <= 0){
                    printCurrentTime();
                    cout << " " << "red" << " lion " << redTribe.warriorList[j].No << " ran away" << endl;
                    redTribe.warriorList.erase(redTribe.warriorList.begin() + j);
                    redTribe.cityArray[i] = 0;
            }
        }
        if(blueTribe.cityArray[i] == 1 && i != 0){
            int j = 0;
            for(j = 0; j < blueTribe.warriorList.size(); ++j){
                if(blueTribe.warriorList[j].pos == i)
                    break;
            }
            if(blueTribe.warriorList[j].name == "lion" && blueTribe.warriorList[j].loyalty <= 0){
                    printCurrentTime();
                    cout << " " << "blue" << " lion " << blueTribe.warriorList[j].No << " ran away" << endl;
                    blueTribe.warriorList.erase(blueTribe.warriorList.begin() + j);
                    blueTribe.cityArray[i] = 0;
            }
        }
    }
}

void Tribe::wolfSnatchWapon(Tribe & redTribe, Tribe & blueTribe){
    for(int i = 1; i < cityNum + 1; ++i){
        if(redTribe.cityArray[i] == 1 && blueTribe.cityArray[i] == 1){
            int j = 0;//for red
            for(j = 0; j < redTribe.warriorList.size(); ++j){
                if(redTribe.warriorList[j].pos == i)
                    break;
            }
            int k = 0;// for blue
            for(k = 0; k < blueTribe.warriorList.size(); ++k){
                if(blueTribe.warriorList[k].pos == i)
                    break;
            }
            if(redTribe.warriorList[j].name == "wolf" && blueTribe.warriorList[k].name != "wolf"){
                    redTribe.warriorList[j].wolfSnatchWapon(blueTribe.warriorList[k],0);
            }
            if(redTribe.warriorList[j].name != "wolf" && blueTribe.warriorList[k].name == "wolf"){
                    blueTribe.warriorList[k].wolfSnatchWapon(redTribe.warriorList[j],1);
            }
        }
    }
}

void Tribe::allGoAhead(Tribe & redTribe, Tribe & blueTribe){
    for(int i = 0; i < redTribe.warriorList.size(); ++i)
        redTribe.warriorList[i].posChanged = 0;
    for(int i = 0; i < blueTribe.warriorList.size(); ++i)
        blueTribe.warriorList[i].posChanged = 0;

    for(int i = 0; i < cityNum + 2; ++i){
        if(redTribe.cityArray[i] == 1){
            int j = 0;
            for(j = 0; j < redTribe.warriorList.size(); ++j){
                if(redTribe.warriorList[j].pos == i)
                    break;
            }
            if(redTribe.warriorList[j].pos == cityNum + 1)//如果已到达敌方司令部
                break;
            if(redTribe.warriorList[j].posChanged == 1)
                continue;
            if(redTribe.warriorList[j].name == "lion")
                redTribe.warriorList[j].loyalty -= redTribe.loyaltyMinus;
            if(redTribe.warriorList[j].name == "iceman")
                redTribe.warriorList[j].life = redTribe.warriorList[j].life - (redTribe.warriorList[j].life / 10);
            redTribe.cityArray[redTribe.warriorList[j].pos] = 0;
            redTribe.warriorList[j].pos++;
            redTribe.cityArray[redTribe.warriorList[j].pos] = 1;
            redTribe.warriorList[j].posChanged = 1;
            if(redTribe.warriorList[j].pos != cityNum + 1)
                redTribe.printGoAheadInfo(redTribe.warriorList[j]);
            if(redTribe.warriorList[j].pos == cityNum + 1)
                blueTribe.printFinsih();
        }
        if(blueTribe.cityArray[i] == 1){
            int j = 0;
            for(j = 0; j < blueTribe.warriorList.size(); ++j){
                if(blueTribe.warriorList[j].pos == i)
                    break;
            }
            if(blueTribe.warriorList[j].pos == 0)//如果已到达敌方司令部
                break;
            if(blueTribe.warriorList[j].posChanged == 1)
                continue;
            if(blueTribe.warriorList[j].name == "lion")
                blueTribe.warriorList[j].loyalty -= blueTribe.loyaltyMinus;
            if(blueTribe.warriorList[j].name == "iceman")
                blueTribe.warriorList[j].life = blueTribe.warriorList[j].life - (blueTribe.warriorList[j].life / 10);
            blueTribe.cityArray[blueTribe.warriorList[j].pos] = 0;
            blueTribe.warriorList[j].pos--;
            blueTribe.cityArray[blueTribe.warriorList[j].pos] = 1;
            blueTribe.warriorList[j].posChanged = 1;
            if(blueTribe.warriorList[j].pos != 0)
                blueTribe.printGoAheadInfo(blueTribe.warriorList[j]);
            if(blueTribe.warriorList[j].pos == 0)
                redTribe.printFinsih();
        }
    }
}

void Tribe::allFightOnce(Tribe & redTribe, Tribe & blueTribe){
    for(int i=0; i < cityNum + 2; ++i){
        if(redTribe.cityArray[i] == 1 && blueTribe.cityArray[i] == 1){
            int j = 0;//for red
            for(j = 0; j < redTribe.warriorList.size(); ++j){
                if(redTribe.warriorList[j].pos == i)
                    break;
            }
            int k = 0;// for blue
            for(k = 0; k < blueTribe.warriorList.size(); ++k){
                if(blueTribe.warriorList[k].pos == i)
                    break;
            }
            //redTribe.warriorList[j] vs blueTribe.warriorList[k]
            Warrior & redWarrior = redTribe.warriorList[j];
            Warrior & blueWarrior = blueTribe.warriorList[k];
            int redAlive = 1, blueAlive = 1;
            int redWaponCount = 0, blueWaponCount = 0;
            int attackJudge = 0;//check whether all wapon attack is 0
            int redWaopnSize = redWarrior.waponOwned.size();
            int blueWaopnSize = blueWarrior.waponOwned.size();
            if(i % 2 == 1){//奇数,red先
                //fight begin
                while(redAlive && blueAlive){
                    //if both have wapon
                    while(redWarrior.waponOwned.size() && blueWarrior.waponOwned.size() && redAlive && blueAlive){
                        //use waponOwned[redWarrior.waponOwned.size() - 1 - redWaponCount%redWarrior.waponOwned.size()]
                        int redAtt = redWarrior.attackOnce(redWarrior.waponOwned[redWarrior.waponOwned.size() - 1 - redWaponCount%(redWarrior.waponOwned.size())].No);
                        blueWarrior.hurtedOnce(redAtt);
                        int blueAtt = blueWarrior.attackOnce(blueWarrior.waponOwned[blueWarrior.waponOwned.size() - 1 - blueWaponCount%(blueWarrior.waponOwned.size())].No);
                        redWarrior.hurtedOnce(blueAtt);
                        // judge whether one die
                        if(redWarrior.life <= 0)
                            redAlive = 0;
                        if(blueWarrior.life <= 0)
                            blueAlive = 0;
                        //if no wapon broken, count++, else count remain unchanged
                        if(redWarrior.waponOwned.size() == redWaopnSize)
                            redWaponCount++;
                        else
                            redWaopnSize = redWarrior.waponOwned.size();
                        if(blueWarrior.waponOwned.size() == blueWaopnSize)
                            blueWaponCount++;
                        else
                            blueWaopnSize = blueWarrior.waponOwned.size();
                        //check whether all wapon attack is 0
                        for(int m = 0; m < redWarrior.waponOwned.size(); ++m){
                            attackJudge = 0;
                            if(redWarrior.waponOwned[m].attackPower != 0){
                                attackJudge = 1;
                                break;
                            }
                        }
                        for(int m = 0; m < blueWarrior.waponOwned.size(); ++m){
                            attackJudge = 0;
                            if(blueWarrior.waponOwned[m].attackPower != 0){
                                attackJudge = 1;
                                break;
                            }
                        }
                        if(attackJudge == 0)
                            break;
                    }
                    //if only red has wapon
                    while(redWarrior.waponOwned.size() && !blueWarrior.waponOwned.size() && redAlive && blueAlive){
                        int redAtt = redWarrior.attackOnce(redWarrior.waponOwned[redWarrior.waponOwned.size() - 1 - redWaponCount%(redWarrior.waponOwned.size())].No);
                        blueWarrior.hurtedOnce(redAtt);
                        if(redWarrior.life <= 0)
                            redAlive = 0;
                        if(blueWarrior.life <= 0)
                            blueAlive = 0;
                        if(redWarrior.waponOwned.size() == redWaopnSize)
                            redWaponCount++;
                        else
                            redWaopnSize = redWarrior.waponOwned.size();
                        //check whether all wapon attack is 0
                        for(int m = 0; m < redWarrior.waponOwned.size(); ++m){
                            attackJudge = 0;
                            if(redWarrior.waponOwned[m].attackPower != 0){
                                attackJudge = 1;
                                break;
                            }
                        }
                        if(attackJudge == 0)
                            break;
                    }
                    // if only blue have wapon
                    while(!redWarrior.waponOwned.size() && blueWarrior.waponOwned.size() && redAlive && blueAlive){
                        int blueAtt = blueWarrior.attackOnce(blueWarrior.waponOwned[blueWarrior.waponOwned.size() - 1 - blueWaponCount%(blueWarrior.waponOwned.size())].No);
                        redWarrior.hurtedOnce(blueAtt);
                        if(redWarrior.life <= 0)
                            redAlive = 0;
                        if(blueWarrior.life <= 0)
                            blueAlive = 0;
                        if(blueWarrior.waponOwned.size() == blueWaopnSize)
                            blueWaponCount++;
                        else
                            blueWaopnSize = blueWarrior.waponOwned.size();
                        //check whether all wapon attack is 0
                        for(int m = 0; m < blueWarrior.waponOwned.size(); ++m){
                            attackJudge = 0;
                            if(blueWarrior.waponOwned[m].attackPower != 0){
                                attackJudge = 1;
                                break;
                            }
                        }
                        if(attackJudge == 0)
                            break;
                    }
                    //if no wapon
                    if(redWarrior.waponOwned.size() == 0 && blueWarrior.waponOwned.size() == 0)
                        break;
                    if(attackJudge == 0)
                        break;
                }
                //fight end
            }
            if(i % 2 == 0){//偶数,blue先
                while(redAlive && blueAlive){
                    //if both have wapon
                    while(redWarrior.waponOwned.size() && blueWarrior.waponOwned.size() && redAlive && blueAlive){
                        //use waponOwned[redWarrior.waponOwned.size() - 1 - redWaponCount%redWarrior.waponOwned.size()]
                        int blueAtt = blueWarrior.attackOnce(blueWarrior.waponOwned[blueWarrior.waponOwned.size() - 1 - blueWaponCount%(blueWarrior.waponOwned.size())].No);
                        redWarrior.hurtedOnce(blueAtt);
                        int redAtt = redWarrior.attackOnce(redWarrior.waponOwned[redWarrior.waponOwned.size() - 1 - redWaponCount%(redWarrior.waponOwned.size())].No);
                        blueWarrior.hurtedOnce(redAtt);
                        // judge whether one die
                        if(redWarrior.life <= 0)
                            redAlive = 0;
                        if(blueWarrior.life <= 0)
                            blueAlive = 0;
                        //if no wapon broken, count++, else count remain unchanged
                        if(redWarrior.waponOwned.size() == redWaopnSize)
                            redWaponCount++;
                        else
                            redWaopnSize = redWarrior.waponOwned.size();
                        if(blueWarrior.waponOwned.size() == blueWaopnSize)
                            blueWaponCount++;
                        else
                            blueWaopnSize = blueWarrior.waponOwned.size();
                        //check whether all wapon attack is 0
                        for(int m = 0; m < redWarrior.waponOwned.size(); ++m){
                            attackJudge = 0;
                            if(redWarrior.waponOwned[m].attackPower != 0){
                                attackJudge = 1;
                                break;
                            }
                        }
                        for(int m = 0; m < blueWarrior.waponOwned.size(); ++m){
                            attackJudge = 0;
                            if(blueWarrior.waponOwned[m].attackPower != 0){
                                attackJudge = 1;
                                break;
                            }
                        }
                        if(attackJudge == 0)
                            break;
                    }
                    //if only red has wapon
                    while(redWarrior.waponOwned.size() && !blueWarrior.waponOwned.size() && redAlive && blueAlive){
                        int redAtt = redWarrior.attackOnce(redWarrior.waponOwned[redWarrior.waponOwned.size() - 1 - redWaponCount%(redWarrior.waponOwned.size())].No);
                        blueWarrior.hurtedOnce(redAtt);
                        if(redWarrior.life <= 0)
                            redAlive = 0;
                        if(blueWarrior.life <= 0)
                            blueAlive = 0;
                        if(redWarrior.waponOwned.size() == redWaopnSize)
                            redWaponCount++;
                        else
                            redWaopnSize = redWarrior.waponOwned.size();
                        //check whether all wapon attack is 0
                        for(int m = 0; m < redWarrior.waponOwned.size(); ++m){
                            attackJudge = 0;
                            if(redWarrior.waponOwned[m].attackPower != 0){
                                attackJudge = 1;
                                break;
                            }
                        }
                        if(attackJudge == 0)
                            break;
                    }
                    // if only blue have wapon
                    while(!redWarrior.waponOwned.size() && blueWarrior.waponOwned.size() && redAlive && blueAlive){
                        int blueAtt = blueWarrior.attackOnce(blueWarrior.waponOwned[blueWarrior.waponOwned.size() - 1 - blueWaponCount%(blueWarrior.waponOwned.size())].No);
                        redWarrior.hurtedOnce(blueAtt);
                        if(redWarrior.life <= 0)
                            redAlive = 0;
                        if(blueWarrior.life <= 0)
                            blueAlive = 0;
                        if(blueWarrior.waponOwned.size() == blueWaopnSize)
                            blueWaponCount++;
                        else
                            blueWaopnSize = blueWarrior.waponOwned.size();
                        //check whether all wapon attack is 0
                        for(int m = 0; m < blueWarrior.waponOwned.size(); ++m){
                            attackJudge = 0;
                            if(blueWarrior.waponOwned[m].attackPower != 0){
                                attackJudge = 1;
                                break;
                            }
                        }
                        if(attackJudge == 0)
                            break;
                    }
                    //if no wapon
                    if(redWarrior.waponOwned.size() == 0 && blueWarrior.waponOwned.size() == 0)
                        break;
                    if(attackJudge == 0)
                        break;
                }
            }
            //judge outcome
            if(redAlive == 1 && blueAlive == 1){//000:40 both red iceman 1 and blue lion 12 were alive in city 2
                printCurrentTime();
                cout << " both red " << redWarrior.name << " " << redWarrior.No 
                << " and blue " << blueWarrior.name << " " << blueWarrior.No 
                << " were alive in city " << i << endl;
                if(redWarrior.name == "dragon"){
                    printCurrentTime();
                    cout << " red dragon " << redWarrior.No << " yelled in city " << redWarrior.pos << endl;
                }
                if(blueWarrior.name == "dragon"){
                    printCurrentTime();
                    cout << " blue dragon " << blueWarrior.No << " yelled in city " << blueWarrior.pos << endl;
                }
            }
            else if(redAlive == 0 && blueAlive == 0){//000:40 both red iceman 1 and blue lion 12 died in city 2
                printCurrentTime();
                cout << " both red " << redWarrior.name << " " << redWarrior.No 
                << " and blue " << blueWarrior.name << " " << blueWarrior.No 
                << " died in city " << i << endl;
                redTribe.warriorList.erase(redTribe.warriorList.begin() + j);
                blueTribe.warriorList.erase(blueTribe.warriorList.begin() + k);
            }
            else if(redAlive ==1 && blueAlive == 0){//000:40 red iceman 1 killed blue lion 12 in city 2 remaining 20 elements
                printCurrentTime();
                cout << " red " << redWarrior.name << " " << redWarrior.No 
                << " killed blue " << blueWarrior.name << " " << blueWarrior.No 
                << " in city " << i << " remaining " << redWarrior.life << " elements" << endl;
                if(redWarrior.name == "dragon"){
                    printCurrentTime();
                    cout << " red dragon " << redWarrior.No << " yelled in city " << redWarrior.pos << endl;
                }
                //red snatch blue wapon
                redWarrior.snatchWapon(blueWarrior);
                blueTribe.warriorList.erase(blueTribe.warriorList.begin() + k);
            }
            else if(redAlive == 0 && blueAlive == 1){
                printCurrentTime();
                cout << " blue " << blueWarrior.name << " " << blueWarrior.No 
                << " killed red " << redWarrior.name << " " << redWarrior.No 
                << " in city " << i << " remaining " << blueWarrior.life << " elements" << endl;
                if(blueWarrior.name == "dragon"){
                    printCurrentTime();
                    cout << " blue dragon " << blueWarrior.No << " yelled in city " << blueWarrior.pos << endl;
                }
                //blue snatch red wapon
                blueWarrior.snatchWapon(redWarrior);
                redTribe.warriorList.erase(redTribe.warriorList.begin() + j);
            }
        }
    }
}