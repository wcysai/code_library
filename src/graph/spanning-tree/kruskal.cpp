const int MAXV = 100005;
const int MAXE = 300005;

int n, m;
struct edge{
    int u, v, w;
    bool operator < (const edge& e) const {
        return w < e.w;
    }
} edges[MAXE];

int p[MAXV];
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

void kruskal(){
    init(n);
    sort(edges, edges + m);
    int curn = 1;
    for (int i = 0; curn < n; i++){
        if (unite(edges[i].u, edges[i].v)){
            // choose the i-th edge
            curn++;
        }
    }
}
