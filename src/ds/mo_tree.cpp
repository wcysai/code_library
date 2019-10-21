const int MAXN = 200005, BLOCK = 300;
int n, m;
vector<int> adj[MAXN];
int en[MAXN], edx;
int dep[MAXN], fa[MAXN];
bool in[MAXN];

inline void deal(int u) {
    if (in[u] ^= 1) {
        // enter
    } else {
        // leave
    }
}

void moveto(int a, int b) {
    if (a == b) return;
    int cross = in[b] ? b : 0;
    auto moveup = [&] (int &x) {
        if (!cross) {
            if (in[x] and !in[fa[x]]) cross = x;
            else if (in[fa[x]] and !in[x]) cross = fa[x];
        }
        deal(x); x = fa[x];
    };
    while (dep[a] > dep[b]) moveup(a);
    while (dep[b] > dep[a]) moveup(b);
    while (a != b) moveup(a), moveup(b);
    deal(a); if (cross) deal(cross);
}

void dfs(int u, int p) {
    en[u] = edx++; fa[u] = p;
    for (int v : adj[u]) if (v != p) {
        dep[v] = dep[u] + 1;
        dfs(v, u); edx++;
    }
}

struct query {
    int l, r, id;
    void yield() { /* TODO */}
};
vector<query> qs;

void run() {
    dfs(1, 0);

    sort(range(qs), [] (query lhs, query rhs) {
        int u0 = en[lhs.l], v0 = en[rhs.l];
        int bl = u0 / BLOCK, br = v0 / BLOCK;
        if (bl != br) return bl < br;
        int u1 = en[lhs.r], v1 = en[rhs.r];
        return bl & 1 ? u1 < v1 : u1 > v1;
    });

    int l = 1, r = 1; deal(1);
    for (auto& q : qs) {
        moveto(l, q.l); l = q.l;
        moveto(r, q.r); r = q.r;
        q.yield();
    }
}
