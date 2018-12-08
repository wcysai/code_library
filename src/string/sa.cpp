void suffix_array(const int s[], int sa[], int rk[], int n, int m) {
    // size of x, y must be at least n, size of cnt must be at least max(n, m)
    static int x[1000005], y[1000005], cnt[1000005];
    copy(s, s + n, rk);
    iota(y, y + n, 0);
    for (int k = 0; ; k ? (k <<= 1) : (k = 1)) {
        if (k) {
            int t = 0;
            for (int i = n - k; i < n; i++) y[t++] = i;
            rep (i, n) if (sa[i] >= k) y[t++] = sa[i] - k;
        }
        fill(cnt, cnt + m, 0);
        rep (i, n) cnt[rk[i]]++;
        partial_sum(cnt, cnt + m, cnt);
        rep (i, n) x[i] = rk[y[i]];
        for (int i = n - 1; i >= 0; i--) 
            sa[--cnt[x[i]]] = y[i];
        swap_ranges(rk, rk + n, y);
        rk[sa[0]] = m = 0;
        for (int i = 1; i < n; i++) {
            int t1 = sa[i], t2 = sa[i-1];
            rk[t1] = (y[t1] == y[t2] and y[t1 + k] == y[t2 + k]) ? m : ++m;
        }
        if (++m == n) break;
    }
}
