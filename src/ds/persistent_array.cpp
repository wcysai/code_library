struct node {
  static int n, pos;

  union {
    int value;
    struct {
      node *left, *right;
    };
  };
  
  void* operator new(size_t size);

  static node* build(int l, int r, int* il) {
    node* a = new node;
    if (r > l + 1) {
      int mid = (l + r) / 2;
      a->left = build(l, mid, il);
      a->right = build(mid, r, il);
    } else {
      a->value = il[l];
    }
    return a;
  }

  static node* init(int size, int* il) {
    n = size;
    pos = 0;
    return build(0, n, il);
  }

  node *Update(int l, int r, int pos, int val) const {
    node* a = new node(*this);
    if (r > l + 1) {
      int mid = (l + r) / 2;
      if (pos < mid)
        a->left = left->Update(l, mid, pos, val);
      else
        a->right = right->Update(mid, r, pos, val); 
    } else {
      a->value = val;
    }
    return a;
  }

  int Access(int l, int r, int pos) const {
    if (r > l + 1) {
      int mid = (l + r) / 2;
      if (pos < mid) return left->Access(l, mid, pos);
      else return right->Access(mid, r, pos);
    } else {
      return value;
    }
  }

  int access(int index) {
    return Access(0, n, index);
  }

  node *update(int index, int val) {
    return Update(0, n, index, val);
  }
} nodes[30000000];

int node::n, node::pos;
inline void* node::operator new(size_t size) {
  return nodes + (pos++);
}
