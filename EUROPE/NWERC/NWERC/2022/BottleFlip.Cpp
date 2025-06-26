#include "bits/stdc++.h"
#include <iostream> 
#include<vector>
#define blksz 500;
using namespace std;
typedef long double ld; 
const int N = 3e5 + 10;
const int inf = 1e7 + 5;
const int mod = 1e9 + 7;
const double eps = 3e-14; 
long long n,m,l,r,da,dw,h;
vector<int>adj[N + 1];  
vector<int>dv[N + 1]; 
map<pair<int,int>,int>dp[N + 1];
long long A[N + 1];
ld f(ld x){
       ld p = ((ld) h - x / 2.0) * (ld) da * x + (((ld)h - x) / 2.0) * (ld) dw * ((ld)h - x);
       ld q = x *(ld) da + (ld) dw * ((ld) h - x);
       return (p / q);
}
signed main(){
      scanf("%d%d%d%d",&h,&r,&da,&dw);
      ld l = 0; 
      ld r = h; 
      while(r - l >= eps){
            ld x1 = l + (r - l) / 3.0; 
            ld x2 = r - (r - l) / 3.0;
            if(f(x1) < f(x2)) r = x2; 
            else l = x1; 
      }
      cout << setprecision(15) << f(l) << endl; 
      return 0;
}