#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 5e4 + 10;
const int mod = 1e9 + 7;
long long n,m,k,q,component,ans;
char a[N + 1];
int timer = 1;
vector<int>S; 
bool vis[N + 1]; 
int in[N + 1], low[N + 1]; 
int fa[N + 1]; 
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
vector<int>radj[N + 1];
vector<int>topo;
bitset<N>dp[N]; 
long long val[N + 1];
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
        component++;
        while(1){
             int v = S.back();
             S.pop_back();
             fa[v] = component;  
             vis[v] = 1; 
             if(u == v) break; 
        }   
    }
}
void dfs1(int u){
     vis[u] = 1; 
     for(int i = 0; i < tadj[u].size(); i++){
           int v = tadj[u][i];
           if(vis[v]) continue; 
           dfs1(v); 
     }
     topo.push_back(u); 
}
signed main(){
     scanf("%d%d%d",&n,&m,&q); 
     vector<pair<int,int>>edges;
     for(int i = 0; i < m; i++){
          int u,v; scanf("%d%d",&u,&v);
          adj[u].push_back(v);
     }
     for(int i = 1; i <= n; i++) if(!in[i]) dfs(i);
     for(int i = 1; i <= n; i++){
          for(int j = 0; j < adj[i].size(); j++){
               int v = adj[i][j];
               if(fa[v] == fa[i]) continue;
               tadj[fa[i]].push_back(fa[v]);
               radj[fa[v]].push_back(fa[i]);
          }
     }
     memset(vis,0,sizeof(vis));
     for(int i = 1; i <= n; i++){
           if(!vis[fa[i]]){
                 dfs1(fa[i]); 
           }
     }
     for(int i = 0; i < topo.size(); i++){
          dp[topo[i]][topo[i]] = 1; 
     }
     for(int i = 0; i < topo.size(); i++){
             int u = topo[i]; 
             for(int j = 0; j < radj[u].size(); j++){
                    int v = radj[u][j];
                    dp[v] |= dp[u]; 
             }
       }
       for(int i = 1; i <= q; i++){
             int u,v; scanf("%d%d",&u,&v);
             //cout << fa[u] << " " << fa[v] << ' ' << dp[fa[u]][fa[v]] << endl; 
             cout << (dp[fa[u]][fa[v]] ? "YES" : "NO") << '\n'; 
       }
       return 0;
}