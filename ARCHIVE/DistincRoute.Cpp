#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
const int N = 5e3 + 10;
#define double long double
const long long INF = 1e14 + 1;
typedef pair<int,int> pii;
int n,q,k,a,b,m,s,t;
const double eps = 1e-9; 
int bit[N + 1];
vector<int>adj[N + 1];
vector<pair<int,int>>adj1[N + 1]; 
long long weight[N + 1][N + 1]; 
vector<int>path;
int fa[N + 1];
bool vis[N + 1]; 
long long bfs(int src = s,int tar = t){
     queue<pair<int,long long>>q;
     fill(fa + 1, fa + n + 1, 0); 
     q.push({src,INF});
     while(q.size()){
         int node; long long aug; 
         tie(node,aug) = q.front();
         q.pop(); 
         for(int i = 0; i < adj[node].size(); i++){
              int u = adj[node][i]; 
              if(!fa[u] && weight[node][u] > 0){
                    aug = min(aug , weight[node][u]);
                    fa[u] = node; 
                    if(u == tar) return aug; 
                    q.push({u,aug}); 
              }
         }
     }
     return 0; 
}
long long maxflow(){
      long long flow = 0; 
      long long aug = 0;
      while(aug = bfs()){
           int g = t; 
           flow += aug;
           while(s != g){
               weight[fa[g]][g] -= aug; 
               weight[g][fa[g]] += aug; 
               g = fa[g]; 
           }
      }
      return flow;
}
void dfs(int src = 1){
      path.push_back(src); 
      if(src == N) return; 
      for(int i = 0; i < adj1[src].size(); i++){
          int v = adj1[src][i].first;
          int id = adj1[src][i].second; 
          if(weight[src][v] == 0 && !vis[id]){
               vis[id] = 1;
               dfs(v); 
               break;
          }
      }
}
signed main(){
      scanf("%d%d",&n,&m);
      for(int i = 0; i < m; i++){
           int u,v; scanf("%d%d",&u,&v);
           adj[u].push_back(v);
           adj[v].push_back(u);
           adj1[u].push_back({v,i}); 
           weight[u][v]++; 
      }
      s = 1; t = n;       
      long long flow = maxflow(); 
      printf("%lld\n",flow); 
      for(int i = 0; i < flow; i++){
           path.clear();
           dfs(1); 
           printf("%zu\n",path.size()); 
           for(int i = 0; i < path.size(); i++) printf("%d ",path[i]); 
           printf("\n");
      }
      return 0;
}