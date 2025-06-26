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
    T norm() const { return x * x + y * y; }
    double dist() const { return sqrt((double)norm()); }
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
using point = Point<double>; 
int sideOf(point s, point e, point p) { return sgn(s.cross(e, p)); }
const int mod = 1e9 + 7;
const int M = 750;
int64_t dyn[M][M];
point P[M]; 
point A[M]; 
int N; 
int64_t f(int i, int j)
{
    if(dyn[i][j] != -1) return dyn[i][j]; 
    int64_t &ret = dyn[i][j]; 
    ret = P[j].cross(P[0]) > 0 && sideOf(P[i], P[j], P[0]) > 0;
    for(int k = j + 1; k < N; k++)
    {
        if(j > 0)
        {
            if(P[j].cross(P[k]) <= 0 || P[i].cross(P[j], P[k]) <= 0) continue; 
        }
        else if(P[j].cross(P[k]) <= 0) continue; 
        ret = (ret + f(j, k)) % mod; 
    }
    return ret; 
}
int chk_side(point a)
{
    return (a.x > 0 || a.x == 0 && a.y > 0); 
}
int cmp(point a, point b)
{
    if(chk_side(a) != chk_side(b)) return chk_side(a); 
    return a.cross(b) > 0;
}
int main(void)
{
    point H, G; 
    while(cin >> H.x >> H.y)
    {
        cin >> G.x >> G.y >> N;
        G = G - H;
        P[0] = G;  
        ++N;  
        for(int i = 1; i < N; i++) cin >> P[i].x >> P[i].y;
        for(int i = 1; i < N; i++) P[i] = P[i] - H;
        sort(P, P + N, cmp); 
        int st = 0; 
        for(int i = 0; i < N; i++) if(G == P[i]) 
        {
            st = i; 
            break; 
        }
        for(int i = st; i < N + st; i++) A[i - st] = P[i % N];
        for(int i = 0; i < N; i++) P[i] = A[i];  
        //for(int i = 0; i < N; i++) cout << P[i] << '\n'; 
        memset(dyn, -1, sizeof(dyn)); 
        cout << f(0, 0) << '\n'; 
    }
    return 0; 
}