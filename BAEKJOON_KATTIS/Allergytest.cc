#include "bits/stdc++.h"
using namespace std;
const int INF = 1e9;
signed main(void)
{
    int n;
    cin >> n;
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    vector<vector<int>> dyn((1 << n), vector<int>(7, INF));
    dyn[0][0] = 0;
    for (int mask = 0; mask < (1 << n); mask++)
    {
        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
            {
                for (int j = 0; j < 7; j++)
                {
                    int curr = max(0, arr[i] - j - 1);
                    dyn[mask][curr] = min(dyn[mask][curr], dyn[mask xor (1 << i)][j] + curr + 1);
                }
            }
        }
    }
    cout << *min_element(dyn[(1 << n) - 1].begin(), dyn[(1 << n) - 1].end()) << '\n';
    return 0;
}