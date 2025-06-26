#include "bits/stdc++.h"

using namespace std;

const int INF = 1e9;

int main(void)
{
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    vector<vector<int>> dyn(n + 1, vector<int>(n + 1, -1));
    function<int(int, int)> f = [&](int l, int r)
    {
        if (l == r)
            return 0;
        if (dyn[l][r] != -1)
            return dyn[l][r];
        int &ret = dyn[l][r];
        ret = INF;
        for (int i = l; i < r; i++)
        {
            ret = min(ret, f(l, i) + f(i + 1, r) + (arr[l] != arr[i + 1]));
        }
        return ret;
    };
    cout << f(0, n) << '\n';
    return 0;
}