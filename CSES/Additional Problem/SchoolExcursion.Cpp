#include <bits/stdc++.h>
#pragma GCC target("popcnt")
#include <iostream> 
#include<vector>
#define blksz 500;
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
const int N = 1e5 + 10;
const int inf = 1e7 + 5;
const int mod = 1e9 + 7;
int n,m,k,q,p,d; 
vector<int>dv[N + 1]; 
multiset<pair<int,int>,greater<pair<int,int>>>dp[N + 1];
long long A[N + 1]; 
long long f[N + 1]; 
long long ans = inf;
vector<int>adj[N + 1];
bool vis[N + 1]; 
int fa[N + 1];
int sz[N + 1]; 
int find(int u){
     return u == fa[u] ? u : fa[u] = find(fa[u]); 
}
void merge(int u,int v){
     u = find(u); v = find(v);
     if(u == v) return; 
     if(sz[u] < sz[v]) swap(u,v);
     sz[u] += sz[v]; 
     fa[v] = u; 
}
int main(){
       int n; 
       cin >> n >> m; 
       for(int i = 1; i <= n; i++){
            fa[i] = i; sz[i] = 1; 
       }
       for(int i = 0; i < m; i++){
            int u,v; cin >> u >> v;
            merge(u,v); 
       }
       vector<int>comp; 
       for(int i = 1; i <= n; i++){
            if(fa[i] == i){
                 comp.push_back(sz[i]); 
            }
       }
       bitset<N>dp; 
       dp[0] = 1; 
       for(int i = 0; i < comp.size(); i++){
              dp |= dp << comp[i];   
       }  
       for(int i = 1; i <= n; i++) cout << dp[i]; 
       return 0;
}