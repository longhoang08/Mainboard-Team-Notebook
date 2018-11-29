/**
 * Problem' s query: insert a[i] after a[j]
 */
struct node {
    node *par, *left, *right;
    int value, cnt;
};
int n, Q, tree[N];
node *root, *nilT;
void calc(node *x) {
    if (x != nilT)
        x->cnt = x->left->cnt + x->right->cnt + 1;
}

node *FindPosition(node *cur, int pos) {
    node *x = cur;
    while (x != nilT) {
        int ord = x->left->cnt + 1;
        if (ord == pos)
            return x;
        if (ord > pos)
            x = x->left;
        else
            x = x->right, pos -= ord;
    }
    return nilT;
}
void SetL(node *parent, node *child) {
    if (child != nilT)
        child->par = parent;
    if (parent != nilT)
        parent->left = child;
}
void SetR(node *parent, node *child) {
    if (child != nilT)
        child->par = parent;
    if (parent != nilT)
        parent->right = child;
}
void Uptree(node *x) {
    if (x == root)
        return;
    node *y = x->par, *z = y->par;
    if (y->left == x) {
        SetL(y, x->right);
        SetR(x, y);
    } else {
        SetR(y, x->left);
        SetL(x, y);
    }
    if (z == nilT)
        root = x, x->par = nilT;
    else if (z->left == y)
        SetL(z, x);
    else
        SetR(z, x);
    calc(y);
    calc(x);
}
void Splay(node *x) {
    while (1) {
        node *y = x->par;
        if (y == nilT)
            break;
        node *z = y->par;
        if (z != nilT) {
            if ((y == z->left) == (y->left == x))
                Uptree(y);
            else
                Uptree(x);
        }
        Uptree(x);
    }
    root = x;
}
void Split(node *r, int i, node *&r1, node *&r2) {
    if (i == 0) {
        r1 = nilT, r2 = r;
        return;
    }
    node *x = FindPosition(r, i);
    Splay(x);
    r2 = x->right;
    r1 = x;
    r1->right = nilT;
    calc(r1), calc(r2);
}
node *Join(node *r1, node *r2) {
    if (r1 == nilT)
        return r2;
    while (r1->right != nilT)
        r1 = r1->right;
    Splay(r1);
    SetR(r1, r2);
    calc(r1);
    return r1;
}
void Insert(int i, int val) {
    node *x = new node;
    x->value = val;
    x->par = nilT;
    node *r1, *r2;
    Split(root, i - 1, r1, r2);
    SetL(x, r1), SetR(x, r2);
    calc(x);
    root = x;
}

void Delete(int i) {
    node *x = FindPosition(root, i);
    Splay(x);
    node *r1 = x->left, *r2 = x->right;
    r1->par = nilT; r2->par = nilT;
    delete x;
    root = Join(r1, r2);
}
vector<int> arr;
void GetArray(node *x) {
    if (x == nilT)
        return;
    GetArray(x->left);
    arr.push_back(x->value);
    GetArray(x->right);
    delete x;
}

int main() {
    nilT = new node;
    nilT->value = nilT->cnt = 0;
    nilT->left = nilT->right = nilT->par = nilT;
    root = new node;
    root->value = root->cnt = 1;
    root->left = root->right = root->par = nilT;
    cin >> n >> Q;
    for (int i = 2; i <= n; i++)
        Insert(i, i);
    for (int i = 1; i <= Q; i++) {
        cin >> u >> v;
        int val = FindPosition(root, u)->value;
        Delete(u);
        Insert(v, val);
    }
    GetArray(root);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int F = 1;
        for (int x = arr[i]; x; x -= x & (-x))
            F = max(F, tree[x] + 1);
        ans = max(ans, F);
        for (int x = arr[i]; x <= n; x += x & (-x))
            tree[x] = max(tree[x], F);
    }
    cout << n - ans << endl;
}
