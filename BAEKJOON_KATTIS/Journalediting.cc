#include "bits/stdc++.h"
using namespace std;
const int INF = 1e9;
signed main(void)
{
    int n;
    cin >> n;
    vector <vector<pair<int, int>>> adj(n);
    for (int i = 0; i < n; i++)
    {
        int c;
        cin >> c;
        for (int j = 0; j < c; j++)
        {
            int cost, sz;
            cin >> cost >> sz;
            int preq = 0;
            for (int k = 0; k < sz; k++)
            {
                int p;
                cin >> p;
                preq |= (1 << p);
            }
            adj[i].push_back({preq, cost});
        }
    }

    vector<int> dyn(1 << n, INF);
    dyn[0] = 0;
    for (int mask = 0; mask < (1 << n); mask++)
    {
        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
            {
                for (auto [smask, cost] : adj[i])
                {
                    if ( (smask & mask) == smask)
                    {
                        dyn[mask] = min(dyn[mask], dyn[mask xor (1 << i)] + cost);
                    }
                }
            }
        }
    }
    int ans = INF;
    for (int mask = 0; mask < (1 << n); mask++)
    {
        if (mask & 1)
        {
            ans = min(ans, dyn[mask]);
        }
    }
    cout << ans << '\n'; 
    return 0;
}