#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct Course{
    char name[55];
    int ddl, cost;
};

bool operator<(const Course & a, const Course & b){
    return strcmp(a.name, b.name) < 0;
}

Course course[20];
int dp[1<<20];
int dpa[1<<20];

bool compareV(vector<int> & a, vector<int> & b){
    for(int i = 0; i < a.size(); ++i){
        if(a[i] > b[i])
            return true;
        if(a[i] < b[i])
            return false;
    }
    return false;
}

void push(int n, vector<int> & v){
    if(n == 0)
        return;
    push((1 << dpa[n]) ^ n, v);
    v.push_back(dpa[n]);
}

int main()
{
    int N;
    cin >> N;
    while(N--){
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i)
            cin >> course[i].name >> course[i].ddl >> course[i].cost;
        sort(course, course + n);
        for(int i = 0; i < (1 << n); ++i)
            dp[i] = 1000;
        dp[0] = 0;
        for(int i = 0; i < (1 << n); ++i){
            int t = 0;
            for(int j = 0; j < n; ++j)
                if((i >> j) & 1)
                    t += course[j].cost;
            for(int j = 0; j < n; ++j){
                if(! ((i >> j) & 1)){
                    int tmp = dp[i];
                    if(course[j].ddl < t + course[j].cost)
                        tmp += course[j].cost + t - course[j].ddl;
                    if(tmp < dp[(1 << j) + i]){
                        dp[(1<<j) + i] = tmp;
                        dpa[(1<<j) + i] = j;
                    }
                    else if(tmp == dp[(1 << j) + i]){
                        vector<int> a, b;
                        push((1<<j)+i,a);
                        push(i,b);
                        b.push_back(j);
                        if(compareV(a,b))
                            dpa[(1 << j) + i] = j;
                    }
                }
            }
        }
        cout << dp[(1 << n) - 1] << endl;
        vector<int> res;
        push((1<<n)-1, res);
        for(int i = 0; i < res.size(); ++i)
            cout << course[res[i]].name << endl;
    }
    return 0;
}

