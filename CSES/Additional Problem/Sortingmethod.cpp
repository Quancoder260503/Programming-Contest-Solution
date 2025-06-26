#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e6 + 10
#define lint long long
int bit[MAXN];
int n; 
int fa[MAXN]; 
int comp[MAXN]; 
int arr[MAXN]; 
int dp[MAXN]; 
int range(int i)
{
    int c = 0;
    for (++i; i > 0; i -= (i & -i))
    {
        c = c + bit[i];
    }
    return c;
}
void upd(int i, int dif)
{
    for (++i; i < MAXN; i += (i & -i))
    {
        bit[i] = dif + bit[i];
    }
}
int find(int u)
{
     return u == fa[u] ? u : fa[u] = find(fa[u]); 
}
void unite(int u, int v)
{
     u = find(u); v = find(v);
     if(u == v) return; 
     if(comp[u] > comp[v]) swap(u,v); 
     comp[v] += comp[u];
     fa[u] = v;
}
signed main(void)
{
     scanf("%d", &n); 
     for(int i = 1; i <= n; i++)
     {
         comp[i] = 1; 
         fa[i] = i; 
         scanf("%d", arr + i); 
     }
     lint methoda = 0; 
     lint methodb = 0;
     lint methodc = 0; 
     lint methodd = 0; 
     vector<int>lis; 
     for(int i = 1; i <= n; i++)
     {
        methoda += range(n) - range(arr[i]);
        upd(arr[i], 1);
        if(find(i) == find(arr[i]))
        {
            methodb = methodb - (comp[find(i)] + 1); 
        }
        else
        {
             unite(i, arr[i]); 
        }
        int pos = lower_bound(lis.begin(), lis.end(), arr[i]) - lis.begin(); 
        if(pos == lis.size()) lis.push_back(arr[i]); 
        else lis[pos] = arr[i]; 
     }
     methodc = n - (int) lis.size();
     for(int i = 1; i <= n; i++)
     {
         dp[arr[i]] = dp[arr[i] - 1] + 1; 
     }
     methodd = n - dp[n]; 
     methodb += 2 * n; 
     printf("%lld %lld %lld %lld\n", methoda, methodb, methodc, methodd); 
     return 0; 
}