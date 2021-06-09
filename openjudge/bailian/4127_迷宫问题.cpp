#include <iostream>
using namespace std;

struct Node{
    int x,y;
    int front;
}node[30], ans[30];

int main()
{
    int maze[5][5];
    int next[4][2]={0,1,1,0,0,-1,-1,0};
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            cin >> maze[i][j];
    int head = 1, tail = 1;
    int dx,dy;
    node[tail].x = 0;
    node[tail].y = 0;
    node[tail].front = 0;
    maze[0][0] = 1;
    tail++;
    while(head < tail){
        for(int i = 0; i < 4; ++i){
            dx = node[head].x + next[i][0];
            dy = node[head].x + next[i][1];
            if(dx < 0 || dx > 4 || dy < 0 || dy > 4 || maze[dx][dy] == 1)
                continue;
            maze[dx][dy] = 1;
            node[tail].x = dx;
            node[tail].y = dy;
            node[tail].front = head;
            tail++;
            if(dx == 4 && dy == 4)
                break;
        }
        if(dx == 4 && dy == 4)
            break;
        head++;
    }
    tail--;
    int i = 0;
    while(tail){
        ans[i] = node[tail];
        i++;
        tail = node[tail].front;
    }
    while(i--)
        cout << "(" << ans[i].x << ", " << ans[i].y << ")" << endl;
    return 0;
}

