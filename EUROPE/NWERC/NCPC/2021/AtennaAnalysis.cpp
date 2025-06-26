#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10 
#define lint long long 
lint arr[MAXN]; 
int n, c;
/*
   |x[i] - x[j]| - c|i - j|
   Case 1 : x[i] - x[j] - c(i - j) =  x[i] - ci + (-x[j] + cj)
   Case 2 : x[j] - x[i] - c(i - j) =  -(x[i] + ci) + (x[j] + cj) 
*/
 
signed main(void)
{
    scanf("%d %d", &n, &c);
    lint opt[2];
    fill(opt, opt + 2, LLONG_MIN);
    for(int i = 1; i <= n; i++)
    {
         scanf("%lld\n", &arr[i]); 
    }
    for(int i = 1; i <= n; i++)
    {
         lint add = arr[i] + 1LL * c * i; 
         lint mi = arr[i] - 1LL * c * i;
         lint ans = 0;
         if(i > 1)
         {
             ans = max(ans, mi + opt[0]);
             ans = max(ans, -add + opt[1]); 
         } 
         printf("%lld ", ans); 
         opt[0] = max(opt[0], -mi); 
         opt[1] = max(opt[1], add); 
    }
    return 0;
}