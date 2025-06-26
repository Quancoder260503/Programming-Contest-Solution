#include "bits/stdc++.h"
using namespace std;
#define mp make_pair 
signed main(void)
{
     int r;
     scanf("%d",&r);
     long long ans = LLONG_MAX;
     pair<int,int> res;
     for(int y = 0; y <= r; y++)
     {
         int x = (int) sqrt(1LL * r * r - 1LL * y * y ) + 1; 
         if(1LL * x * x + 1LL * y * y < ans) 
         {
             ans = min(ans, 1LL * x * x + 1LL * y * y); 
             res = mp(x,y); 
         }
     } 
     printf("%d %d\n",res.first, res.second); 
     return 0; 
}