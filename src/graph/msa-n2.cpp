struct MDST {
    int V;
    LL heap[MAXN][MAXN];
    LL shift[MAXN];
    int fa[MAXN], vis[MAXN];

    void init(int n) {
        V = n;
        Rep (i, n) Rep (j, n) heap[i][j] = LLONG_MAX / 2;
    }

    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

    void unite(int x, int y) {
        x = find(x); y = find(y); fa[y] = x; if (x == y) return ;
        Rep (i, V) heap[x][i] = min(heap[x][i], heap[y][i] - shift[y] + shift[x]);
    }

    void add_edge(int u, int v, LL w) { heap[v][u] = min(heap[v][u], w); }

    LL run(int n, int rt) {
        V = n;
        LL ans = 0;
        iota(fa, fa + n + 1, 0);
        Rep (i, n) if (find(i) != find(rt)) {
            int u = find(i);
            stack<int, vector<int>> s;
            while (find(u) != find(rt)) {
                if (vis[u]) while (s.top() != u) {
                    vis[s.top()] = 0; unite(u, s.top()); s.pop();
                } else { vis[u] = 1; s.push(u); }

                Rep (i, V) if (find(i) == u) heap[u][i] = LLONG_MAX / 2;
                
                auto ptr = min_element(heap[u] + 1, heap[u] + V + 1);
                if (*ptr == LLONG_MAX / 2) return LLONG_MIN;
                ans += *ptr - shift[u];
                shift[u] = *ptr;

                u = ptr - heap[u];
            }
            while (s.size()) { vis[s.top()] = 0; unite(rt, s.top()); s.pop(); }
        }
        return ans;
    }
};
