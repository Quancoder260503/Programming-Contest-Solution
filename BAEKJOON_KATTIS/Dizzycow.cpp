#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define mp make_pair
#define N 1500000
#define inf 10000000000
#define x first 
#define y second
typedef pair<long long,long long> Vec; 
typedef long double ldb;
const int mod = 1e9 + 7; 
vector<int> adj[N];
int A[N];  
int n,k,m;
int in[N],low[N]; 
bool vis[N]; 
int fa[N];
int component;
int timer = 1;
vector<int>topo;
vector<int>S;
map<int,int>ADJ[N];
void dfs(int u){
    vis[u] = 1;
    for(int i = 0; i < adj[u].size(); i++){
         int v = adj[u][i]; 
         if(!vis[u]) dfs(v); 
    }
    topo.push_back(u); 
} 
void dfs_scc(int u){
     in[u] = low[u] = timer++;
     S.push_back(u);
     for(int i = 0; i < adj[u].size();i++){
            int v = adj[u][i];
            if(vis[v]) continue;
            if(!in[v]){
                 dfs_scc(v);
                 low[u] = min(low[u],low[v]);
            }
            else low[u] = min(low[u],in[v]);
     }
     if(in[u] == low[u]){ 
        component++;
        while(true){
             int v = S.back();
             S.pop_back();
             vis[u] = 1;
             if(u == v) break; 
        }   
    }
}
signed main(void){
     scanf("%d%d%d",&n,&k,&m); 
     for(int i = 0; i < k; i++){
          int u,v; scanf("%d%d",&u,&v); 
          adj[u].push_back(v); 
          ADJ[u][v] = 1;
     }
     // use tarjan algorithm's to check if their is circle contain in the original graph
     for(int i = 1; i <= n; i++){
           if(!vis[i]) dfs(i); 
     } 
     memset(vis,0,sizeof(vis)); 
     for(int i = 1; i <= n; i++){
          if(!in[i]) dfs_scc(i); 
     }
     if(component > n){
         printf("-1\n");
         return 0; 
     }
     reverse(topo.begin(),topo.end()); 
     vector<pair<int,int> >edges;
     for(int i = 0; i < m; i++){
          int u,v; scanf("%d%d",&u,&v);
          if(ADJ[v][u] == 1){
               printf("-1\n");
               return 0;
          }
          int posu = lower_bound(topo.begin(),topo.end(),u) - topo.begin(); 
          int posv = lower_bound(topo.begin(),topo.end(),v) - topo.begin();
          if(posu < posv) edges.push_back(mp(u,v));
          else edges.push_back(mp(v,u)); 
     }
     for(int i = 0; i < (int) edges.size(); i++){
         printf("%d %d\n",edges[i].first,edges[i].second);
     }
     return 0; 
}