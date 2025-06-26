#include "bits/stdc++.h"
using namespace std; 
#define N 1000005
int base1 = 31; 
int base2 = 37; 
long long p1[N], p2[N];
long long ph1[N], ph2[N];  
const int mod = (int) 1e9 + 7; 
char s[N]; 
signed main(void)
{
    scanf("%s",&s); 
    int n = strlen(s); 
    p1[0] = p2[0] = 1; 
    ph1[0] = ph2[0] = s[0] - 'a' + 1; 
    for(int i = 1; i <= n; i++)
    {
         p1[i] = p1[i - 1] % mod * base1 % mod;
         p2[i] = p2[i - 1] % mod * base2 % mod; 
         ph1[i] = (ph1[i - 1] % mod * base1 % mod + mod + s[i] - 'a' + 1) % mod; 
         ph2[i] = (ph2[i - 1] % mod * base2 % mod + mod + s[i] - 'a' + 1) % mod; 
    }
    for(int l = 1; l <= n; l++)
    {
        long long h1 = ph1[l - 1];
        long long h2 = ph2[l - 1]; 
        for(int i = 0; i < (n / l) - 1; i++)
        {
            h1 = (h1 % mod * p1[l] % mod + ph1[l - 1] + mod) % mod;
            h2 = (h2 % mod * p2[l] % mod + ph2[l - 1] + mod) % mod;
        }
        h1 = (h1 % mod * p1[n % l] % mod + ph1[n % l - 1] + mod) % mod; 
        h2 = (h2 % mod * p2[n % l] % mod + ph2[n % l - 1] + mod) % mod;  
        if(h1 == ph1[n - 1] && h2 == ph2[n - 1])
        { 
           printf("%d ",l); 
        }
    }
    return 0;
}
/* abcabca */ 