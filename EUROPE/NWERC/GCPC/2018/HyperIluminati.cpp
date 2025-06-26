#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e6 + 10
#define MAXP 54
long long fastpow(int val, int pow)
{
    if(pow == 0) return 1;
    long long ans = 1; 
    long long base = val;
    while(pow)
    {
        if(pow & 1) ans = ans * base;
        base = base * base; 
        pow = pow / 2; 
    }
    return ans;
}
signed main(void)
{
     long long n; 
     scanf("%lld",&n);
     for(int pow = 2; pow <= MAXP; pow++)
     {
         int curr = 1; 
         long long sum = 0; 
         while(sum < n)
         {
            sum += fastpow(curr++, pow); 
         }
         if(sum == n)
         {
             printf("%d %d\n",pow + 1, curr - 1); 
             return 0; 
         }
     } 
     puts("impossible");
     return 0;
}