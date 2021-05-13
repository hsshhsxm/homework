#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

//input
int M,N,R,K,T;
int dragonAttack, ninjaAttack, icemanAttack, lionAttack, wolfAttack;
int dragonLife, ninjaLife, icemanLife, lionLife, wolfLife;
/*
每个司令部一开始都有M个生命元( 1 <= M <= 10000)
两个司令部之间一共有N个城市( 1 <= N <= 20 )
arrow的攻击力是R
lion每经过一场未能杀死敌人的战斗，忠诚度就降低K。
要求输出从0时0分开始，到时间T为止(包括T) 的所有事件。T以分钟为单位，0 <= T <= 5000
第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000
第三行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的攻击力。它们都大于0小于等于10000
*/

struct lionRunToPrint{
    int color;
    int No;
    int city;
    lionRunToPrint(int c, int n, int ci):color(c),No(n),city(ci){}
};
vector<lionRunToPrint> lionRunToPrintList;
struct myCmp{
    bool operator()(lionRunToPrint &a, lionRunToPrint & b){
        if(a.city != b.city)
            return a.city < b.city;
        else 
            return a.color < b.color;
    }
};

//hour
int timeHourCount = 0;
//minute
int timeMinCount = 0;
//判断是否到T
int timeCount = 0;
//0 for red, 1 for blue
string warriorBornList[2][5] = {{"iceman","lion","wolf","ninja","dragon"},
{"lion","dragon","ninja","iceman","wolf"} };
string flagList[2] = {"red", "blue"};
string waponList[] = {"sword","bomb","arrow"};
#define MaxWarrior 5

void printCurrentTime(){
    cout << setfill('0') << setw(3) << timeHourCount << setfill(' ');
    cout << ":" ;
    cout << setfill('0') << setw(2) << timeMinCount << setfill(' ');
    cout << " ";
}

//武器类
class Wapon{
public:
    int attackPower;
    int durability;
    virtual int usedOnce()=0;
};

class Sword:public Wapon{
public:
    Sword(int a, int d = 1){
        attackPower = a;
        durability = d;
    }
    int usedOnce(){
        attackPower = attackPower * 8 / 10;
        if(attackPower == 0)
            return 0;
        return 1;
    };
};

class Bomb:public Wapon{
public:
    Bomb(){}
    int usedOnce(){
        return 0;
    }
};

class Arrow:public Wapon{
public:
    Arrow(int a = R, int d = 3){
        attackPower = a;
        durability = d;
    }
    int usedOnce(){
        --durability;
        return durability;
    }
};

//武士类
class Warrior{
public:
    string name;
    int No;
    int life;
    int attack;
    int color; //red or blue
    int pos;
    vector<Wapon*> waponOwned;
    virtual void goAhead(){
        if(color == 0 && pos != N+1)
            ++pos;
        if(color == 1 && pos != 0)
            --pos;
    }
    virtual bool judgeRun(){return false;}
    virtual void run(){}
};
//dragon 、ninja、iceman、lion、wolf

class Dragon:public Warrior{
public:
    double morale;
    Dragon(int n, int l, int a, int c, double m){
        name = "dragon";
        No = n;
        life = l;
        attack = a;
        color = c;
        morale = m;
        pos = (color == 0)? 0: (N+1);
        if(No % 3 == 0){
            Sword tmp(attack * 2 / 10);
            waponOwned.push_back(&tmp);
        } else if(No % 3 == 1){
            Bomb tmp;
            waponOwned.push_back(&tmp);
        } else{
            Arrow tmp;
            waponOwned.push_back(&tmp);
        }
    }
    void win(){morale += 0.2;}
    void notWin(){morale -= 0.2;}
    void yell(int city){
        if(morale > 0.8){
            printCurrentTime();
            cout << flagList[color] << " dragon " << No << " yelled in city " << city << endl; 
        }
    }
};

class Ninja:public Warrior{
public:
    int step;
    Ninja(int n, int l, int a, int c){
        name = "ninja";
        No = n;
        life = l;
        attack = a;
        color = c;
        step = 0;
        pos = (color == 0)? 0: (N+1);
        if(No % 3 == 0){
            Sword tmp(attack * 2 / 10);
            waponOwned.push_back(&tmp);
        } else if(No % 3 == 1){
            Bomb tmp;
            waponOwned.push_back(&tmp);
        } else{
            Arrow tmp;
            waponOwned.push_back(&tmp);
        }
        if((No+1) % 3 == 0){
            Sword tmp(attack * 2 / 10);
            waponOwned.push_back(&tmp);
        } else if((No+1) % 3 == 1){
            Bomb tmp;
            waponOwned.push_back(&tmp);
        } else{
            Arrow tmp;
            waponOwned.push_back(&tmp);
        }
    }

    void goAhead(){
        if(color == 0 && pos != N+1){
            ++pos;
            ++step;
        }
        if(color == 1 && pos != 0){
            --pos;
            ++step;
        }
        if(step == 2){
            step = 0;
            life -= 9;
            if(life <=0)
                life = 1;
            attack += 20;
        }
    }
};

