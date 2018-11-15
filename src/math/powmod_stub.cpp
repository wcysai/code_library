#include <iostream>
using namespace std;

typedef long long LL;

LL powmod(LL b, LL e, LL m){
    LL r = 1;
    while (e){
        if (e & 1) r = r * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return r;
}


int main(){
    LL a, b, c;
    cin >> a >> b >> c;
    cout << a << '^' << b << " mod " << c << '=' << powmod(a,b,c) << endl;
    return 0;
}
