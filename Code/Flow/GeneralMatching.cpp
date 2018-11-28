class MatchingGraph {
public:
    vector <vector<int> > adj;
    vector <bool> blossom;
    vector <int> parent;
    vector <int> base;
    vector <int> match;
    int n;
    MatchingGraph() {
        n = 0;
    }
    void addEdge(int x, int y) {
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    void clearGraph() {
        int i;
        for (i=0; i<SZ(adj); ++i)
            adj[i].clear();
        fill(blossom.begin(),blossom.end(),false);
        fill(parent.begin(),parent.end(),-1);
        for (i=0; i<n; ++i)
            base[i] = i;
        for (i=0; i<n; ++i)
            match[i] = -1;
    }
    void setN(int newn) {
        n = newn;
        adj.resize(n);
        blossom.resize(n);
        base.resize(n);
        match.resize(n);
        parent.resize(n);
        clearGraph();
    }
    int lca(int x, int y) {
        vector <bool> fy;
        fy.resize(n);
        fill(fy.begin(),fy.end(),false);
        while (true) {
            x = base[x];
            fy[x] = true;
            if (match[x] == -1)
                break;
            x = parent[match[x]];
        }
        while (true) {
            y = base[y];
            if (fy[y])
                return y;
            y = parent[match[y]];
        }
        return -1;
    }
    void path(int now, int child, int curbase) {
        while (base[now] != curbase) {
            blossom[base[now]] = blossom[base[match[now]]] = true;
            parent[now] = child;
            child = match[now];
            now = parent[match[now]];
        }
    }
    int augmentPath(int x) {
        int i,j;
        for (i=0; i<n; ++i)
            base[i] = i;
        for (i=0; i<n; ++i)
            parent[i] = -1;
        queue <int> bfs;
        vector <bool> sudah;
        sudah.resize(n);
        fill(sudah.begin(),sudah.end(),false);
        sudah[x] = true;
        bfs.push(x);
        while (!bfs.empty()) {
            int now = bfs.front();
            bfs.pop();
            for (i=0; i<SZ(adj[now]); ++i) {
                int next = adj[now][i];
                if (base[next]==base[now] || match[next] == now);
                else if (next == x || (match[next]!=-1 &&
                                       parent[match[next]]!=-1)) {
                    int curbase = lca(now,next);
                    fill(blossom.begin(),blossom.end(),false);
                    path(now,next,curbase);
                    path(next,now,curbase);
                    for (j = 0; j < n; ++j)
                        if (blossom[j]) {
                            base[j] = curbase;
                            if (!sudah[j]) {
                                sudah[j] = true;
                                bfs.push(j);
                            }
                        }
                } else if (parent[next]==-1) {
                    parent[next] = now;
                    if (match[next] == -1)
                        return next;
                    sudah[match[next]] = true;
                    bfs.push(match[next]);
                }
            }
        }
        return -1;
    }
    int edmondsMatch() {
        int i;
        int res = 0;
        for (i=0; i<n; ++i) {
            if (match[i]==-1) {
                int x = augmentPath(i);
                while (x>=0) {
                    int p = parent[x];
                    int pp = match[p];
                    match[x] = p;
                    match[p] = x;
                    x = pp;
                }
            }
        }
        for (i=0; i<n; ++i)
            if (match[i]!=-1)
                ++res;
        return res >> 1;
    }
};
