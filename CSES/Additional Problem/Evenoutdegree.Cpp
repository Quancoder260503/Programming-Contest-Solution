#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 5;
const int M = 1e6 + 5;
const int mod = (1 << 32); 
long long n,m,k,q,bridges;
long long a[N + 1];
vector<pair<int,int>>adj[N + 1]; 
int up[21][N + 1];
int in[N + 1];
int out[N + 1];
int low[N + 1]; 
bool use[N + 1],vis[N + 1];
int occ[N + 1];
int dp[N + 1];
int timer = 1; 
vector<pair<int,int>>edges;
void dfs(int u,int p){
     in[u] = timer++; 
     for(int i = 0; i < adj[u].size(); i++){
           auto v = adj[u][i];
           if(v.first == p) continue; 
           if(!in[v.first]){
               dfs(v.first,u);
               if(occ[v.first] % 2 != 0){
                   edges.push_back({v.first,u});
                   occ[v.first]++; 
              }
              else{
                  edges.push_back({u,v.first}); 
                  occ[u]++; 
              }
           }
           else if(in[v.first] < in[u]) {
                occ[u]++; 
                edges.push_back({u,v.first}); 
           }
     }
}
int main(){
     scanf("%d%d",&n,&m);
     for(int i = 0; i < m; i++){
          int u,v; scanf("%d%d",&u,&v);
          adj[u].push_back({v,i});
          adj[v].push_back({u,i});
     }
     int components = 0; 
     for(int i = 1; i <= n; i++){
         if(!in[i]){
             dfs(i,0);
         }
     }
     for(int i = 1; i <= n; i++){
          if(occ[i] % 2 != 0){
               cout<<"IMPOSSIBLE"<<endl;
               return 0; 
          }
     }
     for(int i = 0; i < edges.size(); i++){
           cout<<edges[i].first<<' '<<edges[i].second<<endl;
     }
}