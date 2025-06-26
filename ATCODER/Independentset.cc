#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 4e5 + 10;
const int mod = 1e9 + 7;
const int inv = 5e8 + 4;
const int MAXC  = 20; 
long long n,m,k,q,component,ans;
char a[N + 1];
int timer = 1;
vector<int>S; 
bool vis[N + 1]; 
int in[N + 1], low[N + 1]; 
int fa[N + 1], res[N + 1]; 
int col[N + 1]; 
vector<int>adj[N + 1];
long long dp[N + 1],dp1[N + 1]; 
void dfs(int u,int p){
    for(int i = 0; i < adj[u].size(); i++){
         auto v = adj[u][i];
         if(v == p) continue; 
         dfs(v,u); 
         dp1[u] = dp1[u] % mod * (dp[v] + dp1[v]) % mod; 
    }
    for(int i = 0; i < adj[u].size(); i++){
         int v = adj[u][i];
         if(v == p) continue; 
         dp[u] = dp[u] % mod * dp1[v] % mod; 
    }
}
int main(){
     scanf("%d",&n);
     for(int i = 0; i < n - 1; i++){
          int u,v;  scanf("%d%d",&u,&v);
          adj[u].push_back(v);
          adj[v].push_back(u); 
     }
     for(int i = 1; i <= n; i++) dp[i] = dp1[i] = 1;
     dfs(1,0);
     ans = (dp[1] + dp1[1]) % mod; 
     cout<<ans<<endl; 
}