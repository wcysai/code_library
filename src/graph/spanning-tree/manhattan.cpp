int V = 0;
struct pt{int id, x, y;};
typedef vector<pt>::iterator vit;
vector<pt> pts;

struct edge{
    int u, v, w;
    bool operator < (const edge& e) const {return w < e.w;}
};
vector<edge> edges;

struct BIT{
    inline int lowbit(int x) {return x&-x;}
    int N;
    vector<int> tr;
    vector<int> minv;

    BIT(int n){
        tr.resize(N = n + 5);
        minv.resize(N);
        fill(range(tr), INT_MAX);
    }

    int prefmin(int n, int& x){
        LL ans = INT_MAX;
        int v = 0;
        while (n){
            if (tr[n] < ans) ans = tr[n]; v = minv[n];
            n -= lowbit(n);
        }
        x = ans;
        return v;
    }

    void insert(int n, int v, int x){
        while (n < N){
            if (tr[n] > x) tr[n] = x, minv[n] = v;
            n += lowbit(n);
        }
    }
};

struct CMP{
    inline bool operator ()(const pt& lhs, const pt& rhs){
        if (lhs.x == rhs.x) return lhs.y > rhs.y;
        return lhs.x > rhs.x;
    }
} cmp;

const int DIFF = 1020; // ! DIFF > max(x_i, y_i); discretize when necessary
void make_edge(){
    sort(range(pts), cmp);
    BIT bit(DIFF * 2);
    for (vit it = pts.begin(); it != pts.end(); it++){
        int vxy;
        int v = bit.prefmin(it->x - it->y + DIFF, vxy);
        if (v) edges.push_back(edge{it->id, v, vxy - it->x - it->y});
        bit.insert(it->x - it->y + DIFF, it->id, it->x + it->y);
    }
}

struct UFS{
    int p[10005];
    void init(int num){
        for (int i=1; i<=num; i++) p[i] = i;
    }

    int parent(int x){
        if (p[x] == x) return x;
        return p[x] = parent(p[x]);
    }

    bool unite(int u, int v){
        u = parent(u); v = parent(v);
        p[u] = v; return u != v;
    }
} ufs;

void kruskal(){
    ufs.init(V);
    sort(range(edges));
    int curn = 1;
    for (int i = 0; curn < V; i++){
        if (ufs.unite(edges[i].u, edges[i].v)){
            // choose the i-th edge
            curn++;
        }
    }
}

inline void add_point(int x, int y){pts.push_back(pt {++V, x, y});}

void Manhattan_MST(){
    make_edge();
    for (vit it = pts.begin(); it != pts.end(); it++) swap(it->x, it->y);
    make_edge();
    for (vit it = pts.begin(); it != pts.end(); it++) it->x = -it->x;
    make_edge();
    for (vit it = pts.begin(); it != pts.end(); it++) swap(it->x, it->y);
    make_edge();
    // restore original coordinates
    // for (vit it = pts.begin(); it != pts.end(); it++) it->y = -it->y;
    kruskal();
}
