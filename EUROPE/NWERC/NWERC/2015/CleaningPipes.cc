#include "bits/stdc++.h"

using namespace std;
#define double long double 

const int maxf = 1e6 + 10; 
const double EPS = 1e-5; 

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
bool onSegment(P s, P e, P p)
{
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template <class P>
int segInter(P a, P b, P c, P d)
{
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    // Checks if intersection is single non-endpoint point.
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return 1; 
    set<P> s;
    if (onSegment(c, d, a))
        s.insert(a);
    if (onSegment(c, d, b))
        s.insert(b);
    if (onSegment(a, b, c))
        s.insert(c);
    if (onSegment(a, b, d))
        s.insert(d);
    return s.size() > 0; 
}

template <class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

vector<int>g[maxf]; 
int vis[maxf], col[maxf], ret; 

void dfs(int u, int c)
{
    vis[u] = 1;
    col[u] = c;  
    for(auto v : g[u])
    {
        if(!vis[v])
        {
            dfs(v, 3 xor c); 
        }
        else if(col[v] == c) 
        {
            ret = 0; 
        }  
    }
}

int same(P a, P b)
{
    return a.x == b.x && a.y == b.y; 
}

int main(void)
{
    int N, M; 
    while(cin >> N >> M)
    {
        vector<P>wells(N); 
        for(int i = 0; i < N; i++) cin >> wells[i].x >> wells[i].y; 
        vector<pair<P, P>>pipes(M); 
        for(int i = 0; i < M; i++) 
        {
            int id;
            cin >> id;
            pipes[i].first = wells[--id]; 
            cin >> pipes[i].second.x >> pipes[i].second.y; 
        } 
        ret = 1; 
        for(int i = 0; i < M; i++) for(int j = i + 1; j < M; j++)
        {
            int chk = segInter(pipes[i].first, pipes[i].second, pipes[j].first, pipes[j].second) || (same(pipes[i].second, pipes[j].second));
            if (chk && !same(pipes[i].first, pipes[j].first) && !same(pipes[i].first, pipes[j].second) && !same(pipes[i].second, pipes[j].first))
            {
                //cout << i << " " << j << '\n'; 
                g[i].push_back(j);
                g[j].push_back(i); 
            }
        }
        for(int i = 0; i < M; i++) if(!vis[i]) dfs(i, 1); 
        cout << (ret ? "possible" : "impossible") << '\n'; 
    }
    return 0; 
}