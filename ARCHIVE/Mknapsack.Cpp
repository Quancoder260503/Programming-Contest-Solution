#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<long long,long long> pii;
const int N = 1e7 + 100;
const int INF = 1e7 + 10; 
const int mod = 1e9 + 7;
long long n,m,tot;
int timer = 1;
long double dp[N + 1]; 
vector<long long>lf,ri; 
long long a[N + 1]; 
long long f[N + 1];
long long W[N + 1],V[N + 1];
vector<pii> subset(int l,int r){
    int n = r - l + 1;
    vector<pii> res; 
    for(int mask = 0; mask < (1 << n); mask++){
         long long sum = 0; 
         long long val = 0; 
         for(int j = l; j <= r; j++){
              if(mask & (1 << (j - l))){
                   sum += W[j];
                   val += V[j]; 
              }
         }
         res.push_back({sum,val});
    }
    return res; 
}
int main(){
       scanf("%d%lld",&n,&m);
       for(int i = 1; i <= n; i++) scanf("%lld%lld",&W[i],&V[i]);
       vector<pii> lf = subset(1, n / 2);
       vector<pii> ri = subset(n / 2 + 1, n);
       sort(lf.begin(),lf.end());
       sort(ri.begin(),ri.end()); 
       int ptr = 0;
       long long ans = 0; 
       long long mx = 0; 
       for(int i = lf.size() - 1; i >= 0; i--){
             while(ptr < ri.size() and lf[i].first + ri[ptr].first <= m){
                    mx = max(mx, ri[ptr].second); 
                    ptr++; 
             }
             if(lf[i].first <= m) ans = max(ans, mx + lf[i].second); 
       }
       printf("%lld",ans); 
}