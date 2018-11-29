// hash func overload
struct point{
int x, y;
bool operator==(const point &p)const{ return x == p.x && y == p.y; }
};
struct hasher {
size_t operator()(const point &p)const{ return p.x * 2 + p.y * 3; }
};
unordered_map<point, int, hasher> hsh;
const double eps = 1e-9;
bool equal(const double &x, const double &y) {
    return fabs(x - y) <
           eps;
}
struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
    Point operator + (const Point &p) const {
        return {x + p.x, y +
                p.y
               };
    }
    Point operator - (const Point &p) const {
        return {x - p.x, y -
                p.y
               };
    }
    Point operator * (double t) const {
        return {x * t, y * t};
    }
    double operator * (const Point &p) const {
        return x * p.x + y *
               p.y;
    }
    double operator % (const Point &p) const {
        return x * p.y - y *
               p.x;
    }
    bool operator == (const Point &p) const {
        return equal(x, p.x)
               && equal(y, p.y);
    }
    double operator ~ () const {
        return sqrt(*this **this);
    }
};
struct Comparator {
    Point a, b;
    Comparator(Point a, Point b): a(a), b(b) {}
    bool operator () (const Point &p, const Point &q) {
        return (p-a) * (b-a) < (q-a) * (b-a);
    }
};
bool between(double x, double l, double r) {
    if (l > r) swap(l, r);
    return x + eps > l && x - eps < r;
}
bool inside(Point q, const vector<Point> &p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        int j = i + 1 < n ? i + 1 : 0;
        if (fabs((q - p[i]) % (p[j] - p[i])) > eps) continue;
        if ((q - p[i]) * (p[j] - p[i]) < -eps) continue;
        if ((q - p[j]) * (p[i] - p[j]) < -eps) continue;
        return true;
    }
    int fl = 0;
    for (int i = 0; i < n; i++) {
        int j = i + 1 < n ? i + 1 : 0;
        Point a = p[i], b = p[j];
        if (equal(a.x, b.x)) continue;
        if (a.x > b.x) swap(a, b);
        if (q.x < a.x - eps) continue;
        if (q.x > b.x - eps) continue;
        if ((q - a) % (b - a) > 0) fl ^= 1;
    }
    return fl;
}
void intersect(Point p, Point q, Point a, Point b, vector<Point>
               &ints) {
    double na = (a - p) % (q - p), nb = (b - p) % (q - p);
    if (na * nb > eps) return;
    if (equal(na, nb)) return;
    ints.push_back(a + (b - a) * (na / (na - nb)));
}
void intersectCircleLine() {
    double r, a, b, c;
    double x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);
    if (c*c > r*r*(a*a+b*b)+EPS) puts ("no points");
    else if (abs (c*c - r*r*(a*a+b*b)) < EPS) {
        puts ("1 point");
        cout << x0 << ' ' << y0 << '\n';
    } else {
        double d = r*r - c*c/(a*a+b*b);
        double mult = sqrt (d / (a*a+b*b));
        double ax,ay,bx,by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;
        puts ("2 points");
        cout << ax << ' ' << ay << '\n' << bx << ' ' << by << '\n';
    }
}
