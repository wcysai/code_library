const LL INF = LLONG_MAX / 2;
const int MAXV = 1005;
int V;
LL d[MAXV][MAXV];

void init(){
    Rep (i, V){
        Rep (j, V) d[i][j] = INF;
        d[i][i] = 0;
    }
}

void floyd(){
    Rep (k, V)
        Rep (i, V)
            Rep (j, V)
                // ! (*) if (d[i][k] < INF && d[k][j] < INF)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

