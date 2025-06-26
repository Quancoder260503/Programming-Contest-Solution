#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 1500000
#define C 5
typedef long double ldb;
const int mod = 1e9 + 7; 
long long finv[N];
long long fac[N];
long long inv[N]; 
int n,k,m;  
long long dp[N][(1 << C)]; 
vector<int>adj[N]; 
int col[N]; 
int dfs(int u, int p){
    int ans = 0;
    for(int i = 0; i < adj[u].size(); i++){
         int v = adj[u][i];
         if(v == p) continue;
         ans = ans xor (dfs(v,u) + 1); 
    }
    return ans;
}
signed main(void){
     scanf("%d",&n);
     for(int i = 0; i < n - 1; i++){
          int u,v; 
          scanf("%d%d",&u,&v);
          adj[u].push_back(v);
          adj[v].push_back(u);
     }
     int ans = dfs(1,0);
     printf("%s\n",ans ? "Alice" : "Bob"); 
     return 0; 
}