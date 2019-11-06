namespace TreeISO {
typedef vector<vector<int>> vvi;
typedef vector<int> vi;
typedef pair<vi, int> pvii;
const int MAXN = 4010;
#define ii pair<int, int>
int N;
vvi edges[2], levels[2];
int ts[MAXN], label[2][MAXN], parent[2][MAXN];
vi centroid[2];
int findCentroid(const int tID, const int u, const int p) {
  int children = 0, curr;
  for (auto &e : edges[tID][u]) {
    if (e != p) {
      curr = findCentroid(tID, e, u);
      if (curr > (N >> 1))
        break;
      children += curr;
    }//if
  }//for
  if (N - children - 1 <= (N >> 1))
    centroid[tID].push_back(u);
  return ts[u] = children + 1;
}//findCentroid
int setLevels(const int tID, const int u, const int p, const int d) {
  parent[tID][u] = p;
  levels[tID][d].push_back(u);
  int mx = d;
  for (auto &e : edges[tID][u])
    if (e != p)
      mx = max(mx, setLevels(tID, e, u, d + 1));
  return mx;
}//setLevels
bool isoCheck(const int lvl) {
  for (int it = lvl; it >= 0; it--) {
    vector<pvii> order[2];
    for (int i = 0; i < 2; i++) {
      for (auto &u : levels[i][it]) {
        order[i].push_back(pvii(vi(), u));
        for (auto &e : edges[i][u])
          if (e != parent[i][u])
            order[i].back().first.push_back(label[i][e]);
      }//for
    }//for
    if ((int) order[0].size() != ((int) order[1].size()))
      return 0;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < (int) order[0].size(); j++)
        sort(order[i][j].first.begin(), order[i][j].first.end());
      sort(order[i].begin(), order[i].end());
    }//for
    int labelID = 0;
    for (int i = 0; i < (int) order[0].size(); i++) {
      if (order[0][i].first != order[1][i].first)
        return 0;
      if (i && order[0][i].first == order[0][i - 1].first) {
        label[0][order[0][i].second] = label[1][order[1][i].second] = labelID;
        continue;
      }//if
      label[0][order[0][i].second] = label[1][order[1][i].second] = ++labelID;
    }//for
  }//for
  return 1;
}//isoCheck
int checkISO(int _N, vector<ii> _edges) {
  N = _N;
  int u, v;
  int T = 1;
  while (T--) {
    int cur = 0;
    memset(ts, 0, sizeof(int) * (N + 2));
    for (int i = 0; i < 2; i++) {
      edges[i].assign(N + 5, vi());
      levels[i].assign(N + 5, vi());
      memset(label[i], 0, sizeof(int) * (N + 2));
      memset(parent[i], 0, sizeof(int) * (N + 2));
      centroid[i].clear();
      for (int j = 0; j < N - 1; j++) {
        int u = _edges[cur].first;
        int v = _edges[cur].second;
        cur++;
        edges[i][u].push_back(v);
        edges[i][v].push_back(u);
      }//for
      findCentroid(i, edges[i][0].empty() ? 1 : 0, -1);
    }//for
    if (edges[0][0].empty())
      N++;
    if ((int) centroid[0].size() != (int) centroid[1].size()) {
      return 0;
    }//if
    if ((int) centroid[0].size() == 2) {
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          edges[i][centroid[i][j]].erase(std::remove(edges[i][centroid[i][j]].begin(),
                                                     edges[i][centroid[i][j]].end(),
                                                     centroid[i][!j]), edges[i][centroid[i][j]].end());
          edges[i][centroid[i][j]].push_back(N);
          edges[i][N].push_back(centroid[i][j]);
        }//for
        centroid[i][0] = N;
      }//for
    }//if
    int d[2];
    for (int i = 0; i < 2; i++)
      d[i] = setLevels(i, centroid[i][0], -1, 0);
    if (d[0] != d[1]) {
      return 0;
    }//if
    if (d[0] >= 0)
      return isoCheck(d[0] - 1) ? 1 : 0;
  }//while
  return 0;
}//main
}
