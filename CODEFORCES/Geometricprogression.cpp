#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10 
map<long long,int>mp, mp2; 
int n, k; 
int arr[MAXN]; 
signed main(void)
{
     scanf("%d %d", &n, &k);
     for(int i = 1; i <= n; i++)
     {
         scanf("%d", &arr[i]); 
         mp[arr[i]] += 1; 
     }
     long long ans = 0; 
     for(int i = 1; i <= n; i++)
     {
         mp[arr[i]]--;
         if(arr[i] % k == 0)
         {
             ans += 1LL * mp[1LL * arr[i] * k] * mp2[ arr[i] / k]; 
         }
         mp2[arr[i]] += 1; 
     }
     printf("%lld\n", ans); 
     return 0;
}