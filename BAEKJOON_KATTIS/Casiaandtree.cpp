#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)2e6 + 10
#define mp make_pair
#define pii pair<int, int>
int arr[MAXN];
vector<int> adj[MAXN];
vector<pii> primes[MAXN];
int dep[MAXN];
int n, q;
pii dp[MAXN];
void dfs(int u, int p)
{
    int curr = arr[u];
    dp[u] = mp(-1, -1);
    for (int i = 2; i * i <= curr; i++)
    {
        if (curr % i == 0)
        {
            dp[u] = max(dp[u], primes[i].size() ? primes[i].back(): mp(-1, -1));
            primes[i].push_back(mp(dep[u], u));
        }
        while (curr % i == 0)
            curr = curr / i;
    }
    if (curr > 1)
    {
        dp[u] = max(dp[u], primes[curr].size() ? primes[curr].back() : mp(-1, -1));
        primes[curr].push_back(mp(dep[u], u));
    }
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == p)
            continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
    curr = arr[u];
    for (int i = 2; i * i <= curr; i++)
    {
        if (curr % i == 0)
        {
            primes[i].pop_back();
        }
        while (curr % i == 0)
            curr = curr / i;
    }
    if (curr > 1)
        primes[curr].pop_back();
}
signed main(void)
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dep[1] = 1;
    dfs(1, 0);
    for (int i = 1; i <= q; i++)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int u;
            cin >> u;
            cout << dp[u].second << '\n';
        }
        else
        {
            int u, p;
            cin >> u >> p;
            arr[u] = p;
            dfs(1, 0);
        }
    }
}