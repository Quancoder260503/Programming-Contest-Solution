#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
const int N = 5e4 + 10;
int n,m; 
vector<int>adj[N + 1];
vector<int>radj[N + 1];
vector<int>topo;
bool vis[N + 1]; 
bitset<N>dp[N];
void dfs(int u){
     vis[u] = 1; 
     for(int i = 0; i < adj[u].size(); i++){
           int v = adj[u][i];
           if(vis[v]) continue; 
           dfs(v); 
     }
     topo.push_back(u); 
}
signed main(){
       cin >> n >> m;
       for(int i = 0; i < m; i++){
            int u,v; cin >> u >> v;
            adj[u].push_back(v);
            radj[v].push_back(u); 
       }   
       for(int i = 1; i <= n; i++){ 
             if(!vis[i]) dfs(i); 
       }
       for(int i = 1; i <= n; i++) dp[i][i] = 1; 
       for(int i = 0; i < topo.size(); i++){
             int u = topo[i]; 
             for(int j = 0; j < radj[u].size(); j++){
                    int v = radj[u][j];
                    dp[v] |= dp[u]; 
             }
       }
       for(int i = 1; i <= n; i++){
            cout << dp[i].count() << " "; 
       }
       return 0;
}