const int MAXN = 100005, root = 1;
int n;
vector<int> adj[MAXN];
int fa[MAXN], dfn[MAXN], dep[MAXN], idx;
pair<int, int> st[MAXN * 2][33 - __builtin_clz(MAXN)];

int lca(int u, int v) {
    tie(u, v) = minmax(dfn[u], dfn[v]);
    int k = 31 - __builtin_clz(v-u+1);
    return min(st[u][k], st[v-(1<<k)+1][k]).second;
}

void dfs(int u, int p, int d) {
    fa[u] = p; dep[u] = d;
    st[dfn[u] = idx++][0] = {d, u};
    for (int v : adj[u]) if (v != p) {
        dfs(v, u, d + 1);
        st[idx++][0] = {d, u};
    }
}

void prep() {
    idx = 0; dfs(root, 0, 0);
    int l = 31 - __builtin_clz(idx);
    rep (j, l) rep (i, 1+idx-(1<<j))
        st[i][j+1] = min(st[i][j], st[i+(1<<j)][j]);
}

vector<int> vadj[MAXN];
bool in[MAXN]; // is original vertex 

struct vtree {
    vector<int> cvs;

    vtree(vector<int> vs) {
        for (int x : vs) in[x] = true;
        vs.push_back(root); // add root for convenience
        sort(range(vs), [] (int u, int v) { return dfn[u] < dfn[v]; });
        vs.erase(unique(range(vs)), vs.end());
        cvs = vs;
        vector<int> s;
        for (int x : vs) {
            if (s.empty()) {
                s.push_back(x);
            } else {
                int z = lca(x, s.back()); 
                while (s.size() > 1 and dep[z] < dep[s.rbegin()[1]]) {
                    int v = s.back(); s.pop_back();
                    vadj[s.back()].push_back(v);
                }
                if (dep[z] < dep[s.back()]) {
                    vadj[z].push_back(s.back());
                    s.pop_back();
                }
                if (s.empty() or s.back() != z) {
                    s.push_back(z);
                    cvs.push_back(z);
                }
                s.push_back(x);
            }
        }
        while (s.size() > 1) {
            int v = s.back(); s.pop_back();
            vadj[s.back()].push_back(v);
        }
    }

    int work(); // solve the subproblem

    ~vtree() {
        for (int x : cvs) { 
            in[x] = false; vadj[x].clear();
            // do extra cleanup here
        }
    }

};  
