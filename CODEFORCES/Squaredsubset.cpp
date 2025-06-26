#include "bits/stdc++.h"
using namespace std;
#define MASK 19
#define M  (int) 1e5 + 1
#define MAXN (int) (1 << MASK)
#define lint long long
#define MAX 71
const int mod = 1e9 + 7;
int n; 
int fmask[MAX]; 
int arr[MAX]; 
lint pow2[M];
lint dp[2][MAXN];
const int primes[19] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
signed main(void)
{ 
    scanf("%d", &n); 
    pow2[0] = 1; 
    for(int i = 1; i <= n; i++)
    {
        pow2[i] = pow2[i - 1] % mod * 2 % mod; 
    }
    for(int k = 0; k < 19; k++)
    {
        int i = primes[k]; 
        for(int j = i; j < MAX; j++)
        {
             int num = j; 
             while(num % i == 0) 
             {
                 fmask[j] = fmask[j] xor (1 << k); 
                 num = num / i; 
             }
        }
    }
    for(int i = 1; i <= n; i++)
    {
       int x; scanf("%d", &x);
       arr[x] += 1;     
    }
    dp[0][0] = 1; 
    for(int i = 1; i < MAX; i++)
    {
        if(arr[i])
        {
            for(int mask = 0; mask < (1 << MASK); mask++)
            {
                dp[1][mask] = (dp[1][mask] + mod + 1LL * dp[0][mask] % mod * pow2[arr[i] - 1] % mod) % mod;
                dp[1][mask xor fmask[i]] = (dp[1][mask xor fmask[i]] + mod + 1LL * dp[0][mask] % mod * pow2[arr[i] - 1] % mod) % mod;
            }
            for (int mask = 0; mask < (1 << MASK); mask++)
            {
                dp[0][mask] = dp[1][mask]; 
                dp[1][mask] = 0;
            }
        }  
    }
    printf("%lld\n", (dp[0][0] - 1 + mod) % mod); 
    return 0;    
}