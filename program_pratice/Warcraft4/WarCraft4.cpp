#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

//#define DEBUG
//#define STD

//input
int M,N,R,K,T;
int dragonAttack, ninjaAttack, icemanAttack, lionAttack, wolfAttack;
int dragonLife, ninjaLife, icemanLife, lionLife, wolfLife;

int redTotalLife, blueTotalLife;
int redNo,blueNo;
bool tribeHasWarrior[2]; //0 for red 1 for blue
bool lastColor[2];
int tmpCityLife[2];
bool finish;


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
string waponList[3] = {"sword","bomb","arrow"};

void printCurrentTime(){
    cout << setfill('0') << setw(3) << timeHourCount << setfill(' ');
    cout << ":" ;
    cout << setfill('0') << setw(2) << timeMinCount << setfill(' ');
    cout << " ";
}

//武器类
class Wapon{
public:
    string name;
    int attackPower;
    virtual void usedOnce()=0;
    virtual bool isDestroyed()=0;
};

class Sword:public Wapon{
public:
    Sword(int a, int d = 1){
        name = "sword";
        attackPower = a;
    }
    void usedOnce(){
        attackPower = attackPower * 8 / 10;
    };
    bool isDestroyed(){
        return attackPower == 0;
    }
};

class Bomb:public Wapon{
public:
    Bomb(){
        name = "bomb";
    }
    
};

class Arrow:public Wapon{
public:
    int durability;
    Arrow(int a = R, int d = 3){
        name = "arrow";
        attackPower = R;
        durability = d;
    }
    void usedOnce(){
        --durability;
    }
    bool isDestroyed(){
        return durability == 0;
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
    Sword * sword;
    Arrow * arrow;
    bool ownBomb;
    virtual void goAhead(){}
    void addLife(int a){life += a;}
    virtual bool judgeRun(){return false;}
    virtual void changeMorale(int a){}
    virtual void yell(int city){}
    virtual void loseLoyalty(){}

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
        sword = NULL;
        arrow = NULL;
        ownBomb = false;
        if(No % 3 == 0){
            if(attack * 2 / 10 != 0)
                sword = new Sword(attack * 2 / 10);
        } else if(No % 3 == 1){
            ownBomb = true;
        } else{
            arrow = new Arrow;
        }
        printCurrentTime();
        cout << flagList[color] << " " << name << " " << No << " born" <<endl;
        cout << "Its morale is ";
        cout<<setiosflags(ios::fixed)<<setprecision(2);
        cout << morale << endl;
    }
    void changeMorale(int a){
        if(a == 0)
            morale -= 0.2;
        else 
            morale += 0.2;
    }
    void yell(int city){
        if(morale > 0.8){
            printCurrentTime();
            cout << flagList[color] << " dragon " << No << " yelled in city " << city << endl; 
        }
    }
};

class Ninja:public Warrior{
public:
    Ninja(int n, int l, int a, int c){
        name = "ninja";
        No = n;
        life = l;
        attack = a;
        color = c;
        pos = (color == 0)? 0: (N+1);
        sword = NULL;
        arrow = NULL;
        ownBomb = false;
        if(No % 3 == 0){
            if(attack * 2 / 10 != 0)
                sword = new Sword(attack * 2 / 10);
        } else if(No % 3 == 1){
            ownBomb = true;
        } else{
            arrow = new Arrow;
        }
        if((No+1) % 3 == 0){
            if(attack * 2 / 10 != 0)
                sword = new Sword(attack * 2 / 10);
        } else if((No+1) % 3 == 1){
            ownBomb = true;
        } else{
            arrow = new Arrow;
        }
        printCurrentTime();
        cout << flagList[color] << " " << name << " " << No << " born" <<endl;
    }
};

