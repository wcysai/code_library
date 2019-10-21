struct bit_rupq{ // range update, point query
    int N;
    vector<LL> tr;

    void init(int n) { tr.assign(N = n + 5, 0);}

    LL query(int n) {
        LL ans = 0;
        while (n < N) { ans += tr[n]; n += n & -n; }
        return ans;
    }

    void add(int n, LL x) {
        while (n) { tr[n] += x; n &= n - 1; }
    }
};
