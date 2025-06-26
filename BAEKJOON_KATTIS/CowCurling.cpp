#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 1500000
#define x first 
#define y second
typedef pair<long long,long long> Vec; 
typedef long double ldb;
const int mod = 1e9 + 7; 
int n,k;
using Point = Vec;
vector<Point>lower, upper;
Point P[N];
Vec operator - (Vec AB, Vec AC){
    return Vec(AB.x - AC.x, AB.y - AC.y); 
}
long long cross(Vec AB, Vec AC) {
    return (1LL) * AB.x * AC.y - (1LL) * AB.y * AC.x; 
}
long long cross3(Vec A, Vec B, Vec C) {
    Vec X = B - A; 
    Vec Y = C - A; 
    return  cross(X,Y);
}
void ConvexHull(vector<Point>& Pset){ 
        sort(Pset.begin(),Pset.end());
        Pset.erase(unique(Pset.begin(),Pset.end()),Pset.end());
        int n = Pset.size();
        // lower hull
        vector<Point>hull;
        for(int i = 0; i < n; i++){
              while(hull.size() > 1 && cross3(hull[hull.size() - 2], hull.back(), Pset[i]) <= 0){
                    hull.pop_back(); 
              }
              hull.push_back(Pset[i]); 
        }
        // upper hull 
        int lower_hull = hull.size();
        lower.resize(0); 
        lower = hull;
        for(int i = n - 2; i >= 0; i--){
              while(hull.size() > lower_hull && cross3(hull[hull.size() - 2], hull.back(), Pset[i]) <= 0){
               hull.pop_back(); 
           }
           hull.push_back(Pset[i]); 
        }
        upper.resize(0); 
        for(int i = lower_hull - 1; i < hull.size(); i++)
        {
           upper.push_back(hull[i]); 
        }
        reverse(upper.begin(), upper.end()); 
        return;
}
bool above(Point a, Point b, Point c)
{
   if(b.x == c.x)
   {
        return a.y >= min(b.y, c.y); 
   }
   return 1LL * (a.x - c.x) * (a.y - b.y) - 1LL * (a.x - b.x) * (a.y - c.y) <= 0;
}
bool below(Point a, Point b, Point c)
{
   if (b.x == c.x)
   {
        return a.y <= max(b.y, c.y);
   }
   return 1LL * (a.x - c.x) * (a.y - b.y) - 1LL * (a.x - b.x) * (a.y - c.y) >= 0;
}
int curra, currb;
bool inside(Point c)
{
   if(c.x < lower[0].x || c.x > lower[lower.size() - 1].x) return 0; 
   while(curra < lower.size() - 2 && lower[curra + 1].x <= c.x) curra += 1;
   if(!above(c, lower[curra], lower[curra + 1])) return 0;
   while(currb < upper.size() - 2 && upper[currb + 1].x <= c.x) currb += 1;
   if(!below(c, upper[currb], upper[currb + 1])) return 0;
   return 1;
}
void solve(){
     scanf("%d",&n); 
     vector<Point>Pset;
     for(int i = 0; i < n; i++){
          scanf("%lld%lld",&P[i].x, &P[i].y);
     }
     for(int i = n; i < 2 * n; i++)
     {
          scanf("%lld%lld", &P[i].x, &P[i].y);
     }
     sort(P, P + n);
     sort(P + n, P + 2 * n);
     int teamA, teamB;
     teamA = teamB = 0;
     for(int i = 0; i < n; i++)
     {
          Pset.push_back(P[i]); 
     }
     curra = currb = 0;
     ConvexHull(Pset);
     for(int i = n; i < 2 * n; i++)
     { 
          teamA += inside(P[i]); 
     }
     Pset.clear(); 
     for (int i = n; i < 2 * n; i++)
     {
          Pset.push_back(P[i]);
     }
     curra = currb = 0;
     ConvexHull(Pset);
     for (int i = 0; i < n; i++)
     {
          teamB += inside(P[i]);
     }
     printf("%d %d\n", teamA, teamB); 
     return;
}
signed main(void){
     solve(); 
     return 0; 
}