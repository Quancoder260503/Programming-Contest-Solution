#include "bits/stdc++.h"

using namespace std;
const int maxf = 1e5 + 2;
const int LG = 28;

int N, K;
int64_t vis[maxf][LG + 2][4];
int64_t dyn[maxf][LG + 2];
int64_t ret[maxf];

struct node
{
    vector<int>s; 
    node operator+(const node &other)
    {
        node ret;
        vector<int>curr; 
        for (auto it : s)
        {
            curr.push_back(it);
        }
        for (auto it : other.s)
        {
            curr.push_back(it);
        }
        sort(curr.rbegin(), curr.rend()); 
        while (curr.size() > 4)
        {
            curr.pop_back(); 
        }
        ret.s = curr;
        return ret;
    }
} tree[maxf * 4], null;

void update(int val, int pos, int l = 1, int r = N, int p = 1)
{
    if (l == r)
    {
        tree[p].s.push_back(val);
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        update(val, pos, l, mid, 2 * p);
    else
        update(val, pos, mid + 1, r, 2 * p + 1);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
    return;
}
node query(int L, int R, int l = 1, int r = N, int p = 1)
{
    if (L > r || R < l) return null;
    if (L <= l && r <= R) return tree[p];
    int mid = (l + r) / 2;
    return query(L, R, l, mid, 2 * p) + query(L, R, mid + 1, r, 2 * p + 1);
}
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while (cin >> N >> K)
    {
        vector<pair<int, int>> point;
        point.push_back({0, 0});
        for (int i = 1; i <= N; i++)
        {
            int x;
            cin >> x;
            point.push_back({x, i});
        }
        sort(point.begin(), point.end());
        N = point.size();
        for (int i = 0; i < point.size(); i++)
        {
            update(point[i].second, i + 1);
        }
        memset(dyn, 63, sizeof(dyn));
        memset(ret, 63, sizeof(ret));
        memset(vis, -1, sizeof(vis));

        for (int len = (1 << LG), d = LG; d >= 0; len = len / 2, d--)
        {
            for (int i = 0; i < point.size(); i++)
            {
                int L = point[i].first - len;
                int R = point[i].first + len;
                pair<int, int> pL = {L, -1}, pR = {R, -1};
                L = lower_bound(point.begin(), point.end(), pL) - point.begin() + 1;
                pL = {L, 1e8}, pR = {R, 1e8};
                R = upper_bound(point.begin(), point.end(), pR) - point.begin();
                auto curr = query(L, R);
                int ctr = 0;
                for (auto it : curr.s)
                {
                    vis[point[i].second][d + 1][ctr++] = it;
                }
            }
        }
        for (int i = 0; i <= N; i++) vis[i][0][0] = i;
        vector<pair<int, int>> q;
        q.push_back({0, 1});
        dyn[0][1] = 0;
        for (int steps = 0; q.size(); steps++)
        {
            vector<pair<int, int>> q2;
            for (auto [u, d] : q)
            {
                if (d > 0 && dyn[u][d - 1] > steps + 1)
                {
                    dyn[u][d - 1] = steps + 1;
                    q2.push_back({u, d - 1});
                }
                if (d < LG && dyn[u][d + 1] > steps + 1)
                {
                    dyn[u][d + 1] = steps + 1;
                    q2.push_back({u, d + 1});
                }
                for (int k = 0; k < K; k++)
                {
                    int at = vis[u][d][k];
                    if (at == u)
                    {
                        ret[u] = min(ret[u], (int64_t)steps);
                    }
                    if (at != -1 && dyn[at][d] > steps + 1)
                    {
                        dyn[at][d] = steps + 1;
                        q2.push_back({at, d});
                    }
                }
            }
            q.swap(q2);
        }
        for (int i = 1; i < N; i++)
            cout << (ret[i] > (int64_t)1e8 ? -1 : ret[i]) << '\n';
    }
    return 0;
}