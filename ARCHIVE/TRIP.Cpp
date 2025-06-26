#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 4e5 + 10;
const int mod = 1e9 + 7;
long long n,m,k,q,component,ans;
char a[N + 1];
int timer = 1;
vector<int>S; 
bool vis[N + 1]; 
int in[N + 1], low[N + 1]; 
int fa[N + 1]; 
long long g[2001][2001];
long long dp[17][(1 << 17)];
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
vector<int>radj[N + 1];
long long val[N + 1];
int main(){
     scanf("%d",&n);
     for(int i = 0; i < n; i++){
          for(int j = 0; j < n; j++){
               scanf("%d",&g[i][j]); 
          }
     }
     for(int mask = 1; mask < (1 << n); mask++){
           for(int i = 0; i < n; i++) dp[i][mask] = INT_MAX; 
     }
     for(int i = 0; i < n; i++) dp[i][(1 << i)] = 0; 
     for(int mask = 1; mask < (1 << n); mask++){
          for(int i = 0; i < n; i++){
             for(int j = 0; j < n; j++){
                if(!(mask & (1 << j))){
                    dp[j][mask | (1 << j)] = min(dp[j][mask | (1 << j)],dp[i][mask] + g[i][j]); 
              }
           }
        } 
     }; 
     long long ans = INT_MAX; 
     for(int i = 0; i < n; i++){
         ans = min(ans, dp[i][(1 << n) - 1]);
     }
     printf("%lld \n",ans);
}