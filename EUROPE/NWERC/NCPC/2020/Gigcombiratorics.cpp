#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define MAXN (int) 1e6 + 10
const int mod = 1e9 + 7;
int arr[MAXN]; 
signed main(void)
{
     int n; 
     scanf("%d", &n);
     for(int i = 1; i <= n; i++)
     {
         scanf("%d", arr + i);
     } 
     lint cnt1, cnt12, ans; 
     cnt1 = cnt12 = ans = 0; 
     for(int i = 1; i <= n; i++)
     {
       if(arr[i] == 1)
       {
          cnt1 += 1;     
       }
       else if(arr[i] == 2)
       {
          cnt12 = (cnt12 * 2) % mod;
          cnt12 = (cnt12 + cnt1 + mod) % mod;
       }
       else
       {
           ans = (ans + cnt12 + mod) % mod; 
       }
     }
     printf("%lld\n", ans); 
     return 0; 
}