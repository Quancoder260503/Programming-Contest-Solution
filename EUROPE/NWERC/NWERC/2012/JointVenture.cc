#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, x;
    while (cin >> x)
    {
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) cin >> arr[i];
        sort(arr.begin(), arr.end());
        x = x * 10000000;
        pair<int64_t, int64_t> ret = {-1, -1};
        int64_t res = -1;
        for (int i = 0; i < n; i++)
        {
            int pos = lower_bound(arr.begin(), arr.end(), x - arr[i]) - arr.begin();
            if(pos == n) continue;
            if (arr[pos] == x - arr[i])
            {
                if (res < abs(x - 2 * arr[i]))
                {
                    if (arr[i] * 2 == x)
                    {
                        if(pos + 1 < n && arr[pos + 1] != arr[i]) continue;
                        if(pos + 1 == n) continue;
                    }
                    res = abs(x - 2 * arr[i]);
                    ret = make_pair(arr[i], x - arr[i]);
                }
            }
        }
        if (ret.first > ret.second)
            swap(ret.first, ret.second);
        if (ret.first == -1)
            cout << "danger" << '\n';
        else
            cout << "yes " << ret.first << " " << ret.second << '\n';
    }
    return 0;
}