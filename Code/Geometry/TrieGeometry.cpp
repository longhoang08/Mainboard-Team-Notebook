/**
 * Geometry
 */
Duong tron di qua 3 diem cho truoc
	Let A = (0, 0) centers are  
	(Cy * (Bx^2 + By^2) - By * (Cx^2 + Cy^2))/D
		and
	(Bx * (Cx^2 + Cy^2) - Cx * (Bx^2 + By^2))/D
		where 
	D = 2 * (Bx Cy - By Cx);
 
Diem trong tam giac
bool isInside(const Vector &P) {
	Vector a = C - A, b = B - A, c = P - A;
	T under = a.x*b.y - b.x*a.y;
	T u = (c.x*b.y-c.y*b.x);
	T v = (a.x*c.y-a.y*c.x);
	return u >= 0 && v >= 0 && u+v <= under || u<=0 && v<=0 && u+v >= under;
} //remove equalities if not want the boundary
 
Pick’s theorem (So diem trong da giac co dinh nguyen) 
	I = A − B/2 + 1
	where 
		A is the area of a lattice polygon,
		I is number of lattice points inside it,
		B is number of lattice points on the boundary.
		Number of lattice points minus one on a line segment from (0, 0) and (x, y) is gcd(x, y).
 
Tich chap 3d: a x b = (aybz - azby, azbx - axbx, axby - aybx)
 
Distance from line AB to 𝑃 (for any dimension) : |(A-P) x (B-P)| / |A-B|
 
Khoảng cách từ điểm đến đoạn thẳng
	if (dot(B-A, P-A) < 0) return dist(A,P);
	if (dot(A-B, P-B) < 0) return dist(B,P);
	return fabs(cross(P,A,B) / dist(A,B));
	dot - tich vo huong, cross - tucg cgao
 
Hinh chieu
Hinh chieu cua C tren duong thang AB : [dot(AB, AC) / dot(AB, AB)] AB

Duong tron cat duong tron
// (x1,y1,r1) and (x2,y2,r2)
	a = x2 - x1;
	b = y2 - y1;
	c = [(r1^2 - x1^2 - y1^2) - (r2^2 - x2^2 - y2^2)] / 2;
	d = sqrt(a^2 + b^2);
 
	if not |r1 - r2| <= d <= |r1 + r2|, return "no solution"
	if d == 0, circles are concentric, a special case
 
Duong tron cat duong thang
// (x1,y1,r1) and ax+by=c
Normalize line: 
	d = sqrt(a^2+b^2)
	a /= d; 
	b /= d; 
	c /= d;
	e = c - a*x1 - b*y1;
	h = sqrt(r1^2 - e^2); // check if r1<e for circle-line test
	return (x1, y1) + (a*e, b*e) + h*(-b, a),
		(x1, y1) + (a*e, b*e) - h*(-b, a);
 
Template
double eps = 1e-8;
 
struct point2d {
	double x,y;
	point2d operator-(point2d v) { return (point2d){x-v.x, y-v.y}; }
	point2d operator+(point2d v) { return (point2d){x+v.x, y+v.y}; }
};
 
struct point3d {
	double x,y,z;
	point3d operator-(point3d v) { return (point3d){x-v.x, y-v.y, z-v.z}; }
};
 
double trip(point3d a, point3d b, point3d c) {
	return a.x * ( b.y * c.z - b.z * c.y )
		- a.y * ( b.x * c.z - b.z * c.x )
		+ a.z * ( b.x * c.y - b.y * c.x );
}
 
double len(point2d a) { return sqrt(a.x*a.x+a.y*a.y); }
 
double len(point3d a) { return sqrt(a.x*a.x+a.y*a.y+a.z*a.z); }
 
point3d cross(point3d a, point3d b) {
	return (point3d){
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x
	};
}
 
double dot(point3d a, point3d b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
double dot(point2d a, point2d b) { return a.x*b.x + a.y*b.y; }
double cross(point2d a, point2d b) {
	return a.x*b.y - a.y*b.x;
}
point2d rotate(point2d c, double angle) {
	return (point2d) {
		c.x*cos(angle)-c.y*sin(angle),
		c.x*sin(angle)+c.y*cos(angle) 
	};
}
 
// distance AB to C
double linePointDist(point2d A, point2d B, point2d C, bool isSegment) {
	double dist = cross(B-A,C-A) / len(B-A);
	if(isSegment){
		if( dot(C-B,B-A) > eps) return len(B-C);	
		if( dot(C-A,A-B) > eps) return len(A-C);
	}
	return fabs(dist);
}
 
struct Line { double A,B,C; };//Ax + By = C
Line makeline(point2d a1, point2d a2)
{
	Line ret = (Line){ a2.y-a1.y, a1.x-a2.x };
	ret.C = ret.A * a1.x + ret.B * a1.y;
	return ret;
}
 
double dist(Line l, point2d p)
{
	return fabs(p.x * l.A + p.y * l.B - l.C)/sqrt(l.A*l.A+l.B*l.B);;
}
Line rot90(Line l, point2d p)
{
	Line ret = (Line){ -l.B, l.A };
	ret.C = ret.A * p.x + ret.B * p.y;
	return ret;
}
point2d intersect(Line l1, Line l2)
{
	double det = l1.A*l2.B - l2.A*l1.B;
	if(fabs(det) < eps) det=0;  //zero means parallel
	return (point2d) { (l2.B*l1.C - l1.B*l2.C)/det, (l1.A*l2.C - l2.A*l1.C)/det};
}
 
//for segment segment intersection, check additionally
//min(x1,x2) <= x <= max(x1,x2)
//min(y1,y2) <= x <= max(y1,y2)
bool segmentsIntersect( point2d A, point2d B, point2d C, point2d E )
{
	point2d in = intersect( makeline(A,B), makeline(C,E) );
	return linePointDist(A,B,in,true) < eps && linePointDist(C,E,in,true) < eps;
}
 
// get a line passing between two points
Line getmidline(point2d a, point2d b)
{
	point2d mid(a+b); mid.x/=2; mid.y/=2;
	return rot90( makeline(a,b), mid );
}
 
//reflect a point into it’s "mirror" with repect to a line
point2d reflectPoint(Line l, point2d p)
{
	Line r = rot90(l, p);
	point2d Y=intersect(l,r);
	return Y-(p-Y);
}