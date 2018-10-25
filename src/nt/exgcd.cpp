void exgcd(int a, int b, int &g, int &x, int &y){
    if (!b) g = a, x = 1, y = 0;
    else {
        exgcd(b, a % b, g, y, x),
        y -= x * (a / b);
    }
}
