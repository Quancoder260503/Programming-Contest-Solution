#include "bits/stdc++.h"
using namespace std;
#define lint long long
signed main(void)
{
    int n;
    while (cin >> n)
    {
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        lint ret = 0;
        sort(arr.begin(), arr.end());
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                for (int k = j + 1; k < n; k++)
                {
                    if (arr[i] + arr[j] > arr[k])
                    {
                        ret += (1LL << (k - j - 1));
                    }
                }
            }
        }
        cout << ret << '\n';
    }
    return 0;
}