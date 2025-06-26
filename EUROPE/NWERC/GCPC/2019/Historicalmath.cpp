#include "bits/stdc++.h"
using namespace std;
#define MAXN 1000005
using cd = complex<double>;
const double PI = acos(-1);
const int mod = 1e9 + 7; 
int n, k, m;
vector<long long>mul(const vector<long long>&a, const vector<long long>&b, long long bse)
{
     vector<long long>c(a.size() + b.size(), 0); 
     for(int i = 0; i < a.size(); i++)
     {
         for(int j = 0; j < b.size(); j++)
         {
             c[i + j] += 1LL * a[i] * b[j]; 
             c[i + j + 1] += c[i + j] / bse;
             c[i + j] = c[i + j] % bse; 
         }
     }
     return c;
}
bool cmp(const vector<long long>&a, const vector<long long>&b)
{
     for(int i = a.size() - 1; i >= 0 ; i--)
     {
         if(a[i] != b[i]) 
         {
             return a[i] < b[i]; 
         }
     }
     return false; 
}
signed main(void)
{
    int sza,szb,szc; 
    scanf("%d",&sza);
    vector<long long>a,b,c;
    long long start = 0;
    for(int i = 0; i < sza; i++)
    {
         long long x; scanf("%lld",&x); 
         a.push_back(x); 
         start = max(x, start); 
    }
    scanf("%d",&szb); 
    for(int i = 0; i < szb; i++)
    {
         long long  x; scanf("%lld",&x); 
         b.push_back(x); 
         start = max(x, start); 
    }
    scanf("%d", &szc);
    for (int i = 0; i < szc; i++)
    {
         long long x; scanf("%lld", &x);
         c.push_back(x);
         start = max(x, start); 
    }
    long long lo = start + 1; 
    long long hi = (1LL << 61); 
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end()); 
    reverse(c.begin(), c.end()); 
    while(c.size() < a.size() + b.size()) c.push_back(0); 
    while(lo <= hi)
    {
         long long mid = 1LL * (hi + lo) / 2;
         vector<long long>curr = mul(a,b,mid);
         if(curr == c)
         {
             printf("%lld\n",mid);
             return 0; 
         }
         if(cmp(curr, c))
         {
             hi = mid - 1;
         }
         else
         {
             lo = mid + 1;
         }
    }
    puts("impossible"); 
    return 0; 
}
