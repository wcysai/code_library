const int MAXN = 100005;
int n, m;
vector<int> adj[MAXN];
int dfn[MAXN], low[MAXN], idx;
int sccid[MAXN], sccn;
vector<int> scc[MAXN];

void dfs(int u) {
    static stack<int> s;
    dfn[u] = low[u] = ++idx;
    s.push(u);
    for (int v : adj[u]) {
        if (!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (!sccid[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        sccn++;
        do {
            sccid[s.top()] = sccn;
            scc[sccn].push_back(s.top());
            s.pop();
        } while (scc[sccn].back() != u);
    }
}

vector<int> adjc[MAXN];
void contract() {
    Rep (u, n) for (int v : adj[u]) if (sccid[u] != sccid[v])
        adjc[sccid[u]].push_back(sccid[v]);
}
