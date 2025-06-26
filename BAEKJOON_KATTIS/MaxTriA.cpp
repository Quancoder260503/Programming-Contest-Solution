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
vector<Point> ConvexHull(vector<Point>& Pset){ 
        sort(Pset.begin(),Pset.end());
        Pset.erase(unique(Pset.begin(),Pset.end()),Pset.end());
        int n = Pset.size();
        // lower - hull
        vector<Point>hull;
        for(int i = 0; i < n; i++){
              while(hull.size() > 1 && cross3(hull[hull.size() - 2], hull.back(), Pset[i]) <= 0){
                    hull.pop_back(); 
              }
              hull.push_back(Pset[i]); 
        }
        int lower_hull = hull.size();
        for(int i = n - 2; i >= 0; i--){
              while(hull.size() > lower_hull && cross3(hull[hull.size() - 2], hull.back(), Pset[i]) <= 0){
               hull.pop_back(); 
           }
           hull.push_back(Pset[i]); 
        }
        hull.pop_back(); 
        return hull; 
}
ldb Rotating(vector<Point> &cvhull){ 
      int n = cvhull.size(); 
      ldb ans = 0.0; 
      for(int i = 0; i < n; i++){ 
          int nxt  = (i + 1) % n;
          int tnxt = (nxt + 1) % n; 
          while(nxt != i && tnxt != i){
             ans = max(ans, fabsl(cross(cvhull[nxt] - cvhull[i], cvhull[tnxt] - cvhull[i]))); 
             while(cross(cvhull[i] - cvhull[nxt],cvhull[(tnxt + 1) % n] - cvhull[tnxt]) < 0){
                    tnxt = (tnxt + 1) % n; 
             }
             nxt = (nxt + 1) % n;  
          }
      }
      return ans;
}
void solve(){
     // Rotating Calippers
     vector<Point>Pset;
     for(int i = 0; i < n; i++){
           scanf("%lld %lld\n",&P[i].x,&P[i].y);
           Pset.push_back(P[i]); 
     }
     vector<Point>cvhull = ConvexHull(Pset);
     ldb ans = Rotating(cvhull) / 2.0;
     printf("%0.3llf\n",ans); 
     return;
}
signed main(void){
     while(true){
        scanf("%lld",&n);
        if(n < 0) break;  
        solve();
     }
     return 0; 
}