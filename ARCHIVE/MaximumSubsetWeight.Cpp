#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e2 + 5;
int a[N + 1];
int n,m,q,timer,k;
int dp[N + 1][N + 1];
vector<int>adj[N + 1];
void dfs(int u,int p){
      dp[u][0] = a[u];
      for(int i = 0; i < adj[u].size(); i++){
           int v = adj[u][i];
           if(v == p) continue; 
           dfs(v,u); 
      }
      for(int dis = 0; dis <= N; dis++){
            if(dis == 0){
                 for(int i = 0; i < adj[u].size(); i++){
                     int v = adj[u][i];
                     if(v == p) continue;
                     dp[u][dis] += dp[v][k - dis];
                 }
                 continue; 
            }
            for(int i = 0; i < adj[u].size(); i++){
                 int v = adj[u][i]; 
                 if(v == p) continue; 
                 int val = dp[v][dis - 1];        
                 for(int j = 0; j < adj[u].size(); j++){
                      int x = adj[u][j];
                      if(x == p or x == v) continue; 
                      val += dp[x][max(dis - 1,k - dis)]; 
                 }
                 dp[u][dis] = max(dp[u][dis], val);  
            }
      }
      for(int i = N - 1; i >= 0; i--) dp[u][i] = max(dp[u][i] , dp[u][i + 1]); 
}
int main(){
     scanf("%d%d",&n,&k);
     for(int i = 1; i <= n; i++) scanf("%d",&a[i]); 
     for(int i = 0; i < n - 1; i++){
         int u,v; scanf("%d%d",&u,&v);
         adj[u].push_back(v);
         adj[v].push_back(u); 
     }
     dfs(1,0);
     printf("%d \n",dp[1][0]);
}