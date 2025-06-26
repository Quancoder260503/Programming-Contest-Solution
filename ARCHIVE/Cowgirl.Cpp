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
long long dp[31][(1 << 15)];
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
vector<int>radj[N + 1];
long long val[N + 1];
bool check(int mask,int mask1){
     for(int i = 1; i < n; i++){
          bool x = ((1 << i) & mask) == 0; 
          bool y = ((1 << i) & mask1) == 0;
          bool z = ((1 <<(i - 1)) & mask) == 0;
          bool d = ((1 <<(i - 1)) & mask1) == 0; 
          if(x == y and y == z and z == d) return 0; 
     }
     return 1;
}
void solve(){
     scanf("%d%d",&n,&m); 
     if(n > m) swap(m,n); 
     for(int i = 0; i < (1 << n); i++){
          for(int j = 0; j <= m; j++){
               dp[j][i] = 0;  
          }
     }
     for(int i = 0; i < (1 << n); i++) dp[1][i] = 1;
     for(int i = 2; i <= m; i++){
         for(int mask = 0; mask < (1 << n); mask++){
              for(int mask2 = 0; mask2 < (1 << n); mask2++){
                   if(check(mask,mask2)) dp[i][mask] += dp[i - 1][mask2]; 
              }
         }
     }
     ans = 0;
     for(int mask = 0; mask < (1 << n); mask++) ans += dp[m][mask];
     printf("%lld \n",ans);
}
int main(){
     int t; scanf("%d",&t);
     while(t--){
          solve(); 
     }
}