#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)2e5 + 10
#define mp make_pair
int n;
int ans[MAXN];
map<int, int> vis;
signed main(void)
{
    cin >> n;
    using T = pair<pair<int, int>, int>;
    priority_queue<T, vector<T>, greater<T> > pq;
    for (int i = 1; i <= n; i++)
    {
        int x, d;
        cin >> x >> d;
        pq.push(mp(mp(max(x - d, 1), x), i));
    }
    vis[0] = 1;
    while (pq.size())
    {
        auto curr = pq.top().first;
        int idx = pq.top().second;
        int now = curr.first;
        if (vis[now])
        {
            vector<T> del;
            while (pq.size() && now == pq.top().first.first)
            {
                del.push_back(pq.top());
                pq.pop();
            }
            for (int j = 0; j < del.size(); j++)
            {
                auto curr = del[j].first;
                int idx = del[j].second;
                pq.push(mp(mp(curr.first + j + 1, curr.second), idx));
            }
        }
        else
        {
            vis[now] = 1;
            ans[idx] = now;
            pq.pop();
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " ";
    }
    cout << '\n';
    return 0;
}