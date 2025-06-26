#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int n;
    cin >> n;
    if(n == 1)
    {
        cout << "10" << '\n';
        return 0;
    }
    vector<vector<int>> adj((1 << n) + 1);
    for (int mask = 0; mask < (1 << (n - 1)); mask++)
    {
        int u = mask;
        int v = (mask << 1) % (1 << (n - 1));
        adj[u].push_back(v);
        adj[u].push_back(v | 1);
    }
    auto solve = [&](void)
    {
        stack<int> q;
        q.push(0);
        string ans;
        while (q.size())
        {
            int u = q.top();
            if (adj[u].size())
            {
                int v = adj[u].back();
                adj[u].pop_back();
                q.push(v);
            }
            else
            {
                q.pop(); 
                ans += (char) ((u & 1) + '0'); 
            }
        }
        for(int i = 0; i < n - 2; i++)
        {
            ans += '0'; 
        }
        reverse(ans.begin(), ans.end());
        return ans;
    };
    cout << solve() << '\n';
    return 0;
}