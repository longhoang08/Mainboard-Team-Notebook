chainHead [c]
dinh dau
cua chuoi
c
    chainInd[u]
chuoi ma
dinh u
nam trong

void hld(int u) {
  //Neu chuoi hien tai chua co dinh dau dinh gan goc nhat thi dat u lam dinh dau cua no
  if (chainHead[nChain] == 0) chainHead[nChain] = u;
  //Gan chuoi hien tai cho u
  chainInd[u] = nChain;
  //Giai thich ben duoi
  posInBase[u] = ++nBase;
  // Bien luu dinh con dac biet
  int mxVtx = -1;
  // Tim dinh con dac biet trong so nhung dinh con cua u
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (v != parent[u]) {
      if (mxVtx == -1 || nChild[v] > nChild[mxVtx]) {
        mxVtx = v;
      }
    }
  }
  //Neu tim ra dinh con dac biet (u khong phai la dinh la) thi di chuyen den dinh do
  if (mxVtx > -1)
    hld(mxVtx);
  // Sau khi di het mot chuoi thi tang nChain len va bat dau mot chuoi moi
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (v != parent[u] && v != mxVtx) {
      nChain++;
      hld(v);
    }
  }
}
void update(int u, int a) {
  // uchain chuoi hien tai cua u
  // achain chuoi hien tai cua a
  int uchain = chainInd[u], achain = chainInd[a];
  while (1) {
    // Neu u va a cung nam tren mot chuoi thi update doan tu u den a va ket thuc
    if (uchain == achain) {
      updateIntervalTree(..., posInBase[a], posInBase[u], ...);
      break;
    }
    // Neu u va a khong nam tren cung mot chuoi thi update doan tu u den dinh dau cua chuoi hien tai
    updateIntervalTree(..., posInBase[chainHead[uchain]], posInBase[u], ...);
    // Nhay len dinh cha cua dinh dau hien tai
    u = parent[chainHead[uchain]];
    uchain = chainInd[u];
  }
}