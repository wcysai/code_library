LL mulmod(LL a, LL b, LL m){
    LL r = 0;
    a %= m; b %= m;
    while(b) {
        if(b & 1) r += a, r %= m;
        b >>= 1;
        if(a < m - a)
            a <<= 1;
        else
            a -= (m - a);
    }
    return r;
}

LL mulmod(LL a, LL b) {
  LL tmp = (a * b - (LL)((long double)a/p*b + 1e-8)*p);
  return tmp < 0 ? tmp + p : tmp;
}
