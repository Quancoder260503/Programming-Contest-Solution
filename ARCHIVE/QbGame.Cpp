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
long long g[10][10002];
long long dp[10002][(1 << 8)];
long long dp1[10002][(1 << 8)];
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
vector<int>radj[N + 1];
long long val[N + 1];
void solve(){
     scanf("%d",&n);  
     bool positive = 0;
     long long neg = -INT_MAX; 
     for(int i = 0; i < 8; i++){
           for(int j = 1; j <= n; j++){
               cin>>g[i][j];
               if(g[i][j] > 0) positive = 1;
               else neg  = max(neg,g[i][j]); 
          }
     }
     if(!positive){
          cout<<neg<<endl;
          return;
     }
     for(int i = 1; i <= n; i++){
         for(int mask = 0; mask < (1 << 8); mask++){
               bool good = 1;
               for(int j = 0; j < 8; j++){
                    bool c = (1 << j) & mask;
                    bool d = (1 << (j + 1)) & mask;
                    if(c == 1 and d == 1){
                         good = 0; 
                         break; 
                    }
               }
               if(!good) continue; 
               for(int j = 0; j < 8; j++){
                    if((1 << j) & mask) dp1[i][mask] += g[j][i]; 
               }
         }
     }
     for(int i = 1; i <= n; i++){
         for(int mask = 0; mask < (1 << 8); mask++){
              for(int mask2 = 0; mask2 < (1 << 8); mask2++){
                   if((mask & mask2) == 0) {
                       dp[i][mask] = max(dp[i][mask], dp1[i][mask] + dp[i - 1][mask2]); 
                   }
              }
         }
     }
     ans = 0;
     for(int mask = 0; mask < (1 << 8); mask++) ans = max(ans, dp[n][mask]);
     printf("%lld \n",ans);
}
int main(){
     int t = 1;
     while(t--){
          solve(); 
     }
}