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

LL legendre(LL a, LL p){
    return powmod(a, (p-1)/2, p);
}

#include <iostream>
using namespace std;

int main(){
    LL a, b;
    while (cin >> a >> b){
        cout << legendre(a, b) << endl;
    }
    return 0;
}
