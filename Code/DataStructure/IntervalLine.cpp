// template Interval line Min
#define mid ((lo + hi)>>1)

class Line {
public:
    ll a, b;

    Line (ll x = cmax, ll y = cmax) {
        a = x, b = y;
    }

    ll get(int x) {
        return 1LL * val[x] * a + b;
    }
};

const Line oo = Line(cmax, cmax);


class ILTree {
    int m;
public:
    Line t[maxn*4];

    ILTree(int last = 200000) {
        m = last;
        init(1,1,m);
    }

    void init(int i, int lo, int hi) {
        t[i] = oo;
        if (lo == hi) return;
        init(i * 2,lo,mid);
        init(i * 2 + 1, mid + 1, hi);
    }

    void update(int i, int lo, int hi, int l, int r, Line d) {
        if (l > hi || r < lo) return;
        if (lo >= l && hi <= r) {
            // t[i] hoan toan nam duoi d
            if (t[i].get(lo) <= d.get(lo) && t[i].get(hi) <= d.get(hi)) return;
            //t[i] hoan toan nam tren d thi cap nhap t[i] = d
            if (t[i].get(lo) >= d.get(lo) && t[i].get(hi) >= d.get(hi)) {
                t[i] = d;
                return;
            }
            //nua dau cua d tot hon
            if (t[i].get(lo) >= d.get(lo) && t[i].get(mid) >= d.get(mid)) {
                update(i * 2 + 1, mid + 1, hi, l, r, t[i]);
                t[i] = d;
                return;
            }
            // nua dau cua t[i] tot hon
            if (t[i].get(lo) <= d.get(lo) && t[i].get(mid) <= d.get(mid)) {
                update(i * 2 + 1, mid + 1, hi, l, r, d);
                return;
            }
            // nua sau cua d tot hon
            if (t[i].get(mid + 1) >= d.get(mid + 1) && t[i].get(hi) >= d.get(hi)) {
                update(i * 2, lo, mid, l, r, t[i]);
                t[i] = d;
                return;
            }
            // nua sau cua t[i] tot hon
            if (t[i].get(mid + 1) <= d.get(mid + 1) && t[i].get(hi) <= d.get(hi)) {
                update(i * 2, lo, mid, l, r, d);
                return;
            }
        }
        update(i * 2, lo, mid, l, r, d);
        update(i * 2 + 1, mid + 1, hi, l, r, d);
    }

    ll get(int i, int lo, int hi, int pos) {
        if (lo > pos || hi < pos) return llmax;
        ll res = t[i].get(pos);
        if (lo == hi) return res;
        res = min(res, get(i * 2, lo, mid, pos));
        res = min(res, get(i * 2 + 1, mid + 1, hi, pos));
        return res;
    }
};

#undef mid
#undef oo