class Iceman:public Warrior{
public:
    Iceman(int n, int l, int a, int c){
        name = "iceman";
        No = n;
        life = l;
        attack = a;
        color = c;
        pos = (color == 0)? 0: (N+1);
        if(No % 3 == 0){
            Sword tmp(attack * 2 / 10);
            waponOwned.push_back(&tmp);
        } else if(No % 3 == 1){
            Bomb tmp;
            waponOwned.push_back(&tmp);
        } else{
            Arrow tmp;
            waponOwned.push_back(&tmp);
        }
    }
};

class Lion:public Warrior{
public:
    int loyalty;
    Lion(int n, int l, int a, int c, int lo){
        name = "iceman";
        No = n;
        life = l;
        attack = a;
        color = c;
        loyalty = lo;
        pos = (color == 0)? 0: (N+1);
    }

    bool judgeRun(){
        if(loyalty <=0 )
            return true;
        else 
            return false;
    }
    int loseLoyalty(){
        loyalty -= K;
        return loyalty;
    }
    int beKilled(){
        return life;
    }
    void run(){
        lionRunToPrint tmp(color, No, pos);
        lionRunToPrintList.push_back(tmp);
    }
};

class Wolf:public Warrior{
public:
    Wolf(int n, int l, int a, int c){
        name = "iceman";
        No = n;
        life = l;
        attack = a;
        color = c;
        pos = (color == 0)? 0: (N+1);
    }

    void getWapon(Wapon * wp){
        waponOwned.push_back(wp);
    }
};

//城市类
class City{
public:
    int No;
    int flag; //0 for red, 1 for blue, -1 for null
    int lifeSource;
    Warrior * redW ;// red warrior no
    Warrior * blueW;
    City():flag(-1),lifeSource(0),redW(NULL),blueW(NULL){}
    void produceLife(){lifeSource += 10;}
    int loseLife(){
        int tmp = lifeSource;
        lifeSource = 0;
        return tmp;
    }
    void wDead(int c){
        if(c == 0)
            redW = NULL;
        else 
            blueW = NULL;
    }
}city[22];

class Tribe{
public:  
    int color;
    int life;
    int toBorn;
    int wNo;
    vector<Warrior*> warriorList;
    Tribe(int c, int l = M):color(c),life(l),wNo(1){}
    void createWarrior(){
        if(warriorBornList[color][wNo % 5] == "dragon"){
            if(life > dragonLife){
                life -= dragonLife;
                Dragon tmp(wNo, dragonLife, dragonAttack, color, double(life) / dragonLife);
                warriorList.push_back(&tmp);
                ++wNo;
            }
        }
        if(warriorBornList[color][wNo % 5] == "ninja"){
            if(life > ninjaLife){
                life -= ninjaLife;
                Ninja tmp(wNo, ninjaLife, ninjaAttack, color);
                warriorList.push_back(&tmp);
                ++wNo;
            }
        }
        if(warriorBornList[color][wNo % 5] == "iceman"){
            if(life > icemanLife){
                life -= icemanLife;
                Iceman tmp(wNo, icemanLife, icemanAttack, color);
                warriorList.push_back(&tmp);
                ++wNo;
            }
        }
        if(warriorBornList[color][wNo % 5] == "lion"){
            if(life > lionLife){
                life -= lionLife;
                Lion tmp(wNo, lionLife, lionAttack, color, life);
                warriorList.push_back(&tmp);
                ++wNo;
            }
        }
        if(warriorBornList[color][wNo % 5] == "wolf"){
            if(life > wolfLife){
                life -= wolfLife;
                Wolf tmp(wNo, wolfLife, wolfAttack, color);
                warriorList.push_back(&tmp);
                ++wNo;
            }
        }
    }
    void lionRun(){
        vector<Warrior*>::iterator it = warriorList.begin();
        while(it != warriorList.end()){
            if((*it)->name == "wolf" && (*it)->judgeRun()){
                city[(*it)->pos].wDead(color);
                vector<Warrior*>::iterator tmp = it;
                ++it;
                (*tmp)->run();
                warriorList.erase(tmp);
            }
            else 
                ++it;
        }
    }
    void warriorGo(){
        vector<Warrior*>::iterator it = warriorList.begin();
        while(it != warriorList.end()){
            (*it)->goAhead();
        }
    }
};

void tribeRun(Tribe & redTribe, Tribe & blueTribe){

}

int main(){
    //freopen("in.in","r",stdin);
    //freopen("out.out","w",stdout);
    for(int i = 0; i < 22; ++i)
        city[i].No = i + 1;
    int casen;
    cin >> casen;
    for(int i = 1; i <= casen; ++i){
        cin >> M >> N >> R >> K >> T;
        cin >> dragonAttack >> ninjaAttack >> icemanAttack >> lionAttack >> wolfAttack;
        cin >> dragonLife >> ninjaLife >> icemanLife >> lionLife >> wolfLife;
        Tribe redTribe(M),blueTribe(M);
        cout << "Case " << i << ":" <<endl;
        tribeRun(redTribe, blueTribe);
    }
    return 0;
}
