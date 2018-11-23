vector<int> adj[100005];
int sz[100005], sum;

void getsz(int u, int p) {
  sz[u] = 1; sum++;
  for (int v : adj[u]) {
    if (v == p) continue;
    getsz(v, u);
    sz[u] += sz[v];
  }
}

int getcent(int u, int p) {
  for (int v : adj[u]) 
    if (v != p and sz[v] > sum / 2)
      return getcent(v, u);
  return u;
}

void decompose(int u, int p) {
  sum = 0; getsz(u, p);
  int c = getcent(u, p);
  
  for (int v : adj[c]) { 
    // get answer for subtree v
  }
  // get answer for the whole tree

  for (int v : adj[c]) {
    adj[v].erase(find(range(adj[v]), c));
    decompose(v, c);
    adj[v].push_back(c); // restore deleted edge
  }
}

