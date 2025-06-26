#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    vector<int> ctr(3);
    for (int i = 1; i <= n; i++)
    {
        ctr[i % 3] += b[i];
    }
    int64_t rwhite = 0, rpink = 0, ryellow = 0;
    for (int i = 1; i <= n; i++)
    {
        ryellow += 1LL * a[i] * ctr[(3 - i % 3) % 3];
        rpink += 1LL * a[i] * ctr[(4 - i % 3) % 3];
        rwhite += 1LL * a[i] * ctr[(5 - i % 3) % 3];
    }
    cout << ryellow << " " << rpink << " " << rwhite << '\n';
    return 0;
}