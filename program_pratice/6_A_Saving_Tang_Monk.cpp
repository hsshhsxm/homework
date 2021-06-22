#include <iostream>
#include <cstring>
#include <map>
#include <queue>
using namespace std;

struct Node
{
    int x,y,k,s;
    int step;
};

int N,M;
char myMap[105][105];
int dx[4] = {0,0,-1,1};
int dy[4] = {1,-1,0,0};
int step[105][105][15][35]; // node -> step[x][y][k][s]
int startX, startY;
int snakeNum;
int ans;
map<pair<int,int>,int>snake;
queue<Node> que;

bool check(int x, int y){
    if(x >= 1 && x <= N && y >= 1 && y <= N && myMap[x][y] != '#')
        return true;
    return false;
}

void bfs(Node startNode){
    if(que.size() != 0)
        que.pop();
    que.push(startNode);
    while(que.size() != 0){
        Node currentNode = que.front();
        que.pop();
        Node nextNode;
        for(int i = 0; i < 4; ++i){
            int newX = currentNode.x + dx[i];
            int newY = currentNode.y + dy[i];
            if(! check(newX, newY))
                continue;
            nextNode.x = newX;
            nextNode.y = newY;
            if(myMap[newX][newY] == 'S'){
                int tmp = snake[make_pair(newX,newY)];
                if(currentNode.s & (1 << (tmp - 1))){
                    nextNode.s = currentNode.s;
                    nextNode.k = currentNode.k;
                    nextNode.step = currentNode.step + 1;
                }
                else{
                    nextNode.s = (currentNode.s | (1 << (tmp - 1)));
                    nextNode.k = currentNode.k;
                    nextNode.step = currentNode.step + 2;
                }
                if(nextNode.step < step[newX][newY][nextNode.k][nextNode.s]){
                    step[newX][newY][nextNode.k][nextNode.s] = nextNode.step;
                    que.push(nextNode);
                }
            }
            else if(myMap[newX][newY] >= '1' && myMap[newX][newY] <= '9'){
                int tmp = myMap[newX][newY] - '0';
                if(tmp == currentNode.k + 1)
                    nextNode.k = currentNode.k + 1;
                else 
                    nextNode.k = currentNode.k;
                nextNode.s = currentNode.s;
                nextNode.step = currentNode.step + 1;
                if(nextNode.step < step[newX][newY][nextNode.k][nextNode.s]){
                    step[newX][newY][nextNode.k][nextNode.s] = nextNode.step;
                    que.push(nextNode);
                }
            }
            else if(myMap[newX][newY] == '.'){
                nextNode.k = currentNode.k;
                nextNode.s = currentNode.s;
                nextNode.step = currentNode.step + 1;
                if(nextNode.step < step[newX][newY][nextNode.k][nextNode.s]){
                    step[newX][newY][nextNode.k][nextNode.s] = nextNode.step;
                    que.push(nextNode);
                }
            }
            else if(myMap[newX][newY] == 'T'){
                nextNode.k = currentNode.k;
                nextNode.s = currentNode.s;
                nextNode.step = currentNode.step + 1;
                if(nextNode.step < step[newX][newY][nextNode.k][nextNode.s]){
                    step[newX][newY][nextNode.k][nextNode.s] = nextNode.step;
                }
                if(nextNode.k == M)
                    ans = min(step[newX][newY][nextNode.k][nextNode.s], ans);
                else 
                    que.push(nextNode);
            }
        }
    }
}

int main()
{
    cin >> N >> M;
    while(!(N == 0 && M == 0)){
        memset(step, 0x3f3f3f3f, sizeof(step));
        snake.clear();
        snakeNum = 0;
        ans = 0x3f3f3f3f;
        for(int i = 1; i < N + 1; ++i)
            for(int j = 1; j < N + 1; ++j){
                cin >> myMap[i][j];
                if(myMap[i][j] == 'K'){
                    startX = i;
                    startY = j;
                    myMap[i][j] = '.';
                }
                else if(myMap[i][j] == 'S'){
                    ++snakeNum;
                    snake[make_pair(i,j)] = snakeNum;
                }    
            }
        step[startX][startY][0][0] = 0;
        Node tmp;
        tmp.x = startX;
        tmp.y = startY;
        tmp.k = 0;
        tmp.s = 0;
        tmp.step = 0;
        bfs(tmp);
        if(ans == 0x3f3f3f3f)
            cout<<"impossible"<<endl;
        else
            cout<<ans<<endl;
        cin >> N >> M;
    }
    return 0;
}