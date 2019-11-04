// Circle Circle Intersection
// zz: pairs of points
zz circleLine(double r, double a, double b, double c){
	zz res = zz(ii(-1e9 - 1, -1e9 - 1), ii(-1e9 - 1, -1e9 - 1));
	double x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);
	if (c*c > r*r*(a*a+b*b) + eps)
	    return res;
	else if (abs (c*c - r*r*(a*a+b*b)) < eps) {
	    res.first = ii(x0, y0);
	    return res; }
	else {
	    double d = r*r - c*c/(a*a+b*b);
	    double mult = sqrt (d / (a*a+b*b));
	    double ax, ay, bx, by;
	    ax = x0 + b * mult; bx = x0 - b * mult;
	    ay = y0 - a * mult; by = y0 + a * mult;
	    res.first = ii(ax, ay); res.second = ii(bx, by);
	    return res; } }
zz circleCircleIntersection(Circle c1, Circle c2) {
	zz res = zz(ii(-1e9 - 1, -1e9 - 1), ii(-1e9 - 1, -1e9 - 1));
    if (dist(ii(c1.x, c1.y), ii(c2.x, c2.y)) < eps) {
        if (abs(c1.r - c2.r) < eps)
            return res;
        return res; }
    double dx = c2.x - c1.x; double dy = c2.y - c1.y;
    double A = -2 * dx; double B = -2 * dy;
    double C = dx * dx + dy * dy + c1.r * c1.r - c2.r * c2.r;
    res = circleLine(c1.r, A, B, C);
    res.first = ii(res.first.first + c1.x, res.first.second + c1.y);
    res.second = ii(res.second.first + c1.x, res.second.second + c1.y);
    return res;
}
///// 2 segments intersection
bool onSegment(Point p, Point q, Point r)  // q lies on (p, r)
int orientation(Point p, Point q, Point r){
   int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2;}
bool doIntersect(Point p1, Point q1, Point p2, Point q2){
	int o1 = orientation(p1, q1, p2); int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); int o4 = orientation(p2, q2, q1); 
    if (o1 != o2 && o3 != o4) return true; 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
    return false;}
 //// 