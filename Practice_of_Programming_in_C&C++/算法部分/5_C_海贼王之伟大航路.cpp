#include <iostream>
#include <cstring>
using namespace std;

int n;
int t[20][20];
int totalTime;
int minTime;
int visited[20];
int npos[16][1<<16];

void dfs(int x, int  nowstate){
	if(totalTime > minTime){
		return;
	}
	if(visited[x])
		return;
	//最优性剪枝
	//如果原来到达目前状态有更好的方式，则剪枝
	if(npos[x][nowstate] == -1 || npos[x][nowstate] > totalTime){
		npos[x][nowstate] = totalTime;
	}
	else 
		return;
	visited[x] = 1;
	int tmp = 0;
	for(int i = 0; i < n; ++i)
		tmp += visited[i];
	if(tmp == n-1){
		minTime = min(minTime, totalTime + t[x][n-1]);
		visited[x] = 0;
		return;
	}
	for(int i = 1; i < n-1; ++i){
		if(x == i)
			continue;
		if(visited[i] == 0 && totalTime + t[x][i] < minTime){
			nowstate += 1 << (i - 1);
			totalTime += t[x][i];
			dfs(i, nowstate);
			totalTime -= t[x][i];
			nowstate -= 1 << (i - 1);
		}
	}
	visited[x] = 0;
	return;
}

int main(){
	cin >> n;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			cin >> t[i][j];
	for(int i = 0; i < n; ++i)
		visited[i] = 0;
	minTime = 10000*n;
	totalTime = 0;
	memset(npos, -1, sizeof(npos));
	dfs(0,1);
	cout << minTime << endl;
	return 0;
}