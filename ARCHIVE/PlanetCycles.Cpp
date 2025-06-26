#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
long long n,m,comp,res;
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
deque<int>S;
int in[N + 1];
long long val[N + 1];
int low[N + 1]; 
bool vis[N + 1];
long long dp[N + 1];
int fa[N + 1]; 
int timer = 1; 
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
        comp++;  long long sum = 0; 
        while(1){
             int v = S.back();
             S.pop_back();
             fa[v] = comp;  
             vis[v] = 1; 
             sum++; 
             if(u == v) break; 
        }   
        val[comp] += sum; 
    }
}
long long calc(int u){
    if(dp[u]) return dp[u];
    dp[u] = val[u];
    for(int i = 0; i < tadj[u].size(); i++){
          int v = tadj[u][i];
          dp[u] += calc(v);
    }
    return dp[u]; 
}
int main(){
     scanf("%d",&n);
     for(int i = 1; i <= n; i++){
          int v; scanf("%d",&v);
          adj[i].push_back(v);
     }
     for(int i = 1; i <= n; i++) if(!in[i]) dfs(i);
     memset(vis,0,sizeof(vis));
     for(int i = 1; i <= n; i++){ 
          for(int j = 0; j < adj[i].size(); j++){
               int v = adj[i][j]; 
               if(fa[i] == fa[v]) continue; 
               tadj[fa[i]].push_back(fa[v]); 
          }
     }
     for(int i = 1; i <= n; i++) if(!dp[i]) calc(i);
     for(int i = 1; i <= n; i++) cout<<dp[fa[i]]<<' '; 
}