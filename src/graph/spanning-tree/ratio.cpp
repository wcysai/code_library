double k;
struct edge{
    int u, v;
    double cost, dist;
    double w(return cost - dist * w);
    bool operator < (const edge& rhs) const {
        return w() < rhs.w();
    }
};

double mst(){
    // return sum(dist[e])/sum(cost[e]) for all e in mst
}

double solve(){
    k = 1e5; // initial k estimate
    double nxt;
    while (fabs((nxt = mst()) - k)) > 1e-8){ // admissible error
        k = nxt;
    }
    return k;
}
