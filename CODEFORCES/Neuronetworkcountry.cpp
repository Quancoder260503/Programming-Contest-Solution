#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define MAXN (int)1e6 + 10
#define M 200
const int mod = 1e9 + 7;
int n, m, k; 
struct matrix
{
     lint row[M];  
}; 
void multiply(matrix &a, const matrix &b)
{
     matrix ans;
     for (int i = 0; i < m; i++)
     {
         ans.row[i] = 0;
     }
     for(int i = 0; i < m; i++)
     {
         for(int j = 0; j < m; j++)
         {
             ans.row[(i + j) % m] = (ans.row[(i + j) % m] + 1LL * a.row[i] % mod * b.row[j] % mod + mod) % mod;
         }
     }
     for(int i = 0; i < m; i++)
     {
         a.row[i] = ans.row[i]; 
     }
     return;
} 
void binpow(matrix &a, int pow)
{
     matrix ans; 
     for(int i = 0; i < m; i++)
     {
         ans.row[i] = 0;
     }
     ans.row[0] = 1;
     while(pow)
     {
         if(pow & 1) multiply(ans, a);
         multiply(a, a);
         pow = pow / 2;  
     }
     for(int i = 0; i < m; i++)
     {
         a.row[i] = ans.row[i]; 
     }
     return;
}
int arr[MAXN]; 
signed main(void)
{
    scanf("%d %d %d", &n, &k, &m);
    matrix a, b, c; 
    for(int i = 0; i < m; i++)
    {
        a.row[i] = b.row[i] = c.row[i] = 0;
    }
    for(int i = 1; i <= n; i++)
    { 
        int x; scanf("%d", &x); 
        a.row[x % m] += 1; 
    }
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]); 
        b.row[arr[i] % m] += 1; 
    }
    for(int i = 1; i <= n; i++)
    {
        int x; scanf("%d", &x); 
        c.row[(x + arr[i]) % m] += 1; 
    }
    multiply(a, c);
    if(k > 2)
    {
        binpow(b, k - 2);
        multiply(a, b);
    }
    printf("%lld\n", a.row[0]);
    return 0;
}