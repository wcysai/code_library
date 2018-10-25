const int SIZE = 10005;
int fail[SIZE];
int len;

void construct(const char* p) {
  len = strlen(p);
  fail[0] = fail[1] = 0;
  for (int i = 1; i < len; i++) {
    int j = fail[i];
    while (j && p[i] != p[j]) j = fail[j];
    fail[i + 1] = p[i] == p[j] ? j + 1 : 0;
  }
}

inline void found(int pos) {
  // ! add codes for having found at pos
}

void match(const char* t, const char* p) {  // must be called after construct
  int n = strlen(t);
  int j = 0;
  rep(i, n) {
    while (j && p[j] != t[i]) j = fail[j];
    if (p[j] == t[i]) j++;
    if (j == len) found(i - len + 1);
  }
}
