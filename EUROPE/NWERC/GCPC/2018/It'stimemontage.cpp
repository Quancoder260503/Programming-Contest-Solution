#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)1e6 + 10
int a[MAXN];
int b[MAXN]; 
int dp[MAXN];
int n;
bool good(int d)
{
     for(int i = 1; i <= n; i++)
     {
         if(a[i] + d == b[i]) continue;
         if(a[i] + d < b[i])
         {
             return 0; 
         }
         else
         {
             return 1; 
         }
     }
     return 1; 
}
signed main(void)
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
         scanf("%d ", a + i); 
    }
    for(int i = 1; i <= n; i++)
    {
         scanf("%d ", b + i); 
    }
    int lo = 0;
    int hi = MAXN; 
    while(lo < hi)
    {
         int mid = (lo + hi) / 2; 
         if(good(mid))
         {
              hi = mid;
         }
         else
         {
             lo = mid + 1; 
         }
    }
    printf("%d", lo); 
    return 0;
}