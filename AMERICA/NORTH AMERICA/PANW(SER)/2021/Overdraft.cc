#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int n;
    cin >> n;
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    auto chk = [&](int acc)
    {
        for (int i = 0; i < n; i++)
        {
            acc += arr[i];
            if (acc < 0)
                return 0;
        }
        return 1;
    };
    int lo = 0;
    int hi = 1e9 + 10;
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        if (chk(mid))
        {
            hi = mid;
        }
        else
        {
            lo = mid + 1;
        }
    }
    cout << lo << '\n';
    return 0;
}