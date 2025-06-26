#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 101; 
int n,cnt;
long long a[N + 1];
int msk[N + 1]; 
long long dp[N + 1][(1 << 17) + 1]; 
int fa[N + 1][(1 << 17) + 1]; 
int res[N + 1];
int ord[N + 1]; 
bool vis[N + 1]; 
int main(){
     scanf("%d",&n);
     for(int i = 1; i <= n; i++) scanf("%d",&a[i]);
     for(int i = 2; i <= 60; i++){
     	   if(vis[i]) continue;
     	   ord[i] = cnt++; 
     	   for(int j = i; j <= 60; j += i){
     	   	    vis[j] = 1;
     	   	    msk[j] += (1 << ord[i]);
     	   }
     }
     memset(dp,0x3f3f3f3f,sizeof(dp)); 
     dp[0][0] = 0; 
     for(int i = 1; i <= n; i++){
     	   for(int mask = 0; mask < (1 << 16); mask++){
     	   	   for(int j = 0; j <= 60; j++){
     	  	   	    if(mask & msk[j]) continue;
     	  	   	    if(dp[i][mask | msk[j]] > dp[i - 1][mask] + abs(a[i] - j)){
     	  	   	    	 dp[i][mask | msk[j]] = dp[i - 1][mask] + abs(a[i] - j); 
     	  	   	    	 fa[i][mask | msk[j]] = j; 
     	  	   	    }
     	  	   }
     	  }
     }
     long long ans = 0x3f3f3f3f; 
     long long smask = 0; 
     for(int mask = 0; mask < (1 << 16); mask++){
     	  if(ans > dp[n][mask]){
     	  	   ans = dp[n][mask];
     	  	   smask = mask; 
     	  }
     }
     //cout<<1<<endl;
     for(int i = n; i > 0; i--){
     	   res[i] = fa[i][smask];
     	   smask -= msk[res[i]]; 
     }
     for(int i = 1; i <= n; i++) printf("%d ",res[i]);
     //printf("%ld",dp[n][(1 << 16) - 1]); 
}
