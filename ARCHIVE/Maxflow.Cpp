#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
const int N = 5e3 + 10;
#define double long double
const long long INF = 1e14 + 1;
typedef pair<int,int> pii;
int n,q,k,a,b,m;
const double eps = 1e-9; 
int bit[N + 1];
vector<int>adj[N + 1];
long long weight[N + 1][N + 1]; 
int fa[N + 1];
long long bfs(int src = 1,int tar = n){
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
signed main(){
      scanf("%d%d",&n,&m);
      for(int i = 0; i < m; i++){
           int u,v,w; scanf("%d%d%d",&u,&v,&w);
           adj[u].push_back(v);
           adj[v].push_back(u);
           weight[u][v] += w; 
      }
      long long flow = 0; 
      long long aug = 0;
      while(aug = bfs()){
           int t = n; 
           flow += aug;
           while(t != 1){
               weight[fa[t]][t] -= aug; 
               weight[t][fa[t]] += aug; 
               t = fa[t]; 
           }
      }
      printf("%lld\n",flow); 
      return 0;
}