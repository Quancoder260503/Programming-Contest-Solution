#include "bits/stdc++.h"
using namespace std;
#define MAXN 1000005 
int base1 = 31; 
int base2 = 37; 
long long p1[MAXN];
long long p2[MAXN]; 
const int mod = (int) 1e9 + 7; 
char s[MAXN]; 
long long ph1, ph2, sh1, sh2;
signed main(void)
{
    scanf("%s",&s); 
    int n = strlen(s); 
    p1[0] = p2[0] = 1; 
    for(int i = 1; i <= n; i++)
    {
         p1[i] = p1[i - 1] % mod * base1 % mod;
         p2[i] = p2[i - 1] % mod * base2 % mod;  
    }
    ph1 = ph2 = sh1 = sh2 = 0; 
    for(int i = 0; i < n - 1; i++)
    {
         int l = s[i] - 'a' + 1; 
         int r = s[n - 1 - i] - 'a' + 1; 
         ph1 = (ph1 + p1[i] % mod * l % mod + mod) % mod;
         ph2 = (ph2 + p2[i] % mod * l % mod + mod) % mod; 
         sh1 = (sh1 % mod * base1 % mod + r + mod) % mod; 
         sh2 = (sh2 % mod * base2 % mod + r + mod) % mod;  
         if(sh1 == ph1 && sh2 == ph2)
         {
             printf("%d ",i + 1); 
         }
    }
    printf("\n"); 
    return 0; 
}