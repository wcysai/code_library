const int MAXX = 1e7+5;
int phi[MAXX];
int prime[MAXX], sz;

void sieve(){
    phi[1] = 1;
    for (int i = 2; i < MAXX; i++){
        if (!phi[i]) phi[i] = i-1, prime[sz++] = i;
        for (int j = 0; j < sz && i*prime[j] < MAXX; j++){
            if (i % prime[j] == 0) {
                phi[i*prime[j]] = phi[i]*prime[j];
                break;
            }
            phi[i*prime[j]] = phi[i]*(prime[j] - 1);
        }
    }
}
