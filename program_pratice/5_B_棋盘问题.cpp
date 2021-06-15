#include <iostream>
#include <cstring>
using namespace std;

int visited[50];
char input[50][50];
int res;
int n,k;

void dfs(int x, int y){
    if(y >= k){
        ++res;
        return;
    }
    for(int i = x; i < n; ++i)
        for(int j = 0; j < n; ++j)
            if(visited[j] == 0 && input[i][j] == '#'){
                visited[j] = 1;
                dfs(i+1, y+1);
                visited[j] = 0;
            }
}

int main(){
    cin >> n >> k;
    memset(visited, 0 ,sizeof(visited));
    memset(input, false, sizeof(input));
    while(n != -1 || k != -1){
        for(int i = 0; i < n; ++i)
                cin >> input[i];
        res = 0;
        dfs(0,0);
        cout << res << endl;
        cin >> n >> k;
    }
    return 0;
}