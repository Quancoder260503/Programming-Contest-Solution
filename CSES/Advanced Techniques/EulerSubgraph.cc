#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> info; 
const int N = 5e5 + 5;
const int mod = 1e9 + 7; 
int up[21][N + 1],dp[N + 1],par[N + 1];
int a[N + 1];
int n,m,q;
vector<pair<int,int>>tadj[N + 1];
vector<pair<int,int>>adj[N + 1]; 
int trs,dsz,psz;
vector<array<int,4>>edges;
int cnt; 
bool vis[N + 1],use[N + 1],brid[N + 1]; 
long long ds[21][N + 1];
int st[N + 1],low[N + 1];
int comp[N + 1];
int fa[N + 1];
map<int,int>mp[N + 1];
pair<int,int>ans[N + 1];
int find(int u){
     if(u == fa[u]) return u;
     return fa[u] = find(fa[u]);
}
void unite(int u,int v){
     u = find(u); v = find(v);
     if(u == v) return;
     fa[u] = v;
}
int main(){
      scanf("%d%d",&n,&m);
      long long ans = 1; 
      for(int i = 1; i <= n; i++) fa[i] = i; 
      for(int i = 0; i < m; i++){
           int u,v; scanf("%d%d",&u,&v); 
           if(find(u) == find(v)){
               ans = ans % mod * 2 % mod; 
           }
           else unite(u,v); 
      }
      printf("%lld\n",ans); 
      return 0; 
}