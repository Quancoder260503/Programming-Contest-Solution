#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N, M, T;
    while (cin >> N >> T >> M)
    {
        vector<pair<int32_t, int32_t>>dyn(M + 1, {INT32_MAX, 0}); 
        vector<int32_t>arr(M + 1); 
        for(int i = 1; i <= M; i++)
        {
            cin >> arr[i]; 
        } 
        dyn[0] = {0, 0}; 
        for(int i = 1; i <= M; i++)
        {
            for(int j = max(0, i - N); j < i; j++)
            {
                dyn[i] = min(dyn[i], {max(arr[i], dyn[j].first) + 2 * T, dyn[j].second + 1}); 
            }
        }
        cout << dyn[M].first - T << " " << dyn[M].second << '\n'; 
    }
    return 0; 
}