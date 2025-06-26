#include "bits/stdc++.h"
using namespace std; 
#define lint long long 
#define inf (lint) 1e17
#define MAXN (int) 1e5 + 5
#define mp make_pair
int prefix[MAXN];
int n, k;
lint dp[MAXN][2];
lint cost(int i, int j)
{
     return 1LL * (prefix[j] - prefix[i - 1]) * (prefix[j] - prefix[i - 1]); 
}   
void dnc(int l, int r, int lb, int rb)
{
     if(l > r) return;
     pair<lint,int>opt = mp(inf, 0);
     int mid = (l + r) / 2;
     for(int i = lb; i <= min(mid, rb); i++)
     {
         opt = min(opt, mp(dp[i - 1][0] + cost(i, mid), i)); 
     } 
     dp[mid][1] = opt.first;
     int pos = opt.second; 
     dnc(l, mid - 1, lb, pos);
     dnc(mid + 1, r, pos ,rb); 
}
signed main(void)
{
     scanf("%d %d", &n, &k);
     for(int i = 1; i <= n; i++)
     {
         int x; scanf("%d", &x); 
         prefix[i] = prefix[i - 1] + x; 
     }
     for(int i = 1; i <= n; i++)
     {
         dp[i][0] = cost(1, i);  
     }
     for(int i = 2; i <= k; i++)
     {
         dnc(1, n, 1, n); 
         for(int j = 1; j <= n; j++)
         {
             dp[j][0] = dp[j][1]; 
         }
     }
     printf("%lld\n", dp[n][0]); 
     return 0; 
}