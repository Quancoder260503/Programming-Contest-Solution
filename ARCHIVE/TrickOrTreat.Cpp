#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
#define blksz 500
#define f first
#define s second
#include <ext/pb_ds/assoc_container.hpp>
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
pair<ld,ld>point[N + 1]; 
ld f(ld x){
      ld ans = 0;
      for(int i = 1; i <= n; i++){
           ans = max(ans, (x - point[i].f) * (x - point[i].f) + point[i].s * point[i].s); 
      }
      return (ld) sqrt(ans); 
}
signed main(){
      ios_base::sync_with_stdio(0);
	    cin.tie(0);
      while(cin >> n){
           if(n == 0) break;
           for(int i = 1; i <= n; i++){
                cin >> point[i].f >> point[i].s; 
           }
           ld l = -2e5 - 1; 
           ld r = 2e5 + 1; 
           while(r - l >= eps){
              ld x1 = l + (r - l) / 3.0; 
              ld x2 = r - (r - l) / 3.0;
              if(f(x1) < f(x2)) r = x2; 
              else l = x1; 
           }
           if(f(0) < f(l)) l = 0;
           cout << setprecision(10) << l << " ";
           cout << setprecision(10) << f(l) << endl; 
      }
      return 0;
}