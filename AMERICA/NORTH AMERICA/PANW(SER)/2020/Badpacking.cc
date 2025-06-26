#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int n, c;
    while (cin >> n >> c)
    {
        vector<int> arr(n);
        vector<int> acc(n + 1);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        sort(arr.begin(), arr.end());
        for (int i = 0; i < n; i++)
        {
            acc[i + 1] = acc[i] + arr[i];
        }
        vector<int> dyn(c + 1, 0);
        dyn[0] = 1;
        int ret = min(c, acc[n]);
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = c; j >= arr[i]; j--)
            {
                dyn[j] |= dyn[j - arr[i]];
            }
            for (int j = 0; j + acc[i] <= c; j++)
            {
                if (dyn[j] && j + acc[i] + arr[i] > c)
                {
                    ret = min(ret, j + acc[i]);
                }
            }
        }
        cout << ret << '\n';
    }
    return 0;
}