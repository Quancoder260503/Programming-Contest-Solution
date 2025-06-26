#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    // x & y == x --> x is a submask of y
    // x | y == x --> y is a submask of x
    // x & y > 0 --> x and y have common bits
    // use inclusion - exclusion
    int n;
    cin >> n;
    int K = 20;
    vector<vector<int>> dyn((1 << K), vector<int>(2, 0));
    vector<int>arr(n, 0); 
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i]; 
        dyn[arr[i]][0]++;
        dyn[arr[i]][1]++;
    }
    for (int i = 0; i < K; i++)
    {
        for (int mask = 0; mask < (1 << K); mask++)
        {
            if (mask & (1 << i))
            {
                dyn[mask][0] += dyn[mask xor (1 << i)][0];
            }
        }
    }
    for (int i = K - 1; i >= 0; i--)
    {
        for (int mask = (1 << K) - 1; mask >= 0; mask--)
        {
            if ((mask & (1 << i)) == 0)
            {
                dyn[mask][1] += dyn[mask | (1 << i)][1];
            }
        }
    }
    int fmask = (1 << K) - 1;
    for(int i = 0; i < n; i++)
    {
        cout << dyn[arr[i]][0] << " " << dyn[arr[i]][1] << " " << n - dyn[arr[i] xor fmask][0] << '\n'; 
    }
    return 0;
}