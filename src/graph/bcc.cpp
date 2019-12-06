const int MAXN = 100005;
int n, m;
vector<int> adj[MAXN];
int dfn[MAXN], low[MAXN], idx = 0;
vector<int> bccin[MAXN];
vector<vector<pair<int, int>>> bcc;
stack<pair<int, int>> st;

void dfs(int u, int p = 0) {
    dfn[u] = low[u] = ++idx;
    for (int v : adj[u]) {
        if (!dfn[v]) {
            st.emplace(u, v);
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                bccin[u].push_back(bcc.size());
                vector<pair<int, int>> cur;
                do {
                    cur.push_back(st.top());
                    st.pop();
                } while (cur.back() != make_pair(u, v));
                reverse(range(cur));
                bcc.push_back(move(cur));
            }
        } else if (dfn[v] < dfn[u] and v != p) {
            st.emplace(u, v);
            low[u] = min(low[u], dfn[v]);
        }
    }
}
