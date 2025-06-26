#include "bits/stdc++.h"
using namespace std;
#define N 1000005
int A[N];
struct fewwick
{
    long long bit[N];
    long long sum(int i)
    {
        long long c = 0;
        for (++i; i > 0; i -= (i & -i))
            c = (c + bit[i]);
        return c;
    }
    long long query(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }
    void upd(int i, int dif)
    {
        for (++i; i < N; i += (i & -i))
            bit[i] = (dif + bit[i]);
    }
} bit;
signed main(void)
{
   int n; 
   scanf("%d",&n);
   vector<int>curr;
   for(int i = 1; i <= n; i++)
   {
        scanf("%d",&A[i]); 
        curr.push_back(A[i]); 
   }
   long long ans = 0; 
   sort(curr.begin(),curr.end()); 
   for(int i = 1; i <= n; i++)
   {
         A[i] = lower_bound(curr.begin(),curr.end(), A[i]) - curr.begin(); 
         ans += 1LL * (i - 1 - bit.sum(A[i])); 
         bit.upd(A[i],1); 
   }
   printf("%lld\n",ans); 
   return 0;
}