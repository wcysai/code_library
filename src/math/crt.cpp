void exgcd(LL a, LL b, LL &g, LL &x, LL &y) {
    if (!b) g = a, x = 1, y = 0;
    else {
        exgcd(b, a % b, g, y, x);
        y -= x * (a / b);
    }
}

LL crt(LL r[], LL p[], int n) {
	LL q = 1, ret = 0;
	rep (i, n) q *= p[i];
	rep (i, n) {	
        LL m = q / p[i];
        LL d, x, y;
		exgcd(p[i], m, d, x, y);
		ret = (ret + y * m * r[i]) % q;
	}
	return (q + ret) % q;
}
