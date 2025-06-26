#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 5;
const int M = 1e6 + 5;
const int mod = 1e9 + 7; 
long long n,m,k,q,x;
long long dp[N + 1]; 
long long bit[N + 1];
int up[21][N + 1]; 
vector<int>adj[N]; 
long long finv[N],fac[N],inv[N]; 
void dfs_calc(int u){
    for(int i = 1; i < 23 ; i++){
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i]; 
        if(v == up[0][u]) continue;
        dp[v] = dp[up[0][v] = u] + 1;
        dfs_calc(v);
    } 
}
int lca(int a,int b){
     if(dp[a] < dp[b]) swap(a,b);
     int d = dp[a] - dp[b];
     for(int i = 0; i < 23; i++){
         if(d & (1 << i)) a = up[i][a]; 
     }
     if(a == b) return a; 
     for(int i = 22; i >= 0; i--){
         int ta = up[i][a]; int tb = up[i][b];
         if(ta != tb){
              a = ta;
              b = tb; 
         }
     }
     return up[0][a]; 
}
int main(){
     scanf("%d%d",&n,&q);
     for(int i = 0; i < n - 1; i++){
          int u,v; scanf("%d%d",&u,&v);
          adj[u].push_back(v);
          adj[v].push_back(u); 
     }
     dfs_calc(1);
     for(int i = 0; i < q; i++){
          int u,v; scanf("%d%d",&u,&v);
          long long dist = dp[u] + dp[v] - 2 * dp[lca(u,v)] + 1;
          long long ans = 1ll * dist * (dist - 1) / 2 + n;
          printf("%lld\n",ans); 
     } 
     return 0; 
}