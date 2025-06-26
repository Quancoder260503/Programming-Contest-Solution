#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 4e7 + 10
#define lint long long
int n;
int A[30]; 
signed main(void)
{
     scanf("%d", &n); 
     lint area = 0;
     for(int i = 0; i <= n; i++)
     {
         lint x; scanf("%lld", &x); 
         area += 1LL * (1LL << i) * (1LL << i) * x;   
         A[i] = x; 
     } 
     int mask = (1 << n);
     for(lint height = mask; height < MAXN; height++)
     {
          if(area % height == 0)
          {
              int good = 1;
              lint width = area / height; 
              for(int npow = n; npow >= 0; npow--)
              { 
                  lint currp = 1LL << npow; 
                  lint currh = (height / currp) * currp; 
                  lint currw = (width / currp) * currp; 
                  lint rarea = 1LL * currh * currw; 
                  lint arrea = 0; 
                  for(int k = n; k >= npow; k--)
                  {
                     arrea += 1LL * A[k] * (1LL << k) * (1LL << k); 
                  }
                  if(arrea > rarea)
                  {
                     good = 0; 
                     continue; 
                  }
              }
              if(good)
              {
                   printf("%lld %lld\n", height, width);
                   return 0;
              }
          }
     }
     puts("impossible"); 
     return 0; 
}