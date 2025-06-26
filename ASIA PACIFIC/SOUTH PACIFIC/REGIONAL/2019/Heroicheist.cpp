#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)1e3 + 10;
int n;
vector<int> adj[MAXN];
set<int> keys[MAXN];
int match[MAXN];
bool vis[MAXN];
bool dfs(int u)
{
    if (vis[u])
        return false;
    vis[u] = true;
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (!match[v] || dfs(match[v]))
        {
            match[v] = u;
            return true;
        }
    }
    return false;
}
signed main(void)
{
    cin >> n;
    vector<int> ord;
    for (int i = 1; i <= n; i++)
    {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j++)
        {
            int x;
            cin >> x;
            keys[i].insert(x);
        }
        if (keys[i].size())
        {
            ord.push_back(i);
        }
    }
    set<int> now;
    ord.push_back(n + 1); 
    for (int i = 0; i < ord.size(); i++)
    {
        if (i == 0 || ord[i] == ord[i - 1] + 1)
        {
            now.insert(ord[i]);
            continue;
        }
        else
        {
            for (auto it : now)
            {
                vector<int> err;
                for (auto it2 : keys[it])
                {
                    if (it2 <= ord[i - 1])
                    {
                        err.push_back(it2);
                    }
                }
                for (int j = 0; j < err.size(); j++)
                {
                    keys[it].erase(err[j]);
                }
            }
            for (int j = 1; j <= n; j++)
            {
                adj[j].clear();
                match[j] = vis[j] = 0;
            }
            for (auto it : now)
            {
                for (auto it2 : keys[it])
                {
                    adj[it].push_back(it2);
                }
            }
            for (auto it : now)
            {
                fill(vis + 1, vis + n + 1, 0);
                dfs(it);
            }
            for (int j = ord[i - 1] + 1; j <= n; j++)
            {
                if (match[j] == 0 || j == ord[i])
                {
                    if(j < ord[i])
                    {
                        cout << j - 1 << '\n'; 
                        return 0; 
                    }
                    break; 
                }
                else
                {
                    now.erase(match[j]);
                }
            }
            now.insert(ord[i]); 
        }
    }
    cout << n << '\n';
    return 0;
}