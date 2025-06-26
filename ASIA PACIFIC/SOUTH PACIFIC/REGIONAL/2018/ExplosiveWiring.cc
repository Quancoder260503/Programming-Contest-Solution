#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point
{
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const
    {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream &operator<<(ostream &os, P p)
    {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

using P = Point<int64_t>; 

template <class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> bool segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b), oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) return true; 
	return (onSegment(c, d, a) || (onSegment(c, d, b)) || (onSegment(a, b, c)) || (onSegment(a, b, d)));
}

bool poly_intersect(const vector<P>&a, const vector<P>&b) { 
    for(int i = 0; i < sz(a) - 1; i++) { 
        for(int j = 0; j < sz(b) - 1; j++) { 
            if(segInter(a[i], a[i + 1], b[j], b[j + 1])) return true; 
        }
    }
    return false; 
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n;
    vector<int>val(n);  
    vector<vector<P>>poly(n);
    vector<pair<int64_t, int>>lines; 
    for(int i = 0, x; i < n; i++) {         
        cin >> val[i] >> x;
        poly[i].resize(x); 
        for(auto &pts : poly[i]) { 
            cin >> pts.x >> pts.y; 
        }
        lines.push_back({poly[i].front().x, i});
        lines.push_back({poly[i].back().x,  i});  
    }
    sort(lines.begin(), lines.end()); 
    vector<vector<int>>inter(2 * n + 1, vector<int>(2 * n + 1)); 
    for(int i = 0; i < 2 * n; i++) for(int j = i + 1; j < 2 * n; j++) { 
       inter[i][j] = inter[j][i] = poly_intersect(poly[lines[i].second], poly[lines[j].second]);  
    }
    vector<int>cost(sz(lines)); 
    for(int i = 0; i < sz(lines); i++) {
        cost[i] = val[lines[i].second]; 
    }
    vector<int>pr(2 * n + 1, 2 * n), r(n, -1); 
    for(int i = sz(lines) - 1; i >= 0; i--) { 
        if(r[lines[i].second] == -1) r[lines[i].second] = i; 
        pr[i] = r[lines[i].second]; 
    }
    vector<vector<vector<int>>>dyn(2 * n + 1, vector<vector<int>>(2 * n + 1, vector<int>(2 * n + 1, -1))); 
    function<int(int, int, int)> func = [&](int idx, int ca, int cb) { 
        if(dyn[idx][ca][cb] != -1) return dyn[idx][ca][cb];
        int &ret = dyn[idx][ca][cb]; 
        if(ca == idx || cb == idx || pr[ca] == idx || pr[cb] == idx) return ret = 0;
        ret = func(idx + 1, ca, cb); 
        if(pr[idx] != idx && !inter[idx][ca] && !inter[idx][cb]) { 
            for(int nxt = idx + 1; nxt != ca && nxt != cb && nxt != pr[ca] && nxt != pr[cb]; nxt++) { 
                if(pr[nxt] == nxt || !inter[idx][nxt] || inter[nxt][ca] || inter[nxt][cb]) continue;
                ret = max(ret, cost[idx] + cost[nxt] 
                               + func(idx + 1, idx, nxt) 
                               + func(nxt + 1, idx, nxt) 
                               + func(min(pr[nxt], pr[idx]) + 1, idx, nxt) 
                               + func(max(pr[nxt], pr[idx]) + 1, ca, cb) );  
            }
        }
        return ret; 
    }; 
    cout << func(0, 2 * n, 2 * n) << '\n'; 
    return 0; 
}