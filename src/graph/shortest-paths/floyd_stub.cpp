#include <iostream>
#include <climits>
using namespace std;

typedef long long LL;
const LL INF = LLONG_MAX / 2;
const int MAXV = 1005;
int V;
LL d[MAXV][MAXV];

void init(){
    for (int i = 0; i <= V; i++){
        for (int j = 0; j <= V; j++)
            d[i][j] = INF;
        d[i][i] = 0;
    }
}

void floyd(){
    for (int k = 0; k <= V; k++)
        for (int i = 0; i <= V; i++)
            for (int j = 0; j <= V; j++)
                // ! (*) if (d[i][k] <= INF && d[k][j] <= INF)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

int main(){
    int m, s;
    int u, v;
    long long w;
    cin >> V >> m >> s;
    init();
    while (m--){
        cin >> u >> v >> w;
        d[u][v] = min(d[u][v], w);
    }
    floyd();
    for (int i=1; i<=V; i++){
        cout << d[s][i] << ' ';
    }
    return 0;
}
