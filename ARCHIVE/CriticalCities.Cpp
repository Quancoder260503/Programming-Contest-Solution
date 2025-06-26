#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 5e5 + 5;
int dp[N + 1],val[N + 1],up[21][N + 1];
int a[N + 1],in[N + 1];
int n,m,q,timer;
vector<pair<int,int>>tadj[N + 1];
vector<int>adj[N + 1];
long long ans[N + 1]; 
int dsz,psz,cnt,comsize;
vector<int>S; 
vector<pair<int,int>>edges; 
vector<pair<int,int>>bridges; 
vector<pair<int,int>>queries;
bool brid[N + 1],vis[N + 1]; 
int comps[N + 1];
int low[N + 1],trs[N + 1];
int comp[N + 1];
int fa[N + 1];
long long dfs(int u,int p){
    a[u] = low[u] = ++dsz;
    int add = 1; int add1 = 0; 
    for(int i = 0; i < tadj[u].size(); i++){
        auto x = tadj[u][i];
        int v = x.first;
        if(!a[v]){
            int sub = dfs(v,u);
            add += sub;
            if(low[v] >= a[u]){
                 ans[u] += (long long) (comsize- 1 - sub) * sub; 
                 add1 += sub; 
            }
            else  low[u] = min(low[u] , low[v]); 
        }
        else if( v != p) low[u] = min(a[v] , low[u]);
    }
    ans[u] += (long long) (comsize - 1 - add1) * add1; 
    return add; 
}
void dfs1(int u){
   vis[u] = 1;
   comsize++;
   for(int i = 0; i < tadj[u].size(); i++){
        int v = tadj[u][i].first;
        if(vis[v]) continue; 
        dfs1(v);
   }
}
int main(){
     scanf("%d%d",&n,&m);
     for(int i = 0; i < m; i++){
         int u,v; scanf("%d%d",&u,&v);
         tadj[u].push_back({v,i});
         tadj[v].push_back({u,i}); 
     }
     for(int i = 1; i <= n; i++){
          if(!vis[i]){
             comsize = 0; 
             dfs1(i);
             dfs(i,0); 
          }
     }
     long long res = 0; 
     for(int i = 1; i <= n; i++) res += ans[i];
     long double x = (long double) ((long double) (res) / ((long double) (2 * n)));
     cout<<setprecision(6)<< x <<endl; 
}