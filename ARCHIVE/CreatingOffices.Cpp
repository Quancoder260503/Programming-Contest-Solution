#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
#define blksz 500;
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
const int inf = 1e7 + 5;
const int mod = 1e9 + 7;
long long n,m,k,q,p,d;
vector<int>adj[N + 1]; 
long long a[N + 1];
int dp[N + 1]; 
int opt[N + 1];
int trs[N + 1];
int fa[N + 1]; 
int timer = 1;
bool vis[N + 1]; 
int up[17][N + 1]; 
long long ans; 
int in[N + 1];
int out[N + 1];
int get_centroid(int u,int p,int n){
       for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(v == p || vis[v]) continue; 
            if(trs[v] > n / 2) return get_centroid(v,u,n); 
        }
        return u;
}
int get_size(int u, int p) {
     if(vis[u]) return 0;
     trs[u] = 1;
     for(int i = 0; i < adj[u].size(); i++){
         int v = adj[u][i]; 
         if(v == p) continue;
         trs[u] += get_size(v, u);
     }
     return trs[u];
}
void dfs(int u,int p){
       in[u] = timer++; 
       for(int i = 1; i < 17; i++){
          up[i][u] = up[i - 1][up[i - 1][u]]; 
       }
       for(int i = 0; i < adj[u].size(); i++){
             int v = adj[u][i];
             if(v == p) continue;
             dp[v] = dp[up[0][v] = u] + 1;
             dfs(v,u); 
       }
       out[u] = timer - 1;
}
int jump(int x,int d){
     for(int i = 0; i < 17 ; i++){
        if( (d >> i) & 1) x = up[i][x];
    }
    return x;
}
int lca(int a, int b){
    if(dp[a] < dp[b]) swap(a,b);
    if(in[b] <= in[a] && in[a] <= out[b]) return b;
    a = jump(a,dp[a] - dp[b]); 
    if(a == b) return a;
    for(int i = 16; i >= 0; i--){
         int tA = up[i][a]; int tB = up[i][b];
         if(tA != tB) {
            a = tA; b = tB;
         }
    } 
    return up[0][a];
}  
void build(int u,int p){
    int sz = get_size(u,p);
    int c = get_centroid(u,p,sz);
    vis[c] = 1;
    fa[c] = p;   
    for(int i = 0; i < adj[c].size(); i++){
         int v = adj[c][i]; 
         if(vis[v]) continue; 
         build(v,c); 
    }
} 
int query(int u){
     int v = u; 
     int ans = inf;
     while(v){
          ans = min(ans, opt[v] + dp[v] + dp[u] - 2 * dp[lca(u,v)]); 
          v = fa[v];
     }
     return ans;
}
void update(int u){
     int v = u; 
     opt[v] = 0;
     while(v){
          v = fa[v]; 
          opt[v] = min(opt[v], dp[v] + dp[u] - 2 * dp[lca(u,v)]); 
     }
     return;
}
signed main(){
      scanf("%d%d",&n,&d);
      for(int i = 1; i < n; i++){
           int u,v ; scanf("%d%d",&u,&v);
           adj[u].push_back(v);
           adj[v].push_back(u); 
      }
      dfs(1,0);  
      vector<pair<int,int>>queries;
      for(int i = 1; i <= n; i++){ 
           queries.push_back({dp[i],i}); 
      }
      sort(queries.rbegin(),queries.rend());
      vector<int>res;
      build(1,0); 
      for(int i = 1; i <= n; i++) opt[i] = inf;
      for(int i = 0; i < queries.size(); i++){
            auto v = queries[i]; 
            if(query(v.second) < d) continue;
            update(v.second); 
            res.push_back(v.second);
      }
       printf("%zu\n",res.size()); 
       for(int i = 0; i < res.size(); i++) printf("%lld ",res[i]); 
      //printf("\n"); 
      return 0;
}