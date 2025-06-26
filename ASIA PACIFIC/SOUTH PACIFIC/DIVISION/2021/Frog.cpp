#include "bits/stdc++.h"
using namespace std;
const int MAXN = 100;
vector<int> adj[MAXN];
int n, m;
signed main(void)
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j++)
        {
            int k;
            cin >> k;
            adj[i].push_back(k);
        }
    }
    int ans = (int)1e9;
    for (int i = 0; i < (1 << n); i++)
    {
        int get = 0;
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                for (auto it : adj[j])
                {
                    get = get | (1 << it);
                }
            }
        }
        if(__builtin_popcount(get) == m)
        {
            ans = min(ans, __builtin_popcount(i)); 
        }
    }
    cout << (ans == 1e9 ? -1 : ans) << endl;
    return 0;
}