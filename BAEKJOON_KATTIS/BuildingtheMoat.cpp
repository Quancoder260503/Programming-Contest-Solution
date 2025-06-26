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
long long dist(Vec AB, Vec AC){
    return (1ll) * (AB.x - AC.x) * (AB.x - AC.x) + (1ll) * (AB.y - AC.y) * (AB.y - AC.y); 
}
void solve(){
     scanf("%d",&n); 
     vector<Point>Pset;
     for(int i = 0; i < n; i++){
          scanf("%lld %lld",&P[i].x,&P[i].y); 
          Pset.push_back(P[i]); 
     }
     vector<Point>cvhull = ConvexHull(Pset); 
     int n = cvhull.size(); 
     ldb tot = 0; 
     for(int i = 0; i < n; i++){ 
          tot += (ldb) sqrt((ldb) dist(cvhull[i],cvhull[(i + 1) % n]));
     }
     printf("%0.2llf\n",tot); 
     return;
}
signed main(void){
     solve(); 
     return 0; 
}