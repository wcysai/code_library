int n;
int dp[256][256], dc[256][256];

template <typename T>
void compute(T cost) {
  for (int i = 0; i <= n; i++) {
    dp[i][i] = 0;
    dc[i][i] = i;
  }
  rep (i, n) {
    dp[i][i+1] = 0;
    dc[i][i+1] = i;
  }
  for (int len = 2; len <= n; len++) {
    for (int i = 0; i + len <= n; i++) {
      int j = i + len;
      int lbnd = dc[i][j-1], rbnd = dc[i+1][j];
      dp[i][j] = INT_MAX / 2;
      int c = cost(i, j);
      for (int k = lbnd; k <= rbnd; k++) {
        int res = dp[i][k] + dp[k][j] + c;
        if (res < dp[i][j]) {
          dp[i][j] = res;
          dc[i][j] = k;
        }
      }
    }
  }
};

