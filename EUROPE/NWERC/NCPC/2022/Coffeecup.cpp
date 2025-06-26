#include "bits/stdc++.h"
using namespace std;
#define N 1000005
signed main(void)
{
     int n; scanf("%d",&n);
     int coffee = 0; 
     int ans = 0; 
     for(int i = 1; i <= n; i++)
     {
         char x; scanf(" %c",&x); 
         if(x == '1')
         {
             coffee = 2; 
             ans += 1; 
         }
         else{
              if(coffee > 0)
              {
                 coffee--; 
                 ans += 1; 
              }
         }
     }
     printf("%d\n",ans); 
     return 0; 
}