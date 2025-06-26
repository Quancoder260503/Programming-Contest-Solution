#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 100;
const int INF = 1e7 + 10; 
long long n,m,q,dsz,M,res;
int timer = 1;
vector<int>adj[N + 1];
int fa[N + 1], comp[N + 1];
bool vis[N + 1];
int up[22][N + 1],dp[N + 1],val[N + 1];
void dfs(int u,int p){
     vector<int>cur; 
     for(int i = 0; i < adj[u].size(); i++){
         int v = adj[u][i];
         if(v == p) continue;
         dfs(v,u);
         cur.push_back(dp[v]);
     }
     dp[u] = 1;
     int count = 0; 
     sort(cur.rbegin(),cur.rend());
     for(int i = 0; i < cur.size(); i++){
          dp[u] = max(dp[u], cur[i] + count);
          //if(u == 2) cout<<cur[i]<<' '<<count<<endl; 
          count++; 
     }
}
int main(){
      scanf("%d",&n);
      int u; 
      while(cin >> u) {
           int k; scanf("%d",&k);
           for(int i = 0; i < k; i++){
                int v; scanf("%d",&v);
                adj[u].push_back(v); 
           }
      }
      dfs(1,0);
      cout<<dp[1]<<endl; 
}