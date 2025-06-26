#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
#define blksz 500
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 10002;
const int M = 24;
long long dp[N];
int fa[N];
bool vis[N]; 
long long A[N]; 
int deg[N]; 
vector<int>adj[N]; 
int n,m;
// topological sorting 
// find the maximum time among all components
long long DP(int u){
      if(dp[u] >= 0) return dp[u];
      long long st = 0; 
      for(int i = 0; i < adj[u].size(); i++){
            st = max(st, DP(adj[u][i])); 
      }
      return dp[u] = st + A[u]; 
}
int main(){
      scanf("%d%d",&n,&m);
      memset(dp,-1,sizeof(dp)); 
      for(int i = 0; i < n; i++) scanf("%lld",&A[i]);
      for(int i = 0; i < m; i++){
            int u,v; scanf("%d%d",&u,&v);
            adj[--v].push_back(--u); 
      }
      long long ans = 0; 
      for(int i = 0; i < n; i++){
           ans = max(ans, DP(i)); 
      }
      printf("%lld\n",ans); 
      return 0;
}