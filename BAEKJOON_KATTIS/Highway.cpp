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
long long finv[N];
long long fac[N];
long long inv[N]; 
int n,k;  
// this is the correct algorithm for finding convex diameter

Vec operator - (Vec AB, Vec AC){
    return Vec(AB.x - AC.x, AB.y - AC.y); 
}
long long cross(Vec AB, Vec AC) {
    return (1ll) * AB.x * AC.y - (1ll) * AB.y * AC.x; 
}
long long cross3(Vec AB, Vec AC, Vec BC) {
    Vec X = AC - AB; 
    Vec Y = BC - AB; 
    return  cross(X,Y);
}
using Point = Vec;
Point P[N]; 
long long dist(Vec AB, Vec AC){
      return (1ll) * (AB.x - AC.x) * (AB.x - AC.x) + (1ll) * (AB.y - AC.y) * (AB.y - AC.y); 
}
long long Rotating(vector<Point> &cvhull){ 
      int n = cvhull.size(); 
      long long ans = -1;
      int nxt = 0;
      Point s,e;
      for(int i = 0; i < n; i++){ 
           while(cross3({0,0}, cvhull[(i + 1) % n] - cvhull[i], cvhull[(nxt + 1) % n] - cvhull[nxt]) > 0){
                long long d0 = dist(cvhull[i],cvhull[nxt]); 
                if(ans < d0){
                    ans = d0; 
                    s = cvhull[i];
                    e = cvhull[nxt]; 
                }
                nxt = (nxt + 1) % n;
           }
           long long d0 = dist(cvhull[i],cvhull[nxt]); 
           if(ans < d0){
               ans = d0;
               s = cvhull[i];
               e = cvhull[nxt]; 
           }
      }
      printf("%lld %lld %lld %lld \n",s.x,s.y,e.x,e.y);
      return ans;
}
bool cmp(const Point &a, const Point &b){ 
      long long w = cross3(P[0],a,b);
      return w == 0 ? dist(P[0],a) < dist(P[0],b) : w > 0; 
}
void solve(){
     // Rotating Calippers
     scanf("%lld",&n);
     for(int i = 0; i < n; i++){
           long long x,y;
           scanf("%lld %lld",&P[i].x,&P[i].y);
     }
     swap(P[0], *min_element(P,P + n));
     sort(P + 1, P + n,cmp); 
     vector<Point>hull;
     for(int i = 0; i < n; i++){
              while(hull.size() > 1 && cross3(hull[hull.size() - 2], hull.back(), P[i]) <= 0){
                    hull.pop_back(); 
              }
              hull.push_back(P[i]); 
    }
     Rotating(hull); 
     return;
}
signed main(void){
     int t; 
     scanf("%d",&t);
     while(t--){
        solve(); 
     }
     return 0; 
}