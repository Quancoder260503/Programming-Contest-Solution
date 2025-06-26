#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 4e5 + 10;
const int mod = 1e9 + 7;
long long n,m,k,q,component,ans;
char a[N + 1];
int timer = 1;
vector<int>S; 
long long dp[N + 1],dp1[N + 1]; 
bool vis[N + 1]; 
int in[N + 1], low[N + 1]; 
int fa[N + 1]; 
int deg[N + 1];
long long g[2001][2001];
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
vector<int>topo; 
vector<pair<int,int>>res;
long long val[N + 1];
int fa_dsu[N + 1]; 
int find(int u){
     if(u == fa_dsu[u]) return u;
     return fa[u] = find(fa_dsu[u]); 
}
void unite(int u,int v){
     u = find(u); v = find(v);
     if(u == v) return; 
     fa_dsu[v] = u; 
}
void dfs(int u){
     in[u] = low[u] = timer++;
     S.push_back(u);
     for(int i = 0; i < adj[u].size();i++){
            int v = adj[u][i];
            if(vis[v]) continue;
            if(!in[v]){
                 dfs(v);
                 low[u] = min(low[u],low[v]);
            }
            else low[u] = min(low[u],in[v]);
     }
     if(in[u] == low[u]){ 
        while(1){
             int v = S.back();
             S.pop_back();
             fa[v] = u;  
             vis[v] = 1; 
             if(u == v) break; 
        }   
    }
}
void dfs_topo(int u){
      vis[u] = 1;
      for(int i = 0; i < tadj[u].size(); i++){
           int v = tadj[u][i];
           if(vis[v]) continue; 
           dfs_topo(v); 
      }
      topo.push_back(u); 
}
void dfs_calc(int root,int u){
      vis[u] = 1; 
      if(!deg[u] and root != u) res.push_back({u,root}); 
      for(int i = 0; i < tadj[u].size(); i++){
            int v = tadj[u][i];
            if(vis[v]) continue;
            dfs_calc(root,v);
      }
}
int main(){
     scanf("%d%d",&n,&m); 
     vector<pair<int,int>>edges;
     for(int i = 1; i <= n; i++) fa_dsu[i] = i;
     for(int i = 0; i < m; i++){
          int u,v; scanf("%d%d",&u,&v);
          unite(u,v);
          adj[u].push_back(v);
          edges.push_back({u,v});
     }
     for(int i = 1; i <= n; i++) if(!in[i]) dfs(i);
     for(int i = 1; i <= n; i++) val[fa[i]]++; 
     for(int i = 1; i <= n; i++){
          for(int j = 0; j < adj[i].size(); j++){
               int v = adj[i][j];
               if(fa[v] == fa[i]); 
               tadj[fa[i]].push_back(fa[v]);
               deg[fa[i]]++;
          }
     }
     memset(vis,0,sizeof(vis));
     for(int i = 1; i <= n; i++){
           if(i == fa[i] and !vis[i]) dfs_topo(i); 
     }
     memset(vis,0,sizeof(vis));
     reverse(topo.begin(),topo.end());
     for(int i = 0; i < topo.size(); i++){
          if(!vis[topo[i]]) dfs_calc(topo[i],topo[i]); 
     }
     vector<int>pa; 
     for(int i = 1; i <= n; i++) if(fa_dsu[i] == i) pa.push_back(i);
     for(int i = 1; i < pa.size(); i++){
           res.push_back({pa[i - 1],pa[i]});
           res.push_back({pa[i],pa[i - 1]}); 
     }
     printf("%d\n",res.size());
     for(int i = 0; i < res.size(); i++){
          printf("%d %d \n",res[i].first,res[i].second); 
     }
     return 0; 
} 