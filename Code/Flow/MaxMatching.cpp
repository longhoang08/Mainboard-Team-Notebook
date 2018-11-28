bool dfs(int u) {
    if (mx[u] == T) return false;
    mx[u] = T;
    for(int v : ke[u]) {
        if (!my[v] || dfs(my[v])) {
            my[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    For(i,1,n) {
        T++;
        res += dfs(i);
    }
    // choose my & i
}