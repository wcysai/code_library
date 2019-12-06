const ULL WIDTH = 3, MASK = (1 << WIDTH) - 1, CONN = 1;
int n, m;

ULL Get(ULL mask, int digit) {
    return (mask >> (digit * WIDTH)) & MASK;
}

[[gnu::warn_unused_result]]
ULL Set(ULL mask, int digit, ULL val) {
    digit *= WIDTH;
    return (mask & ~(MASK << digit)) | val << digit;
}

[[gnu::warn_unused_result]]
ULL Set(ULL mask, int digit, ULL val1, ULL val2) {
    return mask = Set(mask, digit, val1), Set(mask, digit+1, val2);
}

ULL Canon(ULL mask) {
    ULL repr[1 << WIDTH] = {}, top = CONN;
    rep (i, m + 1) {
        ULL val = Get(mask, i);
        if (val < CONN) continue;
        if (repr[val] == 0) repr[val] = top++;
        mask = Set(mask, i, repr[val]);
    }
    return mask;
}

ULL Unite(LL mask, ULL val1, ULL val2) {
    rep (i, m + 1) if (Get(mask, i) == val1) mask = Set(mask, i, val2);
    return Canon(mask);
}

char g[16][16];
unordered_map<ULL, ULL> dp[16][16];

int main() {
    fgets(g[0], sizeof(g[0]), stdin);
    sscanf(g[0], "%d %d", &n, &m);
    rep (i, n) fgets(g[i], sizeof(g[i]), stdin);
    int lasti = n, lastj;
    while (lasti--) for (lastj = m; lastj; lastj--) 
        if (g[lasti][lastj-1] == '.') goto cont;   
    cont:;
    rep (i, n) {
        if (i) for (auto pr : dp[i-1][m]) {
            ULL mask, val; tie(mask, val) = pr;
            if (Get(mask, m) == 0) dp[i][0][mask << WIDTH] += val;
        } else {
            dp[0][0][0] = 1;
        }
        rep (j, m) for (auto pr : dp[i][j]) {
            ULL mask, val; tie(mask, val) = pr;
            ULL d1 = Get(mask, j), d2 = Get(mask, j + 1);
            if (g[i][j] == '.') {
                if (d1 == 0 and d2 == 0) {
                    dp[i][j+1][Canon(Set(mask, j, MASK, MASK))] += val;
                } else if (d1 == 0 or d2 == 0) {
                    dp[i][j+1][mask] += val;
                    mask = Set(mask, j, d2); mask = Set(mask, j + 1, d1);
                    dp[i][j+1][mask] += val;
                } else {
                    if (d1 == d2 and not (i == lasti and j + 1 == lastj)) 
                        continue;
                    mask = Unite(Set(mask, j, 0, 0), d1, d2); 
                    dp[i][j+1][mask] += val; 
                }
            } else {
                if (d1 == 0 and d2 == 0) dp[i][j+1][mask] += val;
            }
        }
    }
    cout << dp[lasti][lastj][0] << endl;
    return 0;
}
