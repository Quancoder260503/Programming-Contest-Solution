#include "bits/stdc++.h"

using namespace std; 

const double EPS = 1e-8; 
typedef long long coord;

class point {
public:
	coord x, y;

	point() { x = y = 0; }
	point(coord x1, coord y1) { x = x1; y = y1; }

	friend ostream &operator <<(ostream &os, point p);

	string str()
	{
		ostringstream res;
		res << *this;
		return res.str();
	}

	point operator +=(point a) { x += a.x; y += a.y; return *this; }
	point operator -=(point a) { x -= a.x; y -= a.y; return *this; }
};

point operator +(point a, point b) { return a += b; }
point operator -(point a, point b) { return a -= b; }
coord operator *(point a, point b) { return a.x*b.x + a.y*b.y; }

coord cross(point a, point b) { return a.x*b.y - a.y*b.x; }
double length(point a) { return sqrt((double)(a*a)); }

class line {
public:
	point p1, p2;

	line() { p1 = p2 = point(); }
	line(point q1, point q2) { p1 = q1; p2 = q2; }
};

ostream &operator <<(ostream &os, point p)  { return os << '(' << p.x << ',' << p.y << ')'; }

long long sgn(long long x) { return x==0 ? 0 : (x<0 ? -1 : 1); }

int intersect(line a, line b)
{
	// directions of lines
	point da = a.p2 - a.p1;
	point db = b.p2 - b.p1;

	// degenerate lines
	if ( length(da)<EPS )
		return cross(db,a.p1-b.p1)==0 && (a.p1-b.p1)*(a.p1-b.p2)<=0;
	if ( length(db)<EPS )
		return cross(da,b.p1-a.p1)==0 && (b.p1-a.p1)*(b.p1-a.p2)<=0;

	// special case parallel lines
	if ( cross(da,db)==0 ) {
		if ( cross(a.p1-b.p1,da)!=0 ) return 0;
		return ((b.p1-a.p1)*(b.p1-a.p2)<=0 ||
		        (b.p2-a.p1)*(b.p2-a.p2)<=0 ||
		        (a.p1-b.p1)*(a.p1-b.p2)<=0 ||
		        (a.p2-b.p1)*(a.p2-b.p2)<=0);
	}

	// return false if line segments not really cross
	if ( sgn(cross(da,b.p1-a.p1))*sgn(cross(da,b.p2-a.p1))>0 ) return 0;
	if ( sgn(cross(db,a.p1-b.p1))*sgn(cross(db,a.p2-b.p1))>0 ) return 0;

	return 1;
}

int operator <(point a, point b)
{
	if ( a.x!=b.x ) return a.x<b.x;
	return a.y<b.y;
}


int main(void) {
    ios_base::sync_with_stdio(false);  
    cin.tie(0); 
    cout.tie(0); 
    int tc, s, r, w, p;
    cin >> tc;  
    while(tc--) { 
        cin >> s >> r >> w >> p; 
        vector<pair<point, point>>wall(w); 
        vector<point>product(p); 
        set<point>sensor; 
        for(int i = 0; i < s; i++) { 
            point p; 
            cin >> p.x >> p.y; 
            sensor.insert(p); 
        }
        for(int i = 0; i < w; i++) {
            cin >> wall[i].first.x >> wall[i].first.y >> wall[i].second.x >> wall[i].second.y;  
        }
        for(int i = 0; i < p; i++) { 
            cin >> product[i].x >> product[i].y; 
        }
        for(int i = 0; i < p; i++) { 
            set<point>ret; 
            for(int dx = -r; dx <= r; dx++)
            for(int dy = -r; dy <= r; dy++) { 
                point c = point(product[i].x + dx, product[i].y + dy);
                double distance = length(c - product[i]); 
                if(distance <= r && sensor.count(c)) {  
                    for(int k = 0; k < w; k++) {  
                        distance += intersect(line(c, product[i]), line(wall[k].first, wall[k].second)); 
                    }
                    if(distance <= r) { 
                        ret.insert(c); 
                    }
                }
            }
            cout << ret.size() << " "; 
            for(auto &pts : ret) { 
               cout << "(" << pts.x << "," << pts.y << ") ";   
            }
            cout << '\n'; 
        }
    }
    return 0; 
}