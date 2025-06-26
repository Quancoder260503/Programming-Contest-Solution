#include "bits/stdc++.h"
using namespace std;
#define lint long long
lint a, b;
map<lint, int> mp;
signed main(void)
{
    cin >> a >> b;
    lint A = a;
    lint B = b;
    for (lint i = 2; 1LL * i * i <= a; i++)
    {
        if (a % i == 0)
        {
            int cnt = 0;
            while (a % i == 0) a = a / i, cnt++;
            mp[i] += cnt;
        }
    }
    for (lint i = 2; 1LL * i * i <= b; i++)
    {
        if (b % i == 0)
        {
            int cnt = 0;
            while (b % i == 0) b = b / i, cnt++;
            mp[i] += cnt;
        }
    }
    if (a > 1)
    {
        mp[a] += 1;
    }
    if (b > 1)
    {
        mp[b] += 1;
    }
    if (mp.count(A) && mp.count(B))
    {
        puts(A != B ? "full credit" : "no credit");
    }
    else
    {
        bool good = 1;
        for (auto [p, cnt] : mp)
        {
            good = good & (cnt <= 1);
        }
        puts(good ? "partial credit" : "no credit");
    }
    return 0;
}