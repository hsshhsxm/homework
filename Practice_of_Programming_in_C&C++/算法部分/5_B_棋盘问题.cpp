#include <iostream>
#include <cstring>
using namespace std;

char a[10][10];
int used[10];
int n,k;
int res;

void dfs(int x, int y){
	if(y >= k){
		++res;
		return;
	}
	for(int i = x; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if(used[j] == 0 && a[i][j] == '#'){
				used[j] = 1;
				dfs(i+1,y+1);
				used[j] = 0;
			}
	return;
}

int main(){
	cin >> n >> k;
	while(n != -1 && k != -1){
		memset(used, 0, sizeof(used));
		res = 0;
		for(int i = 0; i <n; ++i)
			cin >> a[i];
		dfs(0,0);
		cout << res << endl;
		cin >> n >> k;
	}
	return 0;
}