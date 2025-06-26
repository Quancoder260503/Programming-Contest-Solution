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
long long Rotating(vector<Point> &cvhull){ 
      int n = cvhull.size();  
      long long ans = 0; 
      for(int i = 0; i < n; i++){
           int r = (i + 2) % n;
           int l = i;
           for(int j = i + 2; j < n; j++){
               long long S1 = abs(cross3(cvhull[i],cvhull[l],cvhull[j]));
               long long S2 = abs(cross3(cvhull[i],cvhull[j],cvhull[r]));
               while(abs(cross3(cvhull[i],cvhull[l],cvhull[j])) < abs(cross3(cvhull[i],cvhull[(l + 1) % n],cvhull[j]))){
                     l = (l + 1) % n; 
                     S1 = abs(cross3(cvhull[i],cvhull[l],cvhull[j]));
               }    
               while(abs(cross3(cvhull[i],cvhull[j],cvhull[r])) < abs(cross3(cvhull[i], cvhull[j], cvhull[(r + 1) % n]))){
                     r = (r + 1) % n; 
                     S2 = abs(cross3(cvhull[i],cvhull[j],cvhull[r]));
               }
               ///cout << i << " " << j << " " << l << " " << r << " " << S1 << " " << S2 << endl; 
               ans = max(ans, S1 + S2);
           }
      }
      return ans;
}
void solve(){
     // Rotating Calipers
     vector<Point>Pset;
     scanf("%d",&n);
     for(int i = 0; i < n; i++){
           scanf("%lld %lld",&P[i].x,&P[i].y);
           Pset.push_back(P[i]); 
     }
     vector<Point>cvhull = ConvexHull(Pset);
     long long ans  = Rotating(cvhull);
     if(ans % 2 == 0){
          printf("%d\n",ans / 2); 
     }
     else{
         double res = (double) (ans / 2.0);
         printf("%0.1lf\n",res);   
     }
     return;
}
signed main(void){
     int t; scanf("%d",&t); 
     while(t--){ 
          solve(); 
     }
     return 0; 
}