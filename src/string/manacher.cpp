struct Manacher {
  int Len;
  vector<int> lc;
  string s;

  void work() {
    lc[1] = 1;
    int k = 1;
    
    for (int i = 2; i <= Len; i++) {
      int p = k + lc[k] - 1;
      if (i <= p) {
        lc[i] = min(lc[2 * k - i], p - i + 1);
      } else {
        lc[i] = 1;
      }
      while (s[i + lc[i]] == s[i - lc[i]]) lc[i]++;
      if (i + lc[i] > k + lc[k]) k = i;
    }
  }

  void init(const char *tt) {
    int len = strlen(tt);
    s.resize(len * 2 + 10);
    lc.resize(len * 2 + 10);
    s[0] = '*';
    s[1] = '#';
    for (int i = 0; i < len; i++) {
      s[i * 2 + 2] = tt[i];
      s[i * 2 + 1] = '#';
    }
    s[len * 2 + 1] = '#';
    s[len * 2 + 2] = '\0';
    Len = len * 2 + 2;
    work();
  }

  pair<int, int> maxpal(int l, int r) {
    int center = l + r + 1;
    int rad = lc[center] / 2;
    int rmid = (l + r + 1) / 2;
    int rl = rmid - rad, rr = rmid + rad - 1;
    if ((r ^ l) & 1) {
    } else rr++;
    return {max(l, rl), min(r, rr)};
  }
};
