#include <iostream>
using namespace std;

char wall[17][17];
char ori[17][17];
int binary[16];
int n;

void setBinary(int k){
	for(int i = 0; i < 16; ++i)
		binary[i] = 0;
	int i = 0;
	while(k){
		binary[i] = k % 2;
		k /= 2;
		++i;
	}
}

void init(){
	for(int i = 0; i < 17; ++i){
		for(int j = 0; j < 17; ++j){
			wall[i][j] = 'w';
			ori[i][j] = 'w';
		}
	}
}

void resetWall(){
	for(int i = 0; i < 17; ++i)
		for(int j = 0; j < 17; ++j)
			wall[i][j] = ori[i][j];
}

bool check(){
	for(int i = 1; i <=n; ++i)
		for(int j = 0; j <=n; ++j)
			if(wall[i][j] == 'w')
				return false;
	return true;
}

char color(char c){
	if(c == 'w')
		return 'y';
	if(c == 'y')
		return 'w';
}

void paint(int i, int j){
	wall[i][j] = color(wall[i][j]);
	wall[i-1][j] = color(wall[i-1][j]);
	wall[i+1][j] = color(wall[i+1][j]);
	wall[i][j-1] = color(wall[i][j-1]);
	wall[i][j+1] = color(wall[i][j+1]);
}

void solve(){
	int minStep = 0;
	for(int i = 0; i < (1<<n); ++i){
		setBinary();
		int step = 0;
		for(int j = 0; j < n; ++j)
			if(binary[j] == 1){
				++step;
				paint(1,j+1);
			}
		for(int j = 2; j <=n; ++j)
			for(int k = 1; i <=n; ++k)
				if(wall[j - 1][k] == 'w'){
					paint(j,k);
					++step;
				}
		if(ckeck()){
			if(step < minStep)
				minStep = step;
		}
		resetWall();
	}
	if(minStep == 0)
		cout << "inf" << endl;
	else
		cout << minStep << endl;
}

int main(){
	init();
	cin >> n;
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= n; ++j){
			cin >> wall[i][j];
			ori[i][j] = wall[i][j];
		}
	}
	solve();
    return 0;
}