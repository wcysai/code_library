#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 2147483647;
const int MAXV = 10005;
const int MAXE = 500005;
struct edge{
    int u, v, w;
};

struct graph{
    int V;
    vector<edge> adj[MAXV];
    int d[MAXV];
    edge* p[MAXV];

    void add_edge(int u, int v, int w){
        edge e;
        e.u = u; e.v = v; e.w = w;
        adj[u].push_back(e);
    }

    bool inq[MAXV];
    void spfa(int src){
        queue<int> q;
        fill(d, d + V + 1, INF);
        d[src] = 0;
        fill(inq, inq + V + 1, false);
        q.push(src); inq[src] = true;
        while (!q.empty()){
            int u = q.front(); q.pop(); inq[u] = false;
            for (int i = 0; i < adj[u].size(); i++){
                edge e = adj[u][i];
                if (d[e.v] > d[u] + e.w){
                    d[e.v] = d[u] + e.w;
                    p[e.v] = &adj[u][i];
                    if (!inq[e.v])
                        q.push(e.v), inq[e.v] = true;
                }
            }
        }
    }

} g;


int main(){
    int m, s, u, v, w;
    scanf("%d%d%d", &g.V, &m, &s);

    for (int i=0; i<m; i++){
        scanf("%d%d%d", &u, &v, &w);
        g.add_edge(u, v, w);
    };
    g.spfa(s);
    for (int i=1; i<=g.V; i++){
        printf("%d ", g.d[i]);
    }

    return 0;
}
