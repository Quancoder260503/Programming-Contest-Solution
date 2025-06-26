#include "bits/stdc++.h"
using namespace std;
#define MAXN 1500000
#define x first
#define y second
#define lint long long 
typedef pair<lint, lint> Vec;
const int mod = 1e9 + 7;
int n, k, q;
using Point = Vec; 
Point origin; 
struct event
{
     int id, type; 
     Point point;
     event(int _type, int _id, Point _curr) : type(_type), id(_id), point(_curr){};
};
Vec operator-(Vec AB, Vec AC)
{
    return Vec(AB.x - AC.x, AB.y - AC.y);
}
lint cross(Vec AB, Vec AC)
{
    return (1ll) * AB.x * AC.y - (1ll) * AB.y * AC.x;
}
lint cross3(Vec AB, Vec AC, Vec BC)
{
    Vec X = AC - AB;
    Vec Y = BC - AB;
    return cross(X, Y);
}
int half(Vec a)
{
    if(a.x != origin.x) return(origin.x > a.x) - (origin.x < a.x); 
    return (origin.y > a.y) - (origin.y < a.y);      
}
bool operator < (event a, event b)
{
     if(half(a.point) == half(b.point))
     {
        lint c = cross3(origin, a.point, b.point);
        if(c == 0) return a.type > b.type; 
        return c < 0; 
     }
     return half(a.point) < half(b.point); 
}
event get_next(event curr)
{
     if(curr.point.x == n)
     {
        if(curr.point.y > 0) return event(0,0, Point(n, curr.point.y - 1)); 
        return event(0, 0, Point(n - 1, 0)); 
     }
     else if(curr.point.x == 0)
     {
        if(curr.point.y < n) return event(0, 0, Point(0, curr.point.y + 1));
        return event(0, 0, Point(1, n)); 
     }
     else if(curr.point.y == n)
     {
        if(curr.point.x < n) return event(0, 0, Point(curr.point.x + 1, n)); 
        return event(0, 0, Point(n, n - 1)); 
     }
     else
     {
        if(curr.point.x > 0) return event(0, 0, Point(curr.point.x - 1, 0)); 
        return event(0, 0, Point(0, 1)); 
     }
}
bool cmp(const Point &a, const Point &b)
{
     return cross3(origin, a, b) < 0; 
}
bool vis[MAXN]; 
signed main(void)
{
    scanf("%d %d", &n, &k);
    scanf("%lld %lld", &origin.x, &origin.y);
    vector<event>events;
    for(int i = 0; i < k; i++)
    {
         vector<Point>poly; 
         int m; 
         scanf("%d", &m); 
         for(int j = 0; j < m; j++)
         {
             lint x,y;
             scanf("%lld %lld", &x, &y); 
             poly.push_back(Point(x,y)); 
         }
         sort(poly.begin(), poly.end(), cmp);
         events.push_back(event(1, i, poly[0])); 
         events.push_back(event(-1, i, poly[m - 1])); 
    }
    sort(events.begin(), events.end()); 
    int on = 0;
    for(int i = 0; i < events.size(); i++)
    {
         if(events[i].type == 1) vis[events[i].id] = 1;
         if(events[i].type == -1 && !vis[events[i].id]) on += 1;
    }
    int ans = 0;
    int ptr = 0;
    event curr = event(0, 0, Point(origin.x ,n));
    for(int i = 0; i < events.size(); i++)
    {
         while(ptr < 4 * n && curr < events[i])
         {
             if(!on) ans += 1;
             ptr += 1;
             curr = get_next(curr);
         }
         on += events[i].type;  
    }
    if(on == 0) ans += 4 * n - ptr;
    printf("%d\n", ans);
    return 0; 
}