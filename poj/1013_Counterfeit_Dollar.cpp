#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

//ac
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        string str[9];
        bool judge = false;
        for(int i = 0; i < 9; ++i)
            cin >> str[i];
        for(int i = 0; i < 12; ++i){
            int a[12];
            for(int j = 0; j < 12; ++j)
                a[j] = 1;
            for(int j = 0; j < 3 && judge == false; ++j){
                a[i] = 0;
                int r = 0,l = 0;
                for(int k = 0; k < str[j*3].size(); ++k){
                    l += a[str[j*3][k] - 'A'];
                    r += a[str[j*3 + 1][k] - 'A'];
                }
                //cout << r << " " << l << endl;
                string t[3] = {"even", "up", "down"};
                //printf("l = %d, r = %d, t = %s, str = %s\n", l, r, t[(l - r + 3) % 3].c_str(), str[j*3 + 2].c_str());
                if(t[(l - r + 3) % 3] == str[j*3 + 2]){
                    //printf("i = %d, j = %d\n",i,j);
                    if(j == 2)
                        judge = true;
                    else 
                        continue;
                }
                else 
                    break;
            }
            for(int j = 0; j < 3 && judge == false; ++j){
                a[i] = 2;
                int r = 0,l = 0;
                for(int k = 0; k < str[j*3].size(); ++k){
                    l += a[str[j*3][k] - 'A'];
                    r += a[str[j*3 + 1][k] - 'A'];
                }
                //cout << r << " " << l << endl;
                string t[3] = {"even", "up", "down"};
                //printf("l = %d, r = %d, t = %s, str = %s\n", l, r, t[(l - r + 3) % 3].c_str(), str[j*3 + 2].c_str());
                if(t[(l - r + 3) % 3] == str[j*3 + 2]){
                    //printf("i = %d, j = %d\n",i,j);
                    if(j == 2)
                        judge = true;
                    else 
                        continue;
                }
                else 
                    break;
            }
            if(judge){
                if(a[i] == 0)
                    printf("%c is the counterfeit coin and it is light.\n", 'A' + i);
                if(a[i] == 2)
                    printf("%c is the counterfeit coin and it is heavy.\n", 'A' + i);
                break;
            }
        }
    }
}