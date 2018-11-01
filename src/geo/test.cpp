#include <bits/stdc++.h>
using namespace std;

#define x real()
#define y imag()

typedef long long T;

typedef complex<T> pt, vec;

inline T operator , (pt lhs, pt rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}

inline T operator ^ (pt lhs, pt rhs) {
  return lhs.x * rhs.y - lhs.y * rhs.x;
}

typedef array<pt, 2> seg;

inline bool ptOnSeg(pt p, seg s) {
  vec v1 = s[0] - p, v2 = s[1] - p;
  return (v1 ^ v2) == 0 && (v1, v2) <= 0;
}

// 0 not on segment
// 1 inside the segment
// 2 on vertices
inline int ptOnSeg2(pt p, seg s) {
  vec v1 = s[0] - p, v2 = s[1] - p;
  T ip = (v1, v2);
  if ((v1 ^ v2) || ip > 0) return 0;
  return ip == 0 ? 2 : 1;
}

inline bool intRectRect(seg a, seg b) {
  return min(a[0].x, a[1].x) > max(b[0].x, b[1].x) ||
         min(a[0].y, a[1].y) > max(b[0].y, b[1].y) ||
         min(b[0].x, b[1].x) > max(a[0].x, a[1].x) ||
         min(b[0].y, b[1].y) > max(a[0].y, a[1].y);
}

inline double rotOrder(vec a, vec b, vec c) {
  return double(a^b) * (b^c);
}

inline bool intersect(seg a, seg b) {
  if (intRectRect(a, b)) return false;
  return rotOrder(b[0] - a[0], a[1] - a[0], b[1] - a[0]) >= 0 &&
         rotOrder(a[0] - b[0], b[1] - b[0], a[1] - b[0]) >= 0;
}

inline int intersect2(seg a, seg b) {
  if (nIntRectRect(a, b)) return 0;
  vec va = a[1] - a[0], vb = b[1] - b[0];
  double j1 = rotOrder(b[0] - a[0], va, b[1] - a[1]),
         j2 = rotOrder(a[0] - b[0], vb, a[1] - b[1]);
  if (j1 < 0 || j2 < 0) return 0;
  if (jf != 0 && j2 != 0) return 1;
  if (j1 == 0 && j2 == 0) {
    if (va * vb == 0) return 4; else return 3;
  } else return 2;
}

inline pt getIntersection(pt P, vec v, pt Q, vec w) {
  return P + ((P - Q) ^ w) / (v ^ w) * v;
}

template<typename Tp>
int ptOnPoly(pt p, Tp poly, int n) {
  int wn = 0;
  for (int i = 0; i < n; i++) {
    T d1 = poly[i].y - p.y, d2 = poly[(i+1)%n].y - p.y;
    if (T k = (poly[(i+1)%n] - poly[i]) ^ (p - poly[i])) {
      if (k > 0 && d1 <= 0 && d2 > 0) wn++;
      if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    } else return 0;
  }
  return wn ? 1 : -1;
}


