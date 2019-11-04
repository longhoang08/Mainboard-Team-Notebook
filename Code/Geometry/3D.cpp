typedef double T;
struct p3 {
    T x,y,z;
    p3 operator+(p3 p) {return {x+p.x, y+p.y, z+p.z};}
    p3 operator-(p3 p) {return {x-p.x, y-p.y, z-p.z};}
    p3 operator*(T d) {return {x*d, y*d, z*d};}
    p3 operator/(T d) {return {x/d, y/d, z/d};} //only for floating-point
    bool operator==(p3 p) {return tie(x,y,z) == tie(p.x,p.y,p.z);}
    bool operator!=(p3 p) {return !operator==(p);}
    T operator|(p3 v, p3 w) {return v.x*w.x + v.y*w.y + v.z*w.z;} //dot product
    p3 operator*(p3 v, p3 w) { //cross product
        return {v.y*w.z - v.z*w.y, v.z*w.x - v.x*w.z, v.x*w.y - v.y*w.x};
    }}
T sq(p3 v) {return v|v;}
double abs(p3 v) {return sqrt(sq(v));}
p3 unit(p3 v) {return v/abs(v);}
double angle(p3 v, p3 w) {
    double cosTheta = (v|w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));}
T orient(p3 p, p3 q, p3 r, p3 s) {return (q-p)*(r-p)|(s-p);} // S vs plane PQR
struct plane {
    p3 n; T d; // From normal n and offset d
    plane(p3 n, T d) : n(n), d(d) {} // From normal n and point P
    plane(p3 n, p3 p) : n(n), d(n|p) {} // From three non-collinear points P,Q,R
    plane(p3 p, p3 q, p3 r) : plane((q-p)*(r-p), p) {}
    // - these work with T = int
    T side(p3 p) {return (n|p)-d;}
    double dist(p3 p) {return abs(side(p))/abs(n);}
    plane translate(p3 t) {return {n, d+(n|t)};}
    // - these require T = double
    plane shiftUp(double dist) {return {n, d + dist*abs(n)};}
    p3 proj(p3 p) {return p - n*side(p)/sq(n);}
    p3 refl(p3 p) {return p - n*2*side(p)/sq(n);}};
struct line3d {
    p3 d, o;
    // From two points P, Q
    line3d(p3 p, p3 q) : d(q-p), o(p) {}
    // From two planes p1, p2 (requires T = double)
    line3d(plane p1, plane p2) {
        d = p1.n*p2.n;  
        o = (p2.n*p1.d - p1.n*p2.d)*d/sq(d);
    }
    // - these work with T = int
    double sqDist(p3 p) {return sq(d*(p-o))/sq(d);}
    double dist(p3 p) {return sqrt(sqDist(p));}
    bool cmpProj(p3 p, p3 q) {return (d|p) < (d|q);}
    // - these require T = double
    p3 proj(p3 p) {return o + d*(d|(a-o))/sq(d);}
    p3 refl(p3 p) {return proj(p)*2 - p;}
    p3 inter(plane p) {return o - d*p.side(o)/(p.n|d);}};
double dist(line l1, line l2) {
    p3 n = l1.d*l2.d;
    if (n == zero) return l1.dist(l2.o);
    return abs((l2.o-l1.o)|n)/abs(n);}
p3 closestOnL1(line l1, line l2) {
    p3 n2 = l2.d*(l1.d*l2.d);
    return l1.o + l1.d*((l2.o-l1.o)|n2)/(l1.d|n2);}
double smallAngle(p3 v, p3 w) {
    return acos(min(abs(v|w)/abs(v)/abs(w), 1.0));}
double angle(plane p1, plane p2) {
    return smallAngle(p1.n, p2.n);}
bool isParallel(plane p1, plane p2) {
    return p1.n*p2.n == zero;}
bool isPerpendicular(plane p1, plane p2) {
    return (p1.n|p2.n) == 0;}
double angle(line3d l1, line3d l2) {
    return smallAngle(l1.p, l2.d);}
bool isParallel(line3d l1, line3d l2) {
    return l1.d*l2.d == zero;}
bool isPerpendicular(line3d l1, line3d l2) {
    return (l1.d|l2.d) == 0;}
double angle(plane p, line3d l) {
    return M_PI/2 - smallAngle(p.n, l.d);}
bool isParallel(plane p, line3d l) {
    return (p.n|l.d) == 0;}
bool isPerpendicular(plane p, line3d l) {
    return p.n*l.d == zero;}
line3d perpThrough(plane p, p3 o) {return line(o, o+p.n);}
plane perpThrough(line3d l, p3 o) {return plane(l.d, o);}
