#include "bits/stdc++.h"
using namespace std; 
#define N 1000005
int n; 
long long A[N]; 
long long sf[N];
long long pf[N]; 
signed main(void)
{
    scanf("%d",&n); 
    memset(A,63,sizeof(A)); 
    for(int i = 1; i <= n; i++)
    {
       scanf("%lld",&A[i]); 
    } 
    memset(pf,63,sizeof(pf));
    memset(sf,63,sizeof(sf));
    for(int i = 1; i <= n; i++)
    {
         if(A[i] >= A[i - 1]) pf[i] = pf[i - 1];
         else pf[i] = A[i]; 
    }
    for(int i = n; i > 0; i--)
    {
         if(A[i] >= A[i + 1]) sf[i] = sf[i + 1];
         else sf[i] = A[i];
    }
    long long ans = 0;
    for(int i = 1 ; i <= n; i++)
    {
         ans = max(ans, min(A[i] - pf[i], A[i] - sf[i])); 
    }
    printf("%lld\n",ans); 
    return 0; 
}