class BIT2D {
 public:
  vector<int> nodes[maxn];
  vector<int> f[maxn];
 
  void fakeUpdate(int u, int v) {
    for (int x = u; x <= n; x += x & -x)
      nodes[x].push_back(v);
  }
 
  void fakeGet(int u, int v) {
    for (int x = u; x > 0; x -= x & -x)
      nodes[x].push_back(v);
  }
 
  void update(int u, int v) {
    for (int x = u; x <= n; x += x & -x)
      for (int y = lower_bound(nodes[x].begin(), nodes[x].end(), v) - nodes[x].begin() + 1; y <= nodes[x].size();
           y += y & -y)
        f[x][y]++;
  }
 
  int get(int u, int v) {
    int res = 0;
    for (int x = u; x > 0; x -= x & -x)
      for (int y = upper_bound(nodes[x].begin(), nodes[x].end(), v) - nodes[x].begin(); y > 0; y -= y & -y)
        res += f[x][y];
    return res;
  }
 
  void prepare(vector<pair<int, int>> queries) {
    reverse(queries.begin(), queries.end());
    for (auto query : queries) {
      fakeUpdate(query.first, query.second);
    }
    reverse(queries.begin(), queries.end());
    for (int i = 1; i <= n; i++) {
      nodes[i].push_back(inf);
      sort(nodes[i].begin(), nodes[i].end());
      f[i].resize(((int) nodes[i].size()) + 3);
    }
  }
} bit2D;