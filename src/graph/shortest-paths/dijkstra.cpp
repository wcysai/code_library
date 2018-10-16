const int INF = 0x7f7f7f7f;
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

    bool done[MAXV];
    void dijkstra(int src){
        typedef pair<int,int> pii;
        priority_queue<pii, vector<pii>, greater<pii> > q;

        fill(d, d + V + 1, INF);
        d[src] = 0;
        fill(done, done + V + 1, false);
        q.push(make_pair(0, src));
        while (!q.empty()){
            int u = q.top().second; q.pop();
            if (done[u]) continue;
            done[u] = true;
            rep (i, adj[u].size()){
                edge e = adj[u][i];
                if (d[e.v] > d[u] + e.w){
                    d[e.v] = d[u] + e.w;
                    p[e.v] = &adj[u][i];
                    q.push(make_pair(d[e.v], e.v));
                }
            }
        }
    }
};
