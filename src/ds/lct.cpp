// about 0.13s per 100k ops @luogu.org

namespace LCT {
  const int MAXN = 300005;
  int fa[MAXN], ch[MAXN][2], val[MAXN], sum[MAXN];
  bool rev[MAXN];

  bool isroot(int x) {
    return ch[fa[x]][0] == x || ch[fa[x]][1] == x;
  }

  void pull(int x) {
    sum[x] = val[x] ^ sum[ch[x][0]] ^ sum[ch[x][1]];
  }

  void reverse(int x) {
    swap(ch[x][0], ch[x][1]);
    rev[x] ^= 1;
  }

  void push(int x) {
    if (rev[x]) {
      if (ch[x][0]) reverse(ch[x][0]);
      if (ch[x][1]) reverse(ch[x][1]);
      rev[x] = 0;
    }
  }

  void rotate(int x) {
    int y = fa[x], z = fa[y], k = ch[y][1] == x, w = ch[x][!k];
    if (isroot(y)) ch[z][ch[z][1] == y] = x;
    ch[x][!k] = y; ch[y][k] = w;
    if (w) fa[w] = y;
    fa[y] = x; fa[x] = z;
    pull(y);
  }

  void pushall(int x) {
    if (isroot(x)) pushall(fa[x]);
    push(x);
  }

  void splay(int x) {
    int y = x, z = 0;
    pushall(y);
    while (isroot(x)) {
      y = fa[x]; z = fa[y];
      if (isroot(y)) rotate((ch[y][0] == x) ^ (ch[z][0] == y) ? x : y);
      rotate(x);
    }
    pull(x);
  }

  void access(int x) {
    int z = x;
    for (int y = 0; x; x = fa[y = x]) {
      splay(x);
      ch[x][1] = y;
      pull(x);
    }
    splay(z);
  }

  void chroot(int x) {
    access(x); 
    reverse(x);
  }

  void split(int x, int y) {
    chroot(x); 
    access(y);
  }

  int Root(int x) {
    access(x);
    while (ch[x][0]) {
      push(x);
      x = ch[x][0];
    }
    splay(x);
    return x;
  }

  void Link(int u, int v) {  // assume unconnected before
    chroot(u);
    fa[u] = v;
  }

  void Cut(int u, int v) {  // assume connected before
    split(u, v);
    fa[u] = ch[v][0] = 0;
    pull(v);
  }

  int Query(int u, int v) {
    split(u, v);
    return sum[v];
  }

  void Update(int u, int x) {
    splay(u);
    val[u] = x;
  }
};
