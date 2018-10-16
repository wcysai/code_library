const int MAXN = 108;

int n;
LL adj[MAXN][MAXN]; // indexed from 1

int prev[MAXN]; // note that, prev[src] = 0
bool done[MAXN];
LL key[MAXN]; // key[v] = adj[prev[v]][v] for v != src when done
void prim(int src){
    Rep (i, n)
        key[i] = LLONG_MAX, done[i] = false;
    key[src] = 0, prev[src] = 0;
    rep (cnt, n){
        LL u, k = LLONG_MAX;
        Rep (i, n)
            if (!done[i] && key[i] < k)
                u = i, k = key[i];
        done[u] = true;
        Rep (v, n)
            if (!done[v] && adj[u][v] < key[v])
                prev[v] = u, key[v] = adj[u][v];
    }
}
