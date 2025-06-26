#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 5;
const int M = 1e6 + 5;
const int mod = (1 << 32); 
long long n,m,k,q,bridges,comp;
long long a[N + 1];
vector<int>adj[N + 1]; 
deque<int>S;
int up[21][N + 1];
int in[N + 1];
int ans[N + 1];
int out[N + 1];
int low[N + 1]; 
bool vis[N + 1];
int dp[N + 1];
int timer = 1; 
vector<pair<int,int>>edges;
void dfs(int u){
     in[u] = low[u] = timer++;
     vis[u] = 1;
     S.push_back(u);
     for(int i = 0; i < adj[u].size();i++){
            int v = adj[u][i];
            if(!in[v]) dfs(v);
            if (vis[v]) low[u] = min(low[u],low[v]);
     }
     if(in[u] == low[u]){
        comp++;
        while(1){
             int v = S.back();
             S.pop_back();
             vis[v] = 0; 
             ans[v] = comp;
             if(u == v) break; 
        }   
    }
}
int main(){
     scanf("%d%d",&n,&m);
     for(int i = 0; i < m; i++){
          int u,v; scanf("%d%d",&u,&v);
          adj[u].push_back(v);
        /////  adj[v].push_back(u); 
     }
     for(int i = 1; i <= n; i++) if(!in[i]) dfs(i);
     cout<<comp<<endl;
     for(int i = 1; i <= n; i++) cout<<ans[i]<<' ';
}