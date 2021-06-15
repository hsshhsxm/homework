#include <iostream>
#include <cstring>
using namespace std;

int maze[5][5];

int main(){
    memset(maze, 0, sizeof(maze));
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            cin >> maze[i][j];
    return 0;
}