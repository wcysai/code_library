// ~0.1s per 100000 operations @ luogu.org
struct node {
  static int n, pos;

  union {
    struct {
      int value, rank;
    };
    struct {
      node *left, *right;
    };
  };
  
  void* operator new(size_t size);

  static node* build(int l, int r) {
    node* a = new node;
    if (r > l + 1) {
      int mid = (l + r) / 2;
      a->left = build(l, mid);
      a->right = build(mid, r);
    } else {
      a->value = l;
      a->rank = 0;
    }
    return a;
  }

  static node* init(int size) {
    n = size;
    pos = 0;
    return build(0, n);
  }

  node *Update(int l, int r, int pos, node nd) {
    node* a = new node(*this);
    if (r > l + 1) {
      int mid = (l + r) / 2;
      if (pos < mid)
        a->left = left->Update(l, mid, pos, nd);
      else
        a->right = right->Update(mid, r, pos, nd); 
    } else {
      *a = nd;
    }
    return a;
  }

  node *Access(int l, int r, int pos) {
    if (r > l + 1) {
      int mid = (l + r) / 2;
      if (pos < mid) return left->Access(l, mid, pos);
      else return right->Access(mid, r, pos);
    } else {
      return this;
    }
  }

  int find(int x) {
    int fa;
    while ((fa = Access(0, n, x)->value) != x)
      x = fa;
    return x;
  }

  node* unite(int u, int v) {
    u = find(u); v = find(v);
    if (u == v) return this;
    int ru = Access(0, n, u)->rank, rv = Access(0, n, v)->rank;
    if (ru == rv) 
      return Update(0, n, u, {v, ru})->Update(0, n, v, {v, ru+1});
    if (ru > rv) {
      swap(u, v);
      swap(ru, rv);
    }
    return Update(0, n, u, {v, rv});
  }
} nodes[20000000];

int node::n, node::pos;
inline void* node::operator new(size_t size) {
  return nodes + (pos++);
}
