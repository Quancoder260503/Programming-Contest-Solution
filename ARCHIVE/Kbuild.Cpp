#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 5e5 + 5;
int dp[N + 1],ds[N + 1],up[21][N + 1];
int a[N + 1];
int n,m,q,timer;
vector<pair<int,int>>tadj[N + 1];
vector<int>adj[N + 1];
int dsz,psz;
vector<pair<int,int>>edges; 
vector<pair<int,int>>bridges; 
vector<pair<int,int>>queries;
bool brid[N + 1],vis[N + 1]; 
int comps[N + 1];
int low[N + 1],trs[N + 1];
int comp[N + 1];
int fa[N + 1];
int deg[N + 1][2]; 
long long dfs(int u,int p){
    trs[u] = 1;
    for(int i = 1; i < 21 ; i++){
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for(int i = 0;  i < adj[u].size(); i++){
        int v = adj[u][i]; 
        if(v == p) continue;
        ds[v] = ds[up[0][v] = u] + 1;
        trs[u] += dfs(v,u);
    } 
    return trs[u];
}
int jump(int x,int d){
    for(int i = 0; i < 21 ; i++){
        if( (d >> i) & 1) x = up[i][x];
    }
    return x; 
}
int lca(int a, int b){
    if(ds[a] < ds[b]) swap(a,b);
    a = jump(a, ds[a] - ds[b]);
    if(a == b) return a;
    for(int i = 20; i >= 0; i--){
         int tA = up[i][a]; int tB = up[i][b];
         if(tA != tB) {
            a = tA; b = tB;
         }
    } 
    return up[0][a];
}  
void calc(int u,int p){
    for(int i = 0; i < adj[u].size(); i++){
          int v = adj[u][i];
          if(v == p) continue; 
          calc(v,u);
          a[u] += a[v]; 
    }
}
int main(){
     scanf("%d%",&n);
     for(int i = 0; i < n - 1; i++){
         int u,v; scanf("%d%d",&u,&v);
         adj[u].push_back(v);
         adj[v].push_back(u); 
     }
     dfs(1,0);
     scanf("%d",&q);
     for(int i = 0; i < q; i++){
           int u,v; scanf("%d%d",&u,&v);
           int anc = lca(u,v);
           a[anc] = a[anc] - 2; 
           a[u]++; a[v]++; 
     }
     calc(1,0); 
     int cnt = 0; 
     for(int i = 1; i <= n; i++) if(!a[i]) cnt++;
     cout<< cnt - 1 <<endl; 
     return 0; 
}