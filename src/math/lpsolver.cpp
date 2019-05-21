typedef vector<double> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;
const double EPS = 1e-9;

double LPSolve(VVD A, VD b, VD c, VD& x) {
    int m = b.size(), n = c.size();
    VI B(m), N(n+1);
    VVD D(m+2, VD(n+2));
    rep (i, m) rep (j, n) D[i][j] = A[i][j];
    rep (i, m) { B[i] = n + i; D[i][n] = -1; D[i][n+1] = b[i]; }
    rep (j, n) { N[j] = j; D[m][j] = -c[j]; }
    N[n] = -1; D[m+1][n] = 1;

    auto pivot = [&] (int r, int s) {
        double inv = 1.0 / D[r][s];
        rep (i, m+2) if (i != r) rep (j, n+2) if (j != s)
            D[i][j] -= D[r][j] * D[i][s] * inv;
        rep (j, n+2) if (j != s) D[r][j] *= inv;
        rep (i, m+2) if (i != r) D[i][s] *= -inv;
        D[r][s] = inv; swap(B[r], N[s]);
    };

    auto simplex = [&](int phase) {
        int x = m + (phase == 1);
        while (true) {
            int s = -1;
            for (int j = 0; j <= n; j++) {
                if (phase == 2 and N[j] == -1) continue;
                if (s == -1 or D[x][j] < D[x][s] or 
                    D[x][j] == D[x][s] and N[j] < N[s]) s = j;
            }
            if (s < 0 or D[x][s] > -EPS) return true;
            int r = -1;
            for (int i = 0; i < m; i++) {
                if (D[i][s] < EPS) continue;
                if (r == -1 or D[i][n+1] / D[i][s] < D[r][n+1] / D[r][s] or
                    D[i][n+1] / D[i][s] == D[r][n+1] / D[r][s] and 
                    B[i] < B[r]) r = i;
            }
            if (r == -1) return false; else pivot(r, s);
        }
    };

    int r = 0;
    for (int i = 1; i < m; i++) if (D[i][n+1] < D[r][n+1]) r = i;
    if (D[r][n+1] <= -EPS) {
        pivot(r, n);
        if (!simplex(1) or D[m+1][n+1] < -EPS) return NAN;
        rep (i, m) if (B[i] == -1) {
            int s = -1;
            for (int j = 0; j <= n; j++) if (s == -1 or D[i][j] < D[i][s] 
                or D[i][j] == D[i][s] and N[j] < N[s]) s = j;
            pivot(i, s);
        }
    }
    if (!simplex(2)) return DBL_MAX;
    x = VD(n);
    rep (i, m) if (B[i] < n) x[B[i]] = D[i][n+1];
    return D[m][n+1];
}
