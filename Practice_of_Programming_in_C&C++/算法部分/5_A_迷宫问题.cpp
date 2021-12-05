#include <iostream>
#include <cstring>
using namespace std;

int maze[6][6];
int roadx[25];
int roady[25];
int resx[25];
int resy[25];
int depth;
int minLength;

void dfs(int x, int y){
	if(depth > minLength)
		return;
	roadx[depth] = x;
	roady[depth] = y;
	depth++;
	if(x == 5 && y == 5){
		if(depth < minLength){
			minLength = depth;
			for(int i = 0; i < minLength; ++i){
				resx[i] = roadx[i];
				resy[i] = roady[i];
			}
		}
		return;
	}
	maze[x][y] = 1;
	if(x+1 <= 5 && maze[x+1][y] == 0)
		dfs(x+1,y);
	if(y+1 <= 5 && maze[x][y+1] == 0)
		dfs(x,y+1);
	if(y-1 >= 1 && maze[x][y-1] == 0)
		dfs(x,y-1);
	if(x-1 >= 1 && maze[x-1][y] == 0)
		dfs(x-1,y);
	depth--;
	maze[x][y] = 0;
	return;
}

int main(){
	memset(maze, 1 ,sizeof(maze));
	memset(roadx, 0, sizeof(roadx));
	memset(roady, 0 ,sizeof(roady));
	memset(resx, 0 , sizeof(resx));
	memset(resy, 0 , sizeof(resy));
	depth = 0;
	minLength = 30;
	for(int i = 1; i <= 5; ++i)
		for(int j = 1; j <= 5; ++j)
			cin >> maze[i][j];
	maze[1][1] = 1;
	dfs(1,1);
	for(int i = 0; i < minLength; ++i){
		printf("(%d, %d)\n",resx[i]-1,resy[i]-1);
	}
	return 0;
}