vector<int> berlekamp(const vector<int>& a) {
    vector<int> p = {1}, r = {1};
    int dif = 1;
    rep (i, a.size()) {
        int u = 0;
        rep (j, p.size())
            u = (u + 1ll * p[j] * a[i-j]) % mod;
        if (u == 0) {
            r.insert(r.begin(), 0);
        } else {
            auto op = p;
            p.resize(max(p.size(), r.size() + 1));
            int idif = inv(dif);
            rep (j, r.size()) 
                p[j+1] = 
                    (p[j+1] - 1ll * r[j] * idif % mod * u % mod + mod) % mod;
            dif = u;
            r = op;
        }
    }
    return p;
}
