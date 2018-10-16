#include <iostream>
#include <cassert>
using namespace std;

typedef long long LL;

inline LL mathmod(LL a, LL b){
    return (a%b+b)%b;
}

void exgcd(LL a, LL b, LL &g, LL &x, LL &y){
    if (!b) g = a, x = 1, y = 0;
    else exgcd(b, a % b, g, y, x), y -= x * (a / b);
}


int main(){
    LL a, b, g, x, y;
    cin >> a >> b;
    exgcd(a, b, g, x, y);
    assert(g==1);
    cout << mathmod(x, b);
    return 0;
}
