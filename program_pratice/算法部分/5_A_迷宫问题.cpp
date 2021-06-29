#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

struct Point{
    int x,y;
    Point(int a, int b):x(a), y(b){}
    bool operator!=(const Point & a){
        if(x != a.x && y != a.y)
            return true;
        return false;
    }
    bool operator==(const Point & a){
        if(x == a.x && y == a.y)
            return true;
        return false;
    }
};

int maze[5][5];
int visited[5][5];
vector<Point> pointV;
vector<Point> resV;

Point getNextPoint(Point p){
    Point res(-1,-1);
    if(p.x - 1 >= 0){
        if(visited[p.x - 1][p.y] == 0 || visited[p.x][p.y] + 1 < visited[p.x - 1][p.y]){
            res.x = p.x - 1;
            res.y = p.y;
            return res;
        }
    }
    if(p.x + 1 < 5){
        if(visited[p.x + 1][p.y] == 0 || visited[p.x][p.y] + 1 < visited[p.x + 1][p.y]){
            res.x = p.x + 1;
            res.y = p.y;
            return res;
        }
    }
    if(p.y - 1 >= 0){
        if(visited[p.x][p.y - 1] == 0 || visited[p.x][p.y] + 1 < visited[p.x][p.y - 1]){
            res.x = p.x;
            res.y = p.y - 1;
            return res;
        }
    }
    if(p.y + 1 < 5){
        if(visited[p.x][p.y + 1] == 0 || visited[p.x][p.y] + 1 < visited[p.x][p.y + 1]){
            res.x = p.x;
            res.y = p.y + 1;
            return res;
        }
    }
    return res;
}

void getPath(Point & sp, Point & ep){
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            visited[i][j] = maze[i][j];
    if(sp == ep){
        pointV.push_back(sp);
        return;
    }
    vector<Point> visitedV;
    pointV.push_back(sp);
    visited[sp.x][sp.y] = true;
    while(pointV.size() != 0){
        Point next = getNextPoint(pointV[pointV.size()-1]);
        if(next.x == -1){
            pointV.pop_back();
            continue;
        }
        if(next == ep){
            visited[next.x][next.y] = visited[pointV[pointV.size()-1].x][pointV[pointV.size()-1].y] + 1;
            pointV.push_back(ep);
            vector<Point> tmpV = pointV;
            resV.clear();
            while(tmpV.size() != 0){
                resV.push_back(tmpV[tmpV.size() - 1]);
                tmpV.pop_back();
            }
            pointV.pop_back();
            continue;
        }
        //printf("next point = (%d, %d)\n", next.x, next.y);
        visited[next.x][next.y] = visited[pointV[pointV.size()-1].x][pointV[pointV.size()-1].y] + 1;
        pointV.push_back(next);
    }
}

int main(){
    memset(maze, 0, sizeof(maze));
    memset(visited, 0, sizeof(visited));
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            cin >> maze[i][j];
    Point sp(0,0), ep(4,4);
    getPath(sp, ep);
    vector<Point> tmpV;
    vector<Point>::reverse_iterator it = resV.rbegin();
    for(; it != resV.rend(); ++it)
        cout << "(" << it->x << ", " << it->y << ")" << endl;
    return 0;
}