struct AC : Trie {
  int fail[MAXN];
  int last[MAXN];

  void construct() {
    queue<int> q;
    fail[0] = 0;
    rep(c, CHARN) {
      if (int u = tr[0][c]) {
        fail[u] = 0;
        q.push(u);
        last[u] = 0;
      }
    }
    while (!q.empty()) {
      int r = q.front();
      q.pop();
      rep(c, CHARN) {
        int u = tr[r][c];
        if (!u) {
          tr[r][c] = tr[fail[r]][c];
          continue;
        }
        q.push(u);
        int v = fail[r];
        while (v && !tr[v][c]) v = fail[v];
        fail[u] = tr[v][c];
        last[u] = tag[fail[u]] ? fail[u] : last[fail[u]];
      }
    }
  }

  void found(int pos, int j) {
    if (j) {
      // ! add codes for having found word with tag[j]
      found(pos, last[j]);
    }
  }

  void find(const char* text) {  // must be called after construct()
    int p = 0, c, len = strlen(text);
    rep(i, len) {
      c = id(text[i]);
      p = tr[p][c];
      if (tag[p])
        found(i, p);
      else if (last[p])
        found(i, last[p]);
    }
  }
};
