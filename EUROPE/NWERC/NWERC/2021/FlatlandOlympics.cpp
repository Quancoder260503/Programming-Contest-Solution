#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 1500000
#define inf 10000000000000
#define xc first 
#define yc second
typedef long double ldb;
typedef pair<long long,long long> Vec; 
const int mod = 1e9 + 7; 
long long finv[N];
long long fac[N];
long long inv[N]; 
int n,k,cur;  
using Point = Vec;
Point s,e;
long long bit[N];
long long sum(int i){
	     long long c = 0;
	     for(++i; i > 0 ; i -= (i & -i)){
		    c = (c + bit[i]);
         }
	     return c;
}
long long query(int l, int r){
     return sum(r) - sum(l - 1); 
}
void upd(int i,int dif) {
	  for(++i; i < N ; i += (i & -i)){
		   bit[i] = (dif + bit[i]);
      }
}
Vec operator - (Vec AB, Vec AC){
    return Vec(AB.xc - AC.xc, AB.yc - AC.yc); 
}
long long cross(Vec AB, Vec AC) {
    return (1ll) * AB.xc * AC.yc - (1ll) * AB.yc * AC.xc; 
}
long long dot(Vec AB, Vec AC){
    return 1ll * AB.xc * AC.xc + 1ll * AB.yc * AC.yc;
}
long long norm(Point AB){
    return 1ll * AB.xc * AB.xc + 1ll * AB.yc * AB.yc; 
}
long long cross3(Point AB, Point AC, Point BC) {
    Vec X = AC - AB;
    Vec Y = BC - AB;
    return  cross(X,Y);
}
long long dist(Point AB, Point AC){
      return (1ll) * (AB.xc - AC.xc) * (AB.xc - AC.xc) + (1ll) * (AB.yc - AC.yc) * (AB.yc - AC.yc); 
}
Point P[N]; 
int type(Vec A){
    if(A.xc >= 0 && A.yc >= 0) return 0;
    if(A.xc <= 0 && A.yc > 0)  return 1; 
    if(A.xc < 0  && A.yc <= 0) return 2;
    if(A.xc >= 0 && A.yc < 0)  return 3;
}
bool cmpe(const Point &a, const Point &b){
     return cross3(e,a,b) ==  0 ? cross3(s,a,b) < 0 : cross3(e,a,b) > 0;
}
bool cmps(const Point &a, const Point &b){
     return cross3(s,a,b) ==  0 ? cross3(e,a,b) < 0 : cross3(s,a,b) > 0;
}
signed main(){
     scanf("%lld%lld%lld%lld",&s.xc,&s.yc,&e.xc,&e.yc); 
     scanf("%d",&n); 
     for(int i = 0; i < n; i++){
         scanf("%lld%lld",&P[i].xc,&P[i].yc);
     }
     vector<Point>upper;
     vector<Point>lower; 
     int left = 0; 
     int right = 0;
     for(int i = 0; i < n; i++){
          if(cross3(s,e,P[i]) > 0){
              upper.push_back(P[i]);
          }
          else if(cross3(s,e,P[i]) < 0){
              lower.push_back(P[i]); 
          }
          else{
              if(dot(e - s,P[i] - s) > 0) right++; 
              else left++;
          }
     }
     long long ans = 0;
     vector<Point>p = upper; 
     sort(p.begin(),p.end(),cmpe);
     vector<Point>q = upper;
     sort(q.begin(),q.end(),cmps); 
     map<Point,int>mp;
     int cnt = 0;
     for(int i = 0; i < p.size(); i++){
             mp[p[i]] = cnt++; 
     }
     for(int i = 0; i < q.size(); i++){
             ans += query(mp[q[i]],upper.size()); 
            upd(mp[q[i]],1); 
     }
     mp.clear();
     p.resize(0);
     q.resize(0);
     memset(bit,0,sizeof(bit)); 
     p = lower;
     sort(p.begin(),p.end(),cmpe);
     q = lower; 
     sort(q.begin(),q.end(),cmps); 
     cnt = 0;
     for(int i = 0; i < p.size(); i++){
             mp[p[i]] = cnt++; 
     }
     for(int i = 0; i < q.size(); i++){
            ans += query(mp[q[i]],lower.size()); 
            upd(mp[q[i]],1); 
     }
     ans += 1ll * left * (left - 1) / 2; 
     ans += 1ll * right * (right - 1) / 2;
     printf("%lld\n",ans); 
     return 0; 
}