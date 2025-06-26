#include "bits/stdc++.h"
using namespace std;
int n, t, q;
void solve()
{
    cin >> n >> q;
    int rmax = 0, wmax = 0;
    for (int i = 1; i <= q; i++)
    {
        int a, b;
        cin >> a >> b;
        rmax = max(rmax, a);
        wmax = max(wmax, b);
    }
    if (rmax + wmax > n)
    {
        puts("IMPOSSIBLE");
        return;
    }
    for (int i = 0; i < rmax; i++)
    {
        cout << "R";
    }
    for (int i = rmax; i < n; i++)
    {
        cout << "W";
    }
    cout << '\n';
    return;
}
signed main(void)
{
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}