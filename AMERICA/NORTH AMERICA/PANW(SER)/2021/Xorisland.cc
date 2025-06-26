#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    vector<int> dyn((1 << n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if ((arr[i] xor arr[j] xor arr[k]) == 0)
                {
                    dyn[(1 << i) | (1 << j) | (1 << k)]++;
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int mask = 0; mask < (1 << n); mask++)
        {
            if (mask & (1 << i))
            {
                dyn[mask] += dyn[mask xor (1 << i)]; 
            }
        }
    }
    int ans = INT_MAX; 
    for(int mask = 0; mask < (1 << n); mask++)
    {
        if(dyn[mask] > 0) continue; 
        ans = min(ans, n - __builtin_popcount(mask)); 
    }
    cout << ans << '\n'; 
    return 0;
}
/*
   A[k] = A[i] xor A[j]
   A[k] = A[ii] xor A[kk]
   Since xor is a 1-1 function which mean for an integer k, there exist a unique pair (i, j) such that k = i ^ j
   Thus we do a bitmask - dp with ith bit is off when the ith person know their values
    
*/