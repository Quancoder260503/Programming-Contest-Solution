#include "bits/stdc++.h"
using namespace std; 
#define lint long long
#define INF (int) 1e9
struct Point
{
    long long x, y;
    Point(long long _x = 0, long long _y = 0) : x(_x), y(_y) {}; 

};
lint dist(const Point &a, const Point &b)
{
     return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y); 
}
bool cmmp(const Point a, const Point b)
{
     return a.x == b.x ? a.y < b.y : a.x < b.x;
}
struct cmp
{
     bool operator()(const Point &a, const Point &b) const
     {
         return a.y == b.y ? a.x < b.x : a.y < b.y;
     }
};
set<Point, cmp>pset; 
vector<Point>points;
lint closet_pair()
{
     lint ans = dist(points[0], points[1]); 
     sort(points.begin(), points.end(), cmmp); 
     for(int i = 0; i < points.size(); i++)
     {
         lint x = points[i].x; 
         lint y = points[i].y; 
         lint d = sqrt(ans); 
         Point curr = Point(-INF, y - d);
         while(true)
         {
             auto it = pset.upper_bound(curr);
             if(it == pset.end()) break; 
             curr = *it; 
             if(it -> y > y + d) break; 
             if(it -> x < x - d)
             {
                 pset.erase(it); 
                 continue; 
             } 
             ans = min(ans, dist(points[i], curr)); 
         }
         pset.insert(points[i]); 
     }
     return ans; 
}
int n;
signed main(void)
{
     scanf("%d", &n);
     lint prefix = 0;
     for(int i = 1; i <= n; i++)
     {
         int x; scanf("%d", &x); 
         prefix = prefix + x; 
         points.push_back(Point(i, prefix)); 
     }
     printf("%lld\n", closet_pair()); 
     return 0; 
}