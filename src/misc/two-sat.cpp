const int MAXN = 100005;
struct twoSAT {
    int n;
    vector<int> G[MAXN*2];
    bool mark[MAXN*2];
    int S[MAXN*2], c;

    void init(int n) {
        this->n = n;
        for (int i=0; i < n*2; i++) G[i].clear();
        memset(mark, 0, sizeof(mark));
    }

    bool dfs(int x) {
        if (mark[x^1]) return false;
        if (mark[x]) return true;
        mark[x] = true;
        S[c++] = x;
        for (int u : G[x]) if (!dfs(u)) return false;
        return true;
    }

    void add_clause(int x, bool xval, int y, bool yval) {
        x = x * 2 + xval;
        y = y * 2 + yval;
        G[x].push_back(y);
    }

    bool solve() {
        for (int i=0; i<n*2; i+=2) {
            if (!mark[i] && !mark[i+1]) {
                c = 0;
                if (!dfs(i)) {
                    while (c > 0) mark[S[--c]] = false;
                    if (!dfs(i+1)) return false;
                }
            }
        }
        return true;
    }
    
    bool operator[] (int x) { return mark[2*x+1]; }
};
