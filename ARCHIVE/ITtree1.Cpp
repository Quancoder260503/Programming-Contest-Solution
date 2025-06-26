#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 100;
const int INF = 1e7 + 10; 
long long n,m,q,dsz,M,res;
int timer = 1;
vector<pair<int,int>>adj[N + 1];
int fa[N + 1], comp[N + 1];
bool vis[N + 1];
int up[22][N + 1],dp[N + 1],val[N + 1];
void dfs(int u,int p){
      if(adj[u].empty()) dp[u] = INF; 
      for(int i = 0; i < adj[u].size(); i++){
           auto v = adj[u][i];
           dfs(v.first,u);
           dp[u] += min(dp[v.first],v.second); 
      }
}
void solve(){
      scanf("%d",&n);  
      for(int i = 1; i <= n; i++){
          adj[i].resize(0);
          dp[i] = 0; 
      }
      for(int i = 2; i <= n ; i ++){
           int u,c; scanf("%d%d",&u,&c);
           adj[u].push_back({i,c}); 
      }
      dfs(1,0);
      double ans = (long double) dp[1]; 
      if(n == 1) ans = 0.00;
      printf("%.2f \n",ans); 
}
int main(){
     int t; scanf("%d",&t);
     while(t--){
          solve(); 
     }
}