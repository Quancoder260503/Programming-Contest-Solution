#include "bits/stdc++.h"
using namespace std;
int n, m;
const int MAXN = 3e5 + 10;
int cake[MAXN];
int cus[MAXN];
int cnt[MAXN];
vector<int> cakes[MAXN];
signed main(void)
{
    cin >> n >> m;
    for (int i = 0; i < 6; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++)
        {
            cake[j] += (1 << i) * (s[j] - '0');
        }
    }
    for (int i = 0; i < 6; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++)
        {
            cus[j] += (1 << i) * (s[j] - '0');
        }
    }
    for (int i = 0; i < n; i++)
    {
        cakes[cake[i]].push_back(i);
    }
    for (int i = 0; i < m; i++)
    {
        int mask = cus[i];
        pair<int,int> opt = {-1, -1};
        for (int fmask = 0; fmask < (1 << 6); fmask++)
        {
            if ((fmask & mask) == mask && cakes[fmask].size())
            {
                opt = max(opt, {cakes[fmask].back() + 1, fmask});
            }
        }
        cout << opt.first << " ";
        if(opt.first != -1)
        {
            cakes[opt.second].pop_back(); 
        }
    }
    cout << '\n';
    return 0;
}