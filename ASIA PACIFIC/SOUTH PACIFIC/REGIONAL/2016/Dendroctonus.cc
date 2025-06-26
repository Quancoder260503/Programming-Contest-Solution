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
    T dist2() const { return 1LL * x * x + 1LL * y * y; }
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

typedef Point<int64_t> P;

template <class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2, int64_t &den)
{
    auto d = (e1 - s1).cross(e2 - s2);
    den = d;
    if (d == 0) return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, s1 * p + e1 * q};
}

const int maxf = 1e6 + 2; 
int infected[maxf]; 

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    cin >> N; 
    vector<P>p(N); 
    for (int i = 0; i < N; i++)
    {
        char type;
        cin >> p[i].x >> p[i].y >> type;
        infected[i] = (type == 'I'); 
        p[i] = p[i] * 2;
    } 
    int ret = (p.size() <= 1); 
    for (int i = 0; i < p.size(); i++) for (int j = 0; j < p.size(); j++) for (int k = 0; k < p.size(); k++)
    {
        P s1 = (p[i] + p[j]) / 2;
        P s2 = (p[j] + p[k]) / 2;
        P e1 = (p[i] - p[j]) / 2;
        swap(e1.x, e1.y);
        e1.x = -e1.x;
        P e2 = (p[j] - p[k]) / 2;
        swap(e2.x, e2.y);
        e2.x = -e2.x;
        int64_t den;
        auto [_, center] = lineInter(s1, s1 + e1, s2, s2 + e2, den);
        if(den)
        {
            int64_t radius = (center - p[i] * den).dist2();
            int chk = 1;
            for (int x = 0; x < p.size(); x++)
            {
                if(infected[x]) chk = chk & ((center - p[x] * den).dist2() <= radius);
            }
            if(!chk) continue; 
            for (int x = 0; x < p.size(); x++) 
            {
                if(!infected[x]) chk = chk & ((center - p[x] * den).dist2() >= radius);
            }
            if (chk)
            {
                ret = chk;
            }
        } 
    }
    for (int i = 0; i < p.size(); i++) for (int j = i + 1; j < p.size(); j++)
    {
        auto center = (p[i] + p[j]) / 2;
        int64_t radius = (center - p[i]).dist2();
        int chk = 1;
        //cout << center << " " << radius << '\n'; 
        for (int x = 0; x < p.size(); x++) 
        {
            if(infected[x]) 
            {
                chk = chk & ((center - p[x]).dist2() <= radius);
            } 
        }
        if (!chk) continue;
        for (int x = 0; x < p.size(); x++)
        {
            if(!infected[x]) chk = chk & ((center - p[x]).dist2() >= radius);
        }
        if (chk) 
        {
            ret = chk;
        }
    }
    cout << (ret ? "No" : "Yes") << '\n'; 
    return 0;
}

/*
  Alternative solution : use Welz algorithm to find minimum enclosing circle (careful of precision)
*/