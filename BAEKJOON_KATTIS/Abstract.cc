#include "bits/stdc++.h"

using namespace std;

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
template <class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }
/*
template <class P>
int sideOf(const P &s, const P &e, const P &p)
{
    auto a = (e - s).cross(p - s);
    double l = (e - s).dist();
    return (a > l) - (a < -l);
}
*/
typedef Point<double> P;

double rat(P a, P b) { return sgn(b.x) ? a.x / b.x : a.y / b.y; }

double polyUnion(vector<vector<P>> &poly)
{
    double ret = 0;
    for (int i = 0; i < poly.size(); i++)
        for (int v = 0; v < poly[i].size(); v++)
        {
            P A = poly[i][v], B = poly[i][(v + 1) % poly[i].size()];
            vector<pair<double, int>> segs = {{0, 0}, {1, 0}};
            for (int j = 0; j < poly.size(); j++)
                if (i != j)
                {
                    for (int u = 0; u < poly[j].size(); u++)
                    {
                        P C = poly[j][u], D = poly[j][(u + 1) % poly[j].size()];
                        int sc = sideOf(A, B, C), sd = sideOf(A, B, D);
                        // cout << sc << " " << sd << " " << A << " " << B << " " << C << " " << D << " " << A.cross(B) << '\n';
                        if (sc != sd)
                        {
                            double sa = C.cross(D, A), sb = C.cross(D, B);
                            if (min(sc, sd) < 0)
                                segs.emplace_back(sa / (sa - sb), sgn(sc - sd));
                        }
                        else if (!sc && !sd && j < i && sgn((B - A).dot(D - C)) > 0)
                        {
                            segs.emplace_back(rat(C - A, B - A), 1);
                            segs.emplace_back(rat(D - A, B - A), -1);
                        }
                    }
                }
            sort(segs.begin(), segs.end());
            for (auto &s : segs)
                s.first = min(max(s.first, 0.0), 1.0);
            double sum = 0;
            int ctr = segs[0].second;
            for (int j = 1; j < segs.size(); j++)
            {
                if (!ctr)
                    sum += segs[j].first - segs[j - 1].first;
                ctr += segs[j].second;
            }
            ret += A.cross(B) * sum;
        }
    return ret / 2;
}

double Area(vector<P>&pset)
{
    int N = pset.size();
    double ret = 0;
    for (int i = 0; i < N; i++)
    {
        ret += pset[i].cross(pset[(i + 1) % N]);
    }
    return ret / 2;
}

int main(void)
{
    int N, Q;
    cout << fixed << setprecision(10); 
    while (cin >> N && N)
    {
        vector<vector<P>> pset;
        double ret = 0; 
        for (int i = 0; i < N; i++)
        {
            int M; 
            cin >> M; 
            vector<P>poly(M); 
            for(int j = 0; j < M; j++)
            {
                cin >> poly[j].x >> poly[j].y; 
            }
            pset.push_back(poly); 
            ret += Area(poly); 
        }
        cout << -ret << " " << -polyUnion(pset) << '\n'; 
    }
    return 0;
}