#include "bits/stdc++.h"

using namespace std; 

const double eps = 1e-5; 

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

using P = Point<double>;

template <class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) < 0;
}

bool segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b), oc = a.cross(b, c), od = a.cross(b, d);
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) return true;
    if (onSegment(c, d, a)) return true; 
	if (onSegment(c, d, b)) return true; 
	if (onSegment(a, b, c)) return true; 
	if (onSegment(a, b, d)) return true; 
	return false; 
}

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    int tc; 
    for(cin >> tc; tc--; ) { 
        double Prob; 
        vector<P>pts(7); 
        for(int i = 0; i < 7; i++) { 
            cin >> pts[i].x >> pts[i].y; 
        }
        cin >> Prob;
        vector<int>perm(7); 
        iota(perm.begin(), perm.end(), 0);
        vector<vector<int>>cand; 
        do { 
            double ret = 0; 
            vector<pair<P, P>>segs; 
            int check = true;
            for(int i = 0; i < 7; i++) { 
                segs.push_back({pts[perm[i]], pts[perm[(i + 1) % 7]]}); 
            }
            for(int i = 0; i < segs.size(); i++) { 
                for(int j = i + 1; j < segs.size(); j++) { 
                    if(segs[i].first   == segs[j].first || segs[i].first  == segs[j].second) continue; 
                    if(segs[i].second  == segs[j].first || segs[i].second == segs[j].second) continue; 
                    if(segInter(segs[i].first, segs[i].second, segs[j].first, segs[j].second)) { 
                       check = false; 
                       break;
                    } 
                } 
                if(!check) break;  
            }
            if(!check) continue; 
            for(int i = 0; i < perm.size(); i++) { 
                ret += pts[perm[i]].cross(pts[perm[(i + 1) % 7]]); 
            }
            ret = abs(ret) / 2; 
            ret = pow(ret / 4, 3); 
            if(fabsl(ret - Prob) < eps) { 
                cand.push_back(perm); 
            }
        }
        while(next_permutation(perm.begin(), perm.end()));
        assert(cand.size());
        sort(cand.begin(), cand.end()); 
        for(auto &y : cand[0]) { cout << y + 1 << " "; }
        cout << '\n'; 
    }
    return 0; 
}