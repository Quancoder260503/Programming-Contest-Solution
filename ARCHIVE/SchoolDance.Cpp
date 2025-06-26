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
long long weight[N + 1][N + 1]; 
vector<int>path;
int fa[N + 1];
bool vis[N + 1];
int match[N + 1]; 
bool kuhn(int u){
    if(vis[u]) return false;  
    vis[u] = true;
    for(int i = 0; i < adj[u].size(); i++){
         int v = adj[u][i];
         if(!match[v] | kuhn(match[v])){
              match[v] = u; 
              return true;
         }
    }
    return false;
}
signed main(){
      scanf("%d%d%d",&n,&m,&k);
      for(int i = 0; i < k; i++){
           int u,v; scanf("%d%d",&u,&v);
           adj[u].push_back(v);
      }
      for(int i = 1; i <= n; i++){
            fill(vis + 1, vis + n + 1,0);
            kuhn(i); 
      }
      vector<pair<int,int>>matches; 
      for(int i = 1; i <= m; i++){
           if(match[i]) matches.push_back({match[i],i}); 
      }
      printf("%zu\n",matches.size());
      for(int i = 0; i < matches.size(); i++){
           printf("%d %d\n",matches[i].first, matches[i].second); 
      }
      return 0;
}