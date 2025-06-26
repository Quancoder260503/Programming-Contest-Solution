#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int n, k;
    while (cin >> n >> k)
    {
        int ans = 0;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            string answer;
            cin >> answer;
            for (int j = 0; j < k; j++)
            {
                if (answer[j] == 'T') arr[i] |= (1 << j);
            }
        }
        for (int mask = 0; mask < (1 << k); mask++)
        {
            int ret = INT_MAX;
            for (int i = 0; i < n; i++)
            {
                ret = min(ret, k - __builtin_popcount(mask xor arr[i])); 
            }
            ans = max(ret, ans); 
        }
        cout << ans << '\n'; 
    }
    return 0;
}