#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)4e5 + 10;
#define lint long long
vector<int> adj[MAXN];
set<pair<int, int>> trade[MAXN];
int a[MAXN];
int b[MAXN];
int n, m;
void dfs(int u)
{
    trade[u].insert({b[u], u});
    for (auto v : adj[u])
    {
        dfs(v);
        if (trade[u].size() < trade[v].size())
        {
            swap(trade[u], trade[v]);
        }
        for (auto val : trade[v])
        {
            trade[u].insert(val);
        }
    }
    while (trade[u].size() > a[u]) trade[u].erase(*trade[u].begin());
}
signed main(void)
{
    cin >> n;
    for (int i = 2; i <= n; i++)
    {
        int x;
        cin >> x;
        adj[x].push_back(i);
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
    }
    dfs(1);
    lint ans = 0;
    vector<int> arr;
    for (auto [val, node] : trade[1])
    {
        ans += val;
        arr.push_back(node);
    }
    cout << ans << '\n';
    sort(arr.begin(), arr.end()); 
    cout << arr.size() << " "; 
    for(auto to : arr)
    {
        cout << to << " "; 
    }
    cout << '\n';
    return 0;
}