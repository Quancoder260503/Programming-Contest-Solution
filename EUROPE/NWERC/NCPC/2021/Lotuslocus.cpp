#include "bits/stdc++.h"
using namespace std;
#define MAXN 3000
int lcm(int a, int b)
{
     if(a > b) swap(a, b); 
     if(b % a == 0) return b; 
     for(int i = 2; i <= MAXN; i++)
     {
        if(i * a % b == 0)
        {
            return i * a;
        }
     }
     return a * b;
}
signed main(void)
{
   int n;
   int ans = INT_MAX; 
   scanf("%d", &n);
   for(int i = 1; i <= n; i++)
   {
     int y, c1, c2;
     scanf("%d %d %d", &y, &c1, &c2);
     ans = min(ans, y + lcm(c1, c2));
   }
   printf("%d\n", ans);
   return 0;
}