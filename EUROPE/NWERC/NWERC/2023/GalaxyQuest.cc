#include "bits/stdc++.h"

using namespace std; 

template<class T> struct Point3D {
	typedef Point3D P;
	typedef const P& R;
	T x, y, z;
	explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
	bool operator<(R p) const {
		return tie(x, y, z) < tie(p.x, p.y, p.z); }
	bool operator==(R p) const {
		return tie(x, y, z) == tie(p.x, p.y, p.z); }
	P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
	P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
	P operator*(T d) const { return P(x*d, y*d, z*d); }
	P operator/(T d) const { return P(x/d, y/d, z/d); }
	T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
	P cross(R p) const {
		return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
	}
	T dist2() const { return x*x + y*y + z*z; }
	double dist() const { return sqrt((double)dist2()); }
	//Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
	double phi() const { return atan2(y, x); } 
	//Zenith angle (latitude) to the z-axis in interval [0, pi]
	double theta() const { return atan2(sqrt(x*x+y*y),z); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P normal(P p) const { return cross(p).unit(); }
	//returns point rotated 'angle' radians ccw around axis
	P rotate(double angle, P axis) const {
		double s = sin(angle), c = cos(angle); P u = axis.unit();
		return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
	}
};

using pts = Point3D<double>; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    int n, m, q; 
    cin >> n >> m >> q;
    vector<pts>p(n); 
    for(int i = 0; i < n; i++) { 
        cin >> p[i].x >> p[i].y >> p[i].z; 
    }
    vector<vector<pair<int, double>>>g(n);
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v; 
        g[--u].push_back({--v, sqrt((p[u] - p[v]).dist())}); 
        g[v].push_back({u, sqrt((p[u] - p[v]).dist())});  
    }
    using T = pair<double, int>; 
    vector<double>dist(n, 1e100); 
    priority_queue<T, vector<T>, greater<T>>pq; 
    pq.push({0, 0});
    dist[0] = 0; 
    while(pq.size()) { 
        auto [x, u] = pq.top();
        pq.pop(); 
        if(dist[u] != x) continue;
        for(auto [v, w] : g[u]) if(dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w; 
            pq.push({dist[v], v});  
        }
    } 
    cout << fixed << setprecision(10); 
    for(int i = 0, c, t; i < q; i++) {
        cin >> c >> t;
        --c;  
        double b = 1.0 * t / dist[c];
        if(b * b > 4) { 
            double x1 = sqrt(b * b / 4 - 1.0) + b / 2;
            double x2 = -sqrt(b * b / 4 - 1.0) + b / 2;  
            cout << min(x1, x2) * dist[c] * 2 << '\n'; 
        }
        else cout << "impossible\n";
    }
    return 0; 
}