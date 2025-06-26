#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
#define blksz 500
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 110;
const int M = 24;
long long dp[N][2];
int fa[N];
bool vis[N]; 
vector<int>adj[N]; 
int n,m;
int find(int u){
    return u == fa[u] ? u : fa[u] = find(fa[u]); 
}
void dfs(int u,int p){
      if(!vis[u]) dp[u][1] += 1; 
      for(int i = 0; i < adj[u].size(); i++){
           int v = adj[u][i];
           if(v == p) continue;   
           dfs(v, u);
           dp[u][0] += max(dp[v][0], dp[v][1]);
           dp[u][1] += dp[v][0]; 
      }     
}
int main(){
      scanf("%d%d",&n,&m);
      for(int i = 1; i <= n; i++) fa[i] = i;
      vector<pair<int,int>>edges;
      for(int i = 0; i < m; i++){
            int u,v; scanf("%d%d",&u,&v);
            int ku = find(u); int kv = find(v); 
            if(ku == kv){
                 edges.push_back({u,v}); 
            }
            else{
               fa[ku] = kv; 
               adj[u].push_back(v); 
               adj[v].push_back(u); 
            }
      }
      int fmask = (1 << (int) edges.size()); 
      long long ans = 0;
      for(int mask = 0; mask < fmask; mask++){
             memset(dp,0,sizeof(dp));
             memset(vis,0,sizeof(vis)); 
             for(int i = 0; i < (int) edges.size(); i++){
                   if((1 << i) & mask){
                        vis[edges[i].first] = true; 
                   }
                   else{ 
                        vis[edges[i].second] = true;
                   }
             }
             dfs(1,0); 
             ans = max(ans, max(dp[1][1],dp[1][0])); 
      } 
      printf("%lld\n",ans); 
      return 0;
}