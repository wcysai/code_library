constexpr int BLOCK_SZ = 300;

struct query { int l, r, id; };
vector<query> queries;

void add_query(int id, int l, int r) {
  queries.push_back(query{l, r, id}); 
}

int l, r;

// ----- functions to implement -----
inline void yield(int id);
inline void enter(int o);
inline void leave(int o);

void run() {
    if (queries.empty()) return;
    sort(range(queries), [](query lhs, query rhs) {
        int lb = lhs.l / BLOCK_SZ, rb = rhs.l / BLOCK_SZ;
        if (lb != rb) return lb < rb;
        return lhs.r < rhs.r;
    });
    l = queries[0].l;
    r = queries[0].r;
    for (int i = l; i <= r; i++) enter(i);
    for (query q : queries) {
        while (l > q.l) enter(--l);
        while (r < q.r) enter(++r);
        while (l < q.l) leave(l++);
        while (r > q.r) leave(r--);
        yield(q.id);
    }
}
