void findCentroid(int u, int par, int Size) {
  nChild[u] = 1;
  bool pre = true;
  for (int i = 0; i < a[u].size(); i++) {
    int v = a[u][i];
    if (v != par && ok[v]) {
      findCentroid(v, u, Size);
      if (nChild[v] > Size / 2) pre = false;
      nChild[u] += nChild[v];
    }
  }
  if (pre && nChild[u] >= Size / 2)
    centroid = u;
}