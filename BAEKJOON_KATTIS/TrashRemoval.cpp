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
long long dist(Vec AB, Vec AC){
    return 1ll * (AC.x - AB.x) *(AC.x - AB.x) + 1ll * (AC.y - AB.y) * (AC.y - AB.y);
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
bool check(Point A, Point B, Point C){
      Vec BA = B - A; 
      Vec BC = B - C; 
      return 1ll * BA.x * BC.x + 1ll * BA.y * BC.y >= 0; 
}
double solve(){
     vector<Point>Pset;
     for(int i = 0; i < n; i++){
          scanf("%lld%lld",&P[i].x, &P[i].y);
          Pset.push_back(P[i]); 
     }
     vector<Point>cvhull = ConvexHull(Pset);
     double ans = (double) 1e9 ;
     for(int i = 0; i < cvhull.size(); i++){
          //cout << cvhull[i].x << ' ' << cvhull[i].y << endl;
          int r = (i + 2) % cvhull.size();
          int l = i;
          for(int j = i + 2; j < cvhull.size(); j++){
              long long S1 = fabs(cross3(cvhull[i],cvhull[l],cvhull[j]));
              long long S2 = fabs(cross3(cvhull[i],cvhull[r],cvhull[j]));
              while(fabs(cross3(cvhull[i],cvhull[l],cvhull[j])) < fabs(cross3(cvhull[i],cvhull[(l + 1) % cvhull.size()],cvhull[j])) ){
                   l = (l + 1) % cvhull.size(); 
                   S1 = fabs(cross3(cvhull[i],cvhull[l],cvhull[j]));
              }
              while(fabs(cross3(cvhull[i],cvhull[r],cvhull[j])) < fabs(cross3(cvhull[i],cvhull[(r + 1) % cvhull.size()],cvhull[j]))){
                   r = (r + 1) % cvhull.size(); 
                   S2 = fabs(cross3(cvhull[i],cvhull[r],cvhull[j])); 
              }
           ///   cout << i << ' ' << j << " " << l << " " << r << " " << (double) (S1 + S2) / (double) sqrt(dist(cvhull[i],cvhull[j]))<< endl; 
              ans = min(ans, (double) (S1 + S2) / (double) sqrt(dist(cvhull[i],cvhull[j])));             
          }
     }
     for(int i = 0; i < cvhull.size(); i++){
             double cur = 0.0;
             for(int j = 0; j < cvhull.size(); j++){
                    double S = fabs(cross3(cvhull[i],cvhull[(i + 1) % n],cvhull[j]));
                    cur = max(cur, S / (double) sqrt(dist(cvhull[i],cvhull[(i + 1) % n])));  
             }
              //cout << cur << ' ' << i << endl;
              ans = min(ans, cur); 
     }
     // O(N ^ 2 * log(N)); 
     //ans = ans * 2.0; 
     return ans;
}
signed main(void){
    int cnt = 0; 
     while(true){
        scanf("%d",&n); 
        if(!n) break;
        cnt += 1;
        double res = solve();
        printf("Case %d: %.2lf\n",cnt,res + 5e-3 - 1e-6); 
     }
     return 0; 
}