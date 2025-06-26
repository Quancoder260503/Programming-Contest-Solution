#include "bits/stdc++.h"
using namespace std;
const int N = 2e5 + 1;
typedef pair<int,int> pii;
int dp[N + 1];
int n;
int timer = 1;
int fa[N + 1];
int in[N + 1];
int out[N + 1]; 
vector<int>adj[N + 1];
int depth;
int dfs(int u,int p,set<pii>&heavy){
      int ans = 0;
      set<pii>light; 
      int cnt = 0;
      for(int i = 0; i < adj[u].size(); i++){
             int v = adj[u][i];
             if(v == p) continue; 
             dp[v] = dp[u] + 1;
             if(cnt == 0) ans += dfs(v, u, heavy);
             if(cnt == 1) ans += dfs(v, u, light); 
             cnt++; 
      }
      if(heavy.size() < light.size()) swap(heavy,light);  
      int height = light.size() ? light.rbegin() ->  first : dp[u];
      if(heavy.size()){
         auto it = prev(heavy.end()); 
         while(heavy.size() && it -> first > height + 1){
              heavy.erase(*it--);
              ans++; 
         }
      }
      for(auto it : light) heavy.insert(it); 
      heavy.insert({dp[u],u}); 
      return ans; 
}
int main(){
      scanf("%d",&n);
      for(int i = 0; i < n - 1; i++){
           int u,v; scanf("%d%d",&u,&v);
           adj[u].push_back(v);
           adj[v].push_back(u); 
      }
      set<pii>cur; 
      int ans = dfs(1,0,cur); 
      printf("%d\n",ans);
      return 0;
}