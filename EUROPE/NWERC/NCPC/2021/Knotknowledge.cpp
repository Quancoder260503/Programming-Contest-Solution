#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10
int a[MAXN];
int b[MAXN]; 
int vis[MAXN]; 
signed main(void)
{
     int n;
     scanf("%d", &n);
     int tota, totb;
     tota = totb = 0;
     for(int i = 1; i <= n; i++)
     {
         scanf("%d", &a[i]);
         tota += a[i]; 
     }
     for (int i = 1; i < n; i++)
     {
         scanf("%d", &b[i]);
         totb += b[i]; 
     }
     int tot = 0; 
     printf("%d\n", abs(tota - totb)); 
     return 0; 
}