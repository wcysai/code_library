typedef vector<int> perm;

perm operator * (const perm lhs, const perm rhs){
    int sz;
    assert((sz = lhs.size()) == rhs.size());
    perm res(sz);
    rep (i, sz) res[i] = rhs[lhs[i]];
    return res;
}

perm operator ~ (const perm lhs){
    int sz = lhs.size();
    perm res(sz);
    rep (i, sz) res[lhs[i]] = i;
    return res;
}

struct permutation{
    int size;
    vector<vector<int>> orbits;

    permutation(perm p){
        size = p.size();
        vector<bool> visited(size);
        rep (i, size) {
            if (visited[i]) continue;
            int cur = i;
            vector<int> orbit;
            while (!visited[cur]){
                visited[cur] = true;
                orbit.push_back(cur);
                cur = p[cur];
            }
            orbits.push_back(move(orbit));
        }
    }
};
