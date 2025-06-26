#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 1500000
#define inf 10000000000000
#define x first 
#define y second
typedef long double ldb;
typedef pair<long long,long long> Vec; 
const int mod = 1e9 + 7; 
long long finv[N];
long long fac[N];
long long inv[N]; 
int n,k,cur;  
typedef struct { 
    int xc,yc,cost;
} Point;
Vec operator - (Vec AB, Vec AC){
    return Vec(AB.x - AC.x, AB.y - AC.y); 
}
long long cross(Vec AB, Vec AC) {
    return (1ll) * AB.x * AC.y - (1ll) * AB.y * AC.x; 
}
long long norm(Point AB){
    return 1ll * AB.xc * AB.xc + 1ll * AB.yc * AB.yc; 
}
long long cross3(Point AB, Point AC, Point BC) {
    Vec X = Vec(AC.xc - AB.xc, AC.yc - AB.yc); 
    Vec Y = Vec(BC.xc - AB.xc, BC.yc - AB.yc); 
    return  cross(X,Y);
}
long long dist(Point AB, Point AC){
      return (1ll) * (AB.xc - AC.xc) * (AB.xc - AC.xc) + (1ll) * (AB.yc - AC.yc) * (AB.yc - AC.yc); 
}
Point P[N]; 
int type(Vec A){
    if(A.x >= 0 && A.y >= 0) return 0;
    if(A.x <= 0 && A.y > 0)  return 1; 
    if(A.x < 0  && A.y <= 0) return 2;
    if(A.x >= 0 && A.y < 0)  return 3;
}
bool cmp(const Point &a, const Point &b){
     long long w = cross3(P[cur], a , b); 
     return w == 0 ? dist(P[cur],a) < dist(P[cur],b) : w > 0; 
}
bool cmpx(const Point &a, const Point &b){
     Vec AB = Vec(a.xc - P[cur].xc, a.yc - P[cur].yc);
     Vec AC = Vec(b.xc - P[cur].xc, b.yc - P[cur].yc);
     return type(AB) == type(AC) ? cmp(a,b) : type(AB) < type(AC); 
}
signed main(){
     scanf("%d",&n); 
     long long sum = 0;
     for(int i = 0; i < n; i++){
         scanf("%d%d%d",&P[i].xc,&P[i].yc,&P[i].cost);
         sum += P[i].cost; 
     }
     long long ans = inf;
     for(int i = 0; i < n; i++){
           vector<Point>Pset;
           cur = i; 
           for(int j = 0; j < n; j++){
                if(i == j) continue; 
                Pset.push_back(P[j]); 
           }
           sort(Pset.begin(),Pset.end(),cmpx);
           long long lower = sum; 
           long long upper =  P[cur].cost + Pset[0].cost; 
           int nxt = 1;
           for(int j = 0; j < Pset.size(); j++){ 
                while(nxt != j && cross3(P[cur],Pset[j],Pset[nxt]) > 0){
                     upper += Pset[nxt].cost; 
                     lower -= Pset[nxt].cost;
                     nxt = (nxt + 1) % Pset.size(); 
                }
                ans = min(ans, abs(upper - lower));
                upper -= Pset[j].cost; 
                lower += Pset[(j + 1) % Pset.size()].cost;                  
           }
     }
     printf("%lld\n",ans); 
     return 0; 
}