#include "bits/stdc++.h"
using namespace std;
const int INF = 1e7;
int doit(int c, int len, vector<vector<int>>&cost, vector<vector<int>>&dyn)
{
    if (len == 2) return cost[c][c]; 
    if (len == 1) return 0;
    if (dyn[c][len] != -1) return dyn[c][len];
    auto &res = dyn[c][len];
    res = INF;
    for (int i = 0; i < 26; i++)
    {
        res = min(res, cost[c][i] + cost[i][c] + doit(i, len - 2, cost, dyn));
    }
    return res;
}
signed main(void)
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> cost(26, vector<int>(26, INF));
    for (int i = 0; i < n; i++)
    {
        string z;
        int c;
        cin >> z >> c;
        cost[z[0] - 'a'][z[1] - 'a'] = c;
    }
    vector<vector<int>> dyn(26, vector<int>(k + 1, -1));
    int ans = INF;
    for (int i = 0; i < 26; i++)
    {
         ans = min(ans, doit(i, k, cost, dyn)); 
    }
    cout << (ans >= INF ? -1 : ans) << '\n'; 
    return 0;
}