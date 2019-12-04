struct SuffixAutomaton {
    vector<map<char,int>> edges; // edges[i]  : the labeled edges from node i
    vector<int> link;            // link[i]   : the parent of i
    vector<int> length;          // length[i] : the length of the longest string in the ith class
    int last;                    // the index of the equivalence class of the whole string
    SuffixAutomaton(string s) {
        edges.push_back(map<char,int>());
        link.push_back(-1);
        length.push_back(0);
        last = 0;
        for(int i=0;i<s.size();i++) {
            edges.push_back(map<char,int>());
            length.push_back(i+1);
            link.push_back(0);
            int r = edges.size() - 1;
            int p = last;
            while(p >= 0 && edges[p].find(s[i]) == edges[p].end()) {
                edges[p][s[i]] = r;
                p = link[p];
            }
            if(p != -1) {
                int q = edges[p][s[i]];
                if(length[p] + 1 == length[q]) {
                    link[r] = q;
                } else {
                    edges.push_back(edges[q]);
                    length.push_back(length[p] + 1);
                    link.push_back(link[q]);
                    int qq = edges.size()-1;
                    link[q] = qq;
                    link[r] = qq;
                    while(p >= 0 && edges[p][s[i]] == q) {
                        edges[p][s[i]] = qq;
                        p = link[p];
                    }
                }
            }
            last = r;
        }
    }
};