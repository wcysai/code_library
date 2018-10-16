    // ! This procedure is to replace `dijkstra', and cannot be used alone.
    bool inq[MAXV];
    void spfa(int src){
        queue<int> q;
        fill(d, d + V + 1, INF);
        d[src] = 0;
        fill(inq, inq + V + 1, false);
        q.push(src); inq[src] = true;
        while (!q.empty()){
            int u = q.front(); q.pop(); inq[u] = false;
            rep (i, adj[u].size()){
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