class Iceman:public Warrior{
public:
    int step;
    Iceman(int n, int l, int a, int c){
        name = "iceman";
        No = n;
        life = l;
        attack = a;
        color = c;
        step = 0;
        pos = (color == 0)? 0: (N+1);
        sword = NULL;
        arrow = NULL;
        ownBomb = false;
        if(No % 3 == 0){
            if(attack * 2 / 10 != 0)
                sword = new Sword(attack * 2 / 10);
        } else if(No % 3 == 1){
            ownBomb = true;
        } else{
            arrow = new Arrow;
        }
        printCurrentTime();
        cout << flagList[color] << " " << name << " " << No << " born" <<endl;
    }
    void goAhead(){
        ++step;
        if(step == 2){
            step = 0;
            life -= 9;
            if(life <=0)
                life = 1;
            attack += 20;
        }
    }
};

class Lion:public Warrior{
public:
    int loyalty;
    Lion(int n, int l, int a, int c, int lo){
        name = "lion";
        No = n;
        life = l;
        attack = a;
        color = c;
        loyalty = lo;
        pos = (color == 0)? 0: (N+1);
        sword = NULL;
        arrow = NULL;
        ownBomb = false;
        printCurrentTime();
        cout << flagList[color] << " " << name << " " << No << " born" <<endl;
        cout << "Its loyalty is " << loyalty << endl;
    }

    bool judgeRun(){
        if(loyalty <=0 )
            return true;
        else 
            return false;
    }
    void loseLoyalty(){
        loyalty -= K;
    }
};

class Wolf:public Warrior{
public:
    Wolf(int n, int l, int a, int c){
        name = "wolf";
        No = n;
        life = l;
        attack = a;
        color = c;
        pos = (color == 0)? 0: (N+1);
        sword = NULL;
        arrow = NULL;
        ownBomb = false;
        printCurrentTime();
        cout << flagList[color] << " " << name << " " << No << " born" <<endl;
    }
};

