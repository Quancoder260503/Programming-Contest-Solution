#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e5
#define MAX (int) 1e7 + 10
#define mp make_pair; 
bool vis[MAX + 10]; 
int gcd(int a, int b)
{
     if(a == 0) return b; 
     return gcd(b % a, a); 
}
void sieve()
{
    vis[1] = 1;
     for(int i = 2; i < MAX + 10; i++)
     {
         if(vis[i]) continue; 
         for(int j = 2 * i; j < MAX + 10; j += i)
         {
             vis[j] = 1; 
         }
     }
}
void solve()
{
     double a, b;
     scanf("%lf%lf", &a, &b);
     int na = (int) round(a * (double) MAXN);
     int nb = (int) round(b * (double) MAXN);
     int g = gcd(na,nb); 
     na = na / g;
     nb = nb / g; 
     if(na == nb)
     {
         printf("%d %d\n",2,2); 
         return; 
     }
     if(!vis[na] && !vis[nb])
     {
         printf("%d %d\n",na,nb); 
     }
     else
     {
         printf("impossible\n"); 
     }
     return; 
}
signed main(void)
{ 
    int tc; 
    scanf("%d",&tc); 
    sieve(); 
    for(int i = 1; i <= tc; i++)
    {
         solve(); 
    }
    return 0;
}