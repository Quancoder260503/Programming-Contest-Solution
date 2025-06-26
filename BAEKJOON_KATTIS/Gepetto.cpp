#include "bits/stdc++.h"
using namespace std;
#pragma GCC target("popcnt")
#define MAXN (int)500
#define mp make_pair
#define M 52
bitset<MAXN> dp[M];
int n, m;
vector<pair<int,int> > edge;
signed main(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        edge.push_back(mp(--u, --v));  
    }
    int ans = 0;
    for (int mask = 0; mask < (1 << n); mask++)
    {
        bool good = 1; 
        for(int i = 0; i < edge.size(); i++)
        {
             if(mask & (1 << edge[i].first) && mask & (1 << edge[i].second))
             {
                 good = 0; 
                 break; 
             }
        }
        ans += good;
    }
    printf("%d\n", ans); 
    return 0;
}
/* O(n * n * log(n)) */