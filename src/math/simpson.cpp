template <typename T>
double simpson(double l, double r, T&& f) {
    double mid = (l + r) / 2;
    return (f(l) + 4 * f(mid) + f(r)) * (r - l) / 6.0;
}

template <typename T>
double integrate(double l, double r, double eps, double est, T&& f) {
    double mid = (l + r) / 2;
    double lv = simpson(l, mid, f), rv = simpson(mid, r, f);
    if (fabs(lv + rv - est) <= 15.0 * eps) 
        return lv + rv + (lv + rv - est) / 15.0;
    return integrate(l, mid, eps, lv, f) + integrate(mid, r, eps, rv, f);
}

