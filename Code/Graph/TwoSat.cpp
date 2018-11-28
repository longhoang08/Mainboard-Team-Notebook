int n, m, g[maxn];
bool cx[maxn];
vector <int> listV, ke[maxn], K[maxn];

int cal(int x) {
    if (x%2 == 0) return x - 1;
    else return x + 1;
}

void add(int u, int v) {
    ke[u].pb(v);
    K[v].pb(u);
}

void dfs(int u) {
    cx[u] = true;
    for(int v : ke[u])
        if (!cx[v]) dfs(v);
    listV.pb(u);
}

void dfs(int u, int x) {
    g[u] = x;
    for(int v : K[u])
        if (g[v] == 0) dfs(v,x);
}

int main() {
    cin >> m >> n;
    n += n;
    For(i,1,m) {
        int u, v;
        cin >> u >> v;
        u *= 2;
        v *= 2;
        if (u < 0) u = cal(abs(u));
        if (v < 0) v = cal(abs(v));
        add(cal(u),v);
        add(cal(v),u);
    }
    listV.pb(0);
    For(i,1,n)
    if (!cx[i]) dfs(i);
    int ng = 0;
    Ford(i,n,1) {
        int u = listV[i];
        if (g[u] == 0) dfs(u,++ng);
    }
    for(int i = 2; i <= n; i += 2)
        if (g[i] == g[i-1]) NO;
    YES;
    vector <int> result;
    for(int i = 2; i <= n; i += 2)
        if (g[i] > g[i-1]) result.pb(i>>1);
}
