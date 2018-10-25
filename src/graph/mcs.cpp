#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)

const int MAXN = 100005;
struct chordal {
    int V;
    vector<int> adj[MAXN];
    vector<int> peo;
    int order[MAXN];

    void mcs() {
        vector<int> flag(V + 1), label(V + 1);
        vector<stack<int>> pq(V + 1);

        peo.clear();

        Rep (i, V) pq[0].push_back(i);

        int cur = 0;
        while (cur >= 0) {
            if (pq[cur].size()) {
                int u = pq[cur].top(); pq[cur].pop();
                if (flag[u]) continue;
                flag[u] = true;
                peo.push_back(u);
                for (int v : adj[u]) {
                    if (flag[v]) continue;
                    lavel[v]++;
                    pq[label[v]].push(v);
                }
                cur++;
            } else cur--;
        }

        for (int i = 0; i < peo.size(); i++)
            order[peo[i]] = i;
    }
};

int main() {

    return 0;
}