//城市类
class City{
public:
    int No;
    int color; //0 for red, 1 for blue, -1 for null
    int lifeSource;
    int lastWin;
	int justWin;
    Warrior * w[2];
    void init(int i){
        No = i;
        color = -1;
        lifeSource = 0;
        lastWin = -1;
        justWin = -1;
        w[0] = NULL;
        w[1] = NULL;
    }
    void produceLife(){lifeSource += 10;}
    void loseLifeToTribe(){
        int c = -1;
        if(w[0] != NULL && w[1] == NULL)
            c = 0;
        if(w[1] != NULL && w[0] == NULL)
            c = 1;
        if(c != -1){
            if(c == 0)
                redTotalLife += lifeSource;
            if(c == 1)
                blueTotalLife += lifeSource;
            printCurrentTime();
            cout << flagList[w[c]->color] << " " << w[c]->name << " " << w[c]->No << " "
            << "earned " << lifeSource << " elements for his headquarter" << endl;
            lifeSource = 0;
        }
    }
    void loseLife(int c){//30
        printCurrentTime();
        cout << flagList[w[c]->color] << " " << w[c]->name << " " << w[c]->No << " "
        << "earned " << lifeSource << " elements for his headquarter" << endl;
        tmpCityLife[c] += lifeSource;
        lifeSource = 0;
    }
    void win(int c, int l, int d){//40
        if(w[c]->name == "wolf"){
            if(w[c]->sword == NULL && w[1-c]->sword != NULL)
                w[c]->sword = new Sword(w[1-c]->sword->attackPower);
            if(!w[c]->ownBomb && w[1-c]->ownBomb)
                w[c]->ownBomb = true;
            if(w[c]->arrow == NULL && w[1-c]->arrow != NULL)
                w[c]->arrow = new Arrow(w[1-c]->arrow->attackPower, w[1-c]->arrow->durability);
        }
        delete w[1-c];
        w[1-c] = NULL;
        if(d){
            w[c]->changeMorale(1);
            w[c]->yell(No);
        }
        w[c]->life += l;
        loseLife(c);
        justWin = c;
        if(color != c && lastWin == c){
            color = c;
            printCurrentTime();
            cout << flagList[c] << " flag raised in city " << No << endl;
        }
        lastWin = c;
    }
    void fight(){
        int first = 1;
        justWin = -1;        
        if(w[0] == NULL){
            if(w[1] != NULL && w[1]->life <= 0){
                delete w[1];
                w[1] = NULL;
            }
            return;
        }
        if(w[1] == NULL){
            if(w[0] != NULL && w[0]->life <= 0){
                delete w[0];
                w[0] = NULL;
            }
            return;
        }
        if(color == 0 || (color == -1 && No % 2 == 1))
            first = 0;
        else 
            first = 1;
        if(w[0]->life == 0 && w[1]->life == 0){
            delete w[0];
            delete w[1];
            w[0] = w[1] = NULL;
            return;
        }
        if(w[first]->life == 0){
            win(1-first, 0, 0);
            return;
        }
        if(w[1-first]->life == 0){
            win(first, 0, 1);
            return;
        }
        //攻击
        int leftLife = 0;
        (w[1-first]->name == "lion") ? (leftLife = w[1-first]->life) : (leftLife = 0);
        printCurrentTime();
        cout << flagList[first] << " " << w[first]->name << " " << w[first]->No << " attacked "
        << flagList[1-first] << " " << w[1-first]->name << " " << w[1-first]->No << " in city "
        << No << " with " << w[first]->life << " elements and force " << w[first]->attack << endl;
        int swordAttack = 0;
        if(w[first]->sword != NULL){
            swordAttack = w[first]->sword->attackPower;
            w[first]->sword->usedOnce();
            if(w[first]->sword->isDestroyed()){
                delete w[first]->sword;
                w[first]->sword = NULL;
            }
        }
        w[1-first]->life -= w[first]->attack + swordAttack;
        if(w[1-first]->life <= 0){
            printCurrentTime();
            cout << flagList[1-first] << " " << w[1-first]->name << " " << w[1-first]->No << " "
            <<  "was killed in city" << " " << No << endl;
            win(first,leftLife,1);
            return;
        }
        //反击
        (w[first]->name == "lion") ? (leftLife = w[first]->life) : (leftLife = 0);
        if(w[1-first]->name != "ninja"){
            int swordAttack = 0;
            if(w[1-first]->sword != NULL){
                swordAttack = w[1-first]->sword->attackPower;
                w[1-first]->sword->usedOnce();
                if(w[1-first]->sword->isDestroyed()){
                    delete w[1-first]->sword;
                    w[1-first]->sword = NULL;
                }
            }
            w[first]->life -= w[1-first]->attack / 2 + swordAttack;
            printCurrentTime();
            cout << flagList[1-first] << " " << w[1-first]->name << " " << w[1-first]->No << " "
            << "fought back against" << " " << flagList[first] << " " << w[first]->name << " " << w[first]->No
            << " in city " << No << endl;
            if(w[first]->life <= 0){
                printCurrentTime();
                cout << flagList[first] << " " << w[first]->name << " " << w[first]->No << " "
                <<  "was killed in city" << " " << No << endl;
                win(1-first, leftLife, 0);
                return;
            }
        }
        //平局
        w[0]->loseLoyalty();
        w[1]->loseLoyalty();
        w[first]->changeMorale(0);
        w[first]->yell(No);
        lastWin = -1;
    }
    void go(City * next, int c){
        w[c] = next->w[c];
        if(w[c] != NULL)
            w[c]->goAhead();
    }
    bool reachHead(int c){
        if(lastColor[c] == false)
            return false;
        printCurrentTime();
        cout << flagList[c] << " " << w[c]->name << " " << w[c]->No << " " << "reached" << " "
        << flagList[1-c] << " " << "headquarter with" << " " << w[c]->life << " elements and force "
        << w[c]->attack << endl;
        if(tribeHasWarrior[c])
            return true;
        tribeHasWarrior[c] = true;
        return false;
    }
    void lionRun(int c){
        if(w[c] != NULL && w[c]->judgeRun()){
            printCurrentTime();
            cout << flagList[w[c]->color] << " " << w[c]->name << " " << w[c]->No 
            << " ran away" <<endl; 
            delete w[c];
            w[c] = NULL;
        }
    }
    void useBomb(){
        int first = 1;
        if(w[0] == NULL || w[1] == NULL || w[0]->life == 0 || w[1]->life == 0)
            return;
        if(color==0 || (color==-1 && No%2==1))
            first = 0;
        int swordAttack = 0;
        if(w[first]->sword != NULL)
            swordAttack = w[first]->sword->attackPower;
        if(w[1-first]->life <= w[first]->attack + swordAttack){
            if(w[1-first]->ownBomb){
                printCurrentTime();
                cout << flagList[w[1-first]->color] << " " << w[1-first]->name << " "<<
                w[1-first]->No << " used a bomb and killed " << flagList[w[first]->color]
                << " " << w[first]->name << " "<< w[first]->No << endl;
                delete w[0];
                delete w[1];
                w[0] = NULL;
                w[1] = NULL;
            }
            return;
        }
        if(w[1-first]->name == "ninja")
            return;
        swordAttack = 0;
        if(w[1-first]->sword != NULL)
            swordAttack = w[1-first]->sword->attackPower;
        if(w[first]->life <= w[1-first]->attack/2 + swordAttack){
            if(w[first]->ownBomb){
                printCurrentTime();
                cout << flagList[w[first]->color] << " " << w[first]->name << " "<<
                w[first]->No << " used a bomb and killed " << flagList[w[1-first]->color]
                << " " << w[1-first]->name << " "<< w[1-first]->No << endl;
                delete w[0];
                delete w[1];
                w[0] = w[1] = NULL;
                return;
            }
        }
    }
    void useArrow(City * next, int c){
        if(w[c] == NULL)
            return;
        if(w[c]->arrow != NULL && next->w[1-c] != NULL){
            printCurrentTime();
            cout << flagList[c] << " " << w[c]->name << " " << w[c]->No << " shot";
            next->w[1-c]->life -= w[c]->arrow->attackPower;
            w[c]->arrow->usedOnce();
            if(w[c]->arrow->isDestroyed()){
                delete w[c]->arrow;
                w[c]->arrow = NULL;
            }
            if(next->w[1-c]->life <= 0){
                next->w[1-c]->life = 0;
                cout << " and killed " << flagList[1-c] << " " << next->w[1-c]->name << " "
                << next->w[1-c]->No;
            }
            cout << endl;
        }
    }
    void printWaponInfo(int c){
        bool judge = false;
        if(w[c] == NULL)
            return;
        printCurrentTime();
        cout << flagList[w[c]->color] << " " << w[c]->name << " " << w[c]->No << " has ";
        if(w[c]->arrow != NULL){
            cout << "arrow(" << w[c]->arrow->durability << ")";
            judge = true;
        }
        if(w[c]->ownBomb){
            if(judge)
                cout << ",";
            cout << "bomb";
            judge = true;
        }
        if(w[c]->sword != NULL){
            if(judge)
                cout << ",";
            cout << "sword(" << w[c]->sword->attackPower << ")";
            judge = true;
        }
        if(!judge)
            cout << "no weapon";
        cout << endl;
    }
    void printGoInfo(){
        if(w[0] != NULL){
            printCurrentTime();
            cout << flagList[w[0]->color] << " " << w[0]->name << " " << w[0]->No << " "
            << "marched to city" << " " << No << " with " << w[0]->life << " elements and force "
            << w[0]->attack << endl;
        }
        if(w[1] != NULL){
            printCurrentTime();
            cout << flagList[w[1]->color] << " " << w[1]->name << " " << w[1]->No << " "
            << "marched to city" << " " << No << " with " << w[1]->life << " elements and force "
            << w[1]->attack << endl;
        }
    }
}city[24];

