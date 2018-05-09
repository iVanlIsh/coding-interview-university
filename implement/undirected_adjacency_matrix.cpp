#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <stack>
#include <queue>
#include <climits>

using namespace std;
const int MAXN = 10000;
int map[MAXN][MAXN];
int n = 0;
bool c[MAXN];

void dfs() {
    stack<int> s;
    memset(c, 0, sizeof(c));
    for(int i=0; i<n; i++) {
        if(c[i]) continue;
        s.push(i);
        while(!s.empty()) {
            int j = s.top();
            s.pop();
            if (c[j]) continue;
            int next;
            while(j!=-1) {
                next = -1;
                c[j] = true;
                cout << j << " ";
                for (int k = 0; k < n; k++) {
                    if (c[k]) continue;
                    if (map[j][k]!=-1) {
                        if (next == -1) next = k;
                        else s.push(k);
                    }
                }
                j = next;
            }
        }
    }
    cout<<endl;
}

void bfs() {
    queue<int> q;
    memset(c, 0, sizeof(c));
    for(int i=0; i<n; i++) {
        if(c[i]) continue;
        c[i] = true;
        cout<<i<<" ";
        q.push(i);
        while(!q.empty()) {
            int j = q.front();
            q.pop();
            for(int k=0; k<n; k++) {
                if(c[k]) continue;
                if(map[j][k]!=-1) {
                    c[k] = true;
                    cout<<k<<" ";
                    q.push(k);
                }
            }
        }
    }
    cout<<endl;
}

int min(int* distance) {
    int min = -1;
    for(int i=0; i<n; i++)
        if(!c[i]&&distance[i]<INT_MIN&&(min==-1||distance[min]>distance[i]))
            min = i;
    return min;
}

void dijkstra() {
    int previous[MAXN];
    int distance[MAXN];
    memset(c, 0, sizeof(c));
    memset(distance, 1, sizeof(distance));
    int from, to;
    cin>>from>>to;
    distance[from] = 0;
    previous[from] = -1;
    while(1) {
        int current = min(distance);
        if(current==to) {
            stack<int> path;
            while(current!=-1) {
                path.push(current);
                current = previous[current];
            }
            while(!path.empty()) {
                cout<<path.top()<<" ";
                path.pop();
            }
            cout<<endl;
            return;
        }
        if(current == -1) {
            cout<<"No path."<<endl;
            return;
        }
        c[current] = true;
        for(int i=0; i<n; i++) {
            if(c[i]||map[current][i]==-1) continue;
            if(distance[i] > distance[current] + map[current][i]) {
                distance[i] = distance[current] + map[current][i];
                previous[i] = current;
            }
        }
    }
}


//TODO
void prim() {

}

void kruskal() {

}

int main() {
    cin>>n;
    int i,j;
    for(int k=0; k<n; k++)
        for(int m=0; m<n; m++) {
            map[k][m] = -1;
            map[m][k] = -1;
        }
    int l;
    cin>>l;
    while(l--) {
        cin>>i>>j;
        cin>>map[i][j];
        map[j][i] = map[i][j];
    }
    dfs();
    bfs();
    dijkstra();

    prim();
    kruskal();

    return 0;
}