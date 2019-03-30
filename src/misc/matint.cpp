struct MatroidOracle {
    MatroidOracle() { /* TODO */ }
    void insert(int x) { /* TODO */ }
    bool test(int x) const { /* TODO */ }
};

const int MAXN = 8192;
template <typename MT1, typename MT2>
struct MatroidIntersection {
    int n;
    bool in[MAXN] = {}, t[MAXN], vis[MAXN];
    int pre[MAXN];
    vector<int> adj[MAXN];
    queue<int> q;

    MatroidIntersection(int n) : n(n) { }
    
    vector<int> getcur() {
        vector<int> ret;
        rep (i, n) if (in[i]) ret.push_back(i);
        return ret;
    }
    
    void enqueue(int x, int p) { 
        if (vis[x]) return; 
        vis[x] = true; pre[x] = p; q.push(x); 
        if (t[x]) throw x;
    };

    vector<int> run() {
        while (true) {
            vector<int> cur = getcur();
            fill(vis, vis + n, 0);
            rep (i, n) adj[i].clear();
            MT2 mt2;
            for (int i : cur) mt2.insert(i);
            rep (i, n) t[i] = mt2.test(i);
            vector<MT1> mt1s(cur.size());
            vector<MT2> mt2s(cur.size());
            rep (i, cur.size()) rep (j, cur.size()) if (i != j) {
                mt1s[i].insert(cur[j]);
                mt2s[i].insert(cur[j]);
            }
            rep (i, n) if (!in[i]) rep (j, cur.size()) {
                if (mt1s[j].test(i)) adj[cur[j]].push_back(i);
                if (mt2s[j].test(i)) adj[i].push_back(cur[j]);
            }
            q = {};
            try {
                MT1 mt1;
                for (int i : cur) mt1.insert(i);
                rep (i, n) if (mt1.test(i)) enqueue(i, -1);
                while (q.size()) {
                    int u = q.front(); q.pop();
                    for (int v : adj[u]) enqueue(v, u);
                }
            } catch (int v) {
                while (v >= 0) { in[v] ^= 1; v = pre[v]; }
                continue;
            }
            break;
        };
        return getcur();
    }
};