void createWarrior(){
    Warrior * redTmp = NULL;
    Warrior * blueTmp = NULL;
    //red
    if(warriorBornList[0][redNo%5] == "dragon"){
        if(redTotalLife >= dragonLife){
            redTotalLife -= dragonLife;
            redTmp = new Dragon(redNo+1, dragonLife, dragonAttack, 0, (double)redTotalLife / dragonLife);
            ++redNo;
        }
    }
    else if(warriorBornList[0][redNo%5] == "ninja"){
        if(redTotalLife >= ninjaLife){
            redTotalLife -= ninjaLife;
            redTmp = new Ninja(redNo+1, ninjaLife, ninjaAttack, 0);
            ++redNo;
        }
    }
    else if(warriorBornList[0][redNo%5] == "iceman"){
        if(redTotalLife >= icemanLife){
            redTotalLife -= icemanLife;
            redTmp = new Iceman(redNo+1, icemanLife, icemanAttack, 0);
            ++redNo;
        }
    }
    else if(warriorBornList[0][redNo%5] == "lion"){
        if(redTotalLife >= lionLife){
            redTotalLife -= lionLife;
            redTmp = new Lion(redNo+1, lionLife, lionAttack, 0, redTotalLife);
            ++redNo;
        }
    }
    else if(warriorBornList[0][redNo%5] == "wolf"){
        if(redTotalLife >= wolfLife){
            redTotalLife -= wolfLife;
            redTmp = new Wolf(redNo+1, wolfLife, wolfAttack, 0);
            ++redNo;
        }
    }
    //blue
    if(warriorBornList[1][blueNo%5] == "dragon"){
        if(blueTotalLife >= dragonLife){
            blueTotalLife -= dragonLife;
            blueTmp = new Dragon(blueNo+1, dragonLife, dragonAttack, 1, (double)blueTotalLife / dragonLife);
            ++blueNo;
        }
    }
    else if(warriorBornList[1][blueNo%5] == "ninja"){
        if(blueTotalLife >= ninjaLife){
            blueTotalLife -= ninjaLife;
            blueTmp = new Ninja(blueNo+1, ninjaLife, ninjaAttack, 1);
            ++blueNo;
        }
    }
    else if(warriorBornList[1][blueNo%5] == "iceman"){
        if(blueTotalLife >= icemanLife){
            blueTotalLife -= icemanLife;
            blueTmp = new Iceman(blueNo+1, icemanLife, icemanAttack, 1);
            ++blueNo;
        }
    }
    else if(warriorBornList[1][blueNo%5] == "lion"){
        if(blueTotalLife >= lionLife){
            blueTotalLife -= lionLife;
            blueTmp = new Lion(blueNo+1, lionLife, lionAttack, 1, blueTotalLife);
            ++blueNo;
        }
    }
    else if(warriorBornList[1][blueNo%5] == "wolf"){
        if(blueTotalLife >= wolfLife){
            blueTotalLife -= wolfLife;
            blueTmp = new Wolf(blueNo+1, wolfLife, wolfAttack, 1);
            ++blueNo;
        }
    }
    city[0].w[0] = redTmp;
    city[N+1].w[1] = blueTmp;
}

