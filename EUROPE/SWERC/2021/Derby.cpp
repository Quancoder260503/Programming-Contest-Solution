#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define pii pair<lint, int>
#define mp make_pair
int n, v;
vector<int> t, g;
bool cmp(const int a, const int b)
{
    if (1LL * t[a] * v + g[a] == 1LL * t[b] * v + g[b])
    { 
         return 1LL * t[a] * v - g[a] < 1LL * t[b] * v - g[b];
    }
    return 1LL * t[a] * v + g[a] < 1LL * t[b] * v + g[b];
}
signed main(void)
{
    cin >> n >> v;
    t.resize(n + 1);
    g.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> t[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> g[i];
    }
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), cmp);
    vector<lint> lis;
    for (int i = 0; i < n; i++)
    {
        int k = ord[i]; 
        if (1LL * t[k] * v + g[k] < 0 || 1LL * t[k] * v - g[k] < 0) continue;
        int pos = lower_bound(lis.begin(), lis.end(), 1LL * t[k] * v - g[k] + 1) - lis.begin();
        if (pos == (int)lis.size())
        {
            lis.push_back(1LL * v * t[k] - g[k]);
        }
        else
        {
            lis[pos] = 1LL * v * t[k] - g[k];
        }
    }
    cout << (int)lis.size() << '\n';
    return 0;
}
/*
    In this one we need to final the maximum subset of kicks
    Note that in the optimal solution
    Let n be the size of the optimal set
    (0, 0) < (t1, g1) < (t2, g2) < (t3, g3) < ... < (tn, gn)
    Thus for (t[i + 1] - t[i]) * v >= |g[i + 1] - g[i]|
             (t[i + 1] - t[i]) * v >= g[i + 1] - g[i]
             (t[i + 1] - t[i]) * v >= g[i] - g[i + 1]
             t[i + 1] * v + g[i + 1] >= t[i] * v + g[i]

           (This is just LIS of the sequence)
*/