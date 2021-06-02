#include <iostream>
#include <vector>
using namespace std;

int wall[50][50];
// TODO UF
int main()
{
    int m,n;
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            cin >> wall[i][j];
    vector< vector<int> > result;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            vector<int> tmp;
            switch (wall[i][j])
            {
            case 1:
                tmp.push_back(i*n+j+1);
                tmp.push_back((i+1)*n+j);
                if(i > 0)
                    tmp.push_back((i-1)*n+j);
                break;
            case 2:
                tmp.push_back(i*n+j+1);
                tmp.push_back((i+1)*n+j);
                if(j > 0)
                    tmp.push_back(i*n+j-1);
                break;
            case 4:
                tmp.push_back((i+1)*n+j);
                if(j > 0)
                    tmp.push_back(i*n+j-1);
                if(i > 0)
                    tmp.push_back((i-1)*n+j);
                break;
            case 8:
                tmp.push_back(i*n+j+1);
                if(j > 0)
                    tmp.push_back(i*n+j-1);
                if(i > 0)
                    tmp.push_back((i-1)*n+j);
                break;
            case 3:
                tmp.push_back(i*n+j+1);
                tmp.push_back((i+1)*n+j);
                break;
            case 5:
                tmp.push_back((i+1)*n+j);
                if(i > 0)
                    tmp.push_back((i-1)*n+j);
                break;
            case 9:
                tmp.push_back(i*n+j+1);
                if(i > 0)
                    tmp.push_back((i-1)*n+j);
                break;
            case 6:
                tmp.push_back((i+1)*n+j);
                if(j > 0)
                    tmp.push_back(i*n+j-1);
                break;
            case 10:
                tmp.push_back(i*n+j+1);
                if(j > 0)
                    tmp.push_back(i*n+j-1);
                break;
            case 12:
                if(j > 0)
                    tmp.push_back(i*n+j-1);
                if(i > 0)
                    tmp.push_back((i-1)*n+j);
                break;
            case 7:
                
                break;
            case 11:
                
                break;
            case 14:
                
                break;
            case 15:
                
                break;
            default:
                cout << wall[i][j] << endl;
                break;
            }
        }
    }
    return 0;
}