void warriorGoAhead(){
    lastColor[0] = lastColor[1] = false;
    if(city[N].w[0] != NULL){
        city[N+1].go(&city[N], 0);
        lastColor[0] = true;
    }
    for(int i = N; i > 0; --i)
        city[i].go(&city[i-1], 0);
    if(city[1].w[1] != NULL){
        city[0].go(&city[1], 1);
        lastColor[1] = true;
    }
    for(int i = 1; i < N + 1; ++i)
        city[i].go(&city[i+1], 1);
    city[0].w[0] = city[N+1].w[1] = NULL;
    if(city[0].reachHead(1)){
        printCurrentTime();
        cout << "red headquarter was taken" << endl;
        finish = true;
    }
    for(int i = 1; i < N + 1; ++i)
        city[i].printGoInfo();
    if(city[N+1].reachHead(0)){
        printCurrentTime();
        cout << "blue headquarter was taken" << endl;
        finish = true;
    }
}

void changeLife(){
    for(int i = 1; i < N + 1; ++i){
        if(blueTotalLife < 8)
            break;
        if(city[i].justWin == 1){
            city[i].w[1]->addLife(8);
            blueTotalLife -= 8;
        }
    }
    for(int i = N; i > 0; --i){
        if(redTotalLife < 8)
            break;
        if(city[i].justWin == 0){
            city[i].w[0]->addLife(8);
            redTotalLife -= 8;
        }
    }
    redTotalLife += tmpCityLife[0];
    blueTotalLife += tmpCityLife[1];
    tmpCityLife[0] = tmpCityLife[1] = 0;
}

void printTribeLife(){
    printCurrentTime();
    cout << redTotalLife << " elements in red headquarter" << endl;
    printCurrentTime();
    cout << blueTotalLife << " elements in blue headquarter" << endl;
}


int main(){
    #ifdef STD
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    int casen;
    cin >> casen;
    for(int k = 1; k <= casen; ++k){
        cin >> M >> N >> R >> K >> T;
        cin >> dragonLife >> ninjaLife >> icemanLife >> lionLife >> wolfLife;
        cin >> dragonAttack >> ninjaAttack >> icemanAttack >> lionAttack >> wolfAttack;
        //init data
        redTotalLife = blueTotalLife = M;
        redNo = blueNo = 0;
        finish = false;
        tmpCityLife[0] = tmpCityLife[1] = 0;
        tribeHasWarrior[0] = tribeHasWarrior[1] = false;
        lastColor[0] = lastColor[1] = false;
        timeCount = timeMinCount = timeHourCount = -1;

        cout << "Case " << k << ":" <<endl;
        for(int i = 0; i < N + 2; ++i)
            city[i].init(i);
        while(!finish && timeCount <= T){
            //0武士降生
            ++timeCount;
            if(timeCount > T)
                break;
            ++timeHourCount;
            ++timeMinCount;
            createWarrior();
            //5lion逃跑
            timeCount += 5;
            timeMinCount += 5;
            if(timeCount > T)
                break;
            city[0].lionRun(0);
            for(int i = 1; i < N+1; ++i){
                city[i].lionRun(0);
                city[i].lionRun(1);
            }
            city[N+1].lionRun(1);
            //10武士前进到某一城市, 武士抵达敌军司令部, 司令部被占领
            timeCount += 5;
            timeMinCount += 5;
            if(timeCount > T)
                break;
            warriorGoAhead();
            for(int i = 1; i < N+1; ++i)
                city[i].produceLife();
            //30武士取走该城市中的所有生命元
            timeCount += 20;
            timeMinCount += 20;
            if(timeCount > T)
                break;
            if(finish)
                break;
            for(int i = 1; i < N + 1; ++i)
                city[i].loseLifeToTribe();
            //35拥有arrow的武士放箭
            timeCount += 5;
            timeMinCount += 5;
            if(timeCount > T)
                break;
            city[1].useArrow(&city[2],0);
            for(int i = 2; i < N; ++i){
                city[i].useArrow(&city[i+1],0);
                city[i].useArrow(&city[i-1],1);
            }
            city[N].useArrow(&city[N-1],1);
            //38评估是否应该使用bomb
            timeCount += 3;
            timeMinCount += 3;
            if(timeCount > T)
                break;
            for(int i = 1; i < N + 1; ++i)
                city[i].useBomb();
            //40战斗
            timeCount += 2;
            timeMinCount += 2;
            if(timeCount > T)
                break;
            for(int i = 1; i < N + 1; ++i)
                city[i].fight();
            changeLife();
            //50司令部报告它拥有的生命元数量
            timeCount += 10;
            timeMinCount += 10;
            if(timeCount > T)
                break;
            printTribeLife();
            //55武士报告武器情况
            timeCount += 5;
            timeMinCount += 5;
            if(timeCount > T)
                break;
            for(int i = 0; i < N + 2; ++i)
                city[i].printWaponInfo(0);
            for(int i = 0; i < N + 2; ++i)
                city[i].printWaponInfo(1);
            //一轮循环结束
            timeCount += 4;
            timeMinCount = -1;
        }
    }
    return 0;
}
