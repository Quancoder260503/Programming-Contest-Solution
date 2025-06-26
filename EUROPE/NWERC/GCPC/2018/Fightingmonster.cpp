#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e6 + 10
#define mp make_pair
int dp[MAXN]; 
int vis[MAXN]; 
signed main(void)
{ 
    int n; scanf("%d",&n);
    vector<int> curr;
    for(int i = 1; i <= n; i++)
    {
         int x; scanf("%d",&x); 
         if(x == 1) curr.push_back(i); 
         vis[x] = i;
    }
    if((int) curr.size( )>= 2)
    {
         printf("%d %d\n",curr[0],curr[1]);
         return 0;
    }
    dp[0] = 1; dp[1] = 1;  
    for(int i = 2; i < MAXN; i++)
    {
         dp[i] = dp[i - 1] + dp[i - 2];
         if(vis[dp[i]] && vis[dp[i - 1]])
         {
             printf("%d %d\n",vis[dp[i - 1]],vis[dp[i]]);
             return 0;
         }
         if(dp[i] > MAXN) break; 
    }
    puts("impossible"); 
    return 0;
}