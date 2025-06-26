#include "bits/stdc++.h"
using namespace std;
#define lint long long
signed main(void)
{
    int n;
    cin >> n;
    vector<vector<lint>> arr(n, vector<lint>(4, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> arr[i][j];
        }
    }
    vector<lint> acc;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            acc.push_back(arr[i][0] + arr[j][1]);
        }
    }
    lint ans = 0;
    sort(acc.begin(), acc.end());
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ans += upper_bound(acc.begin(), acc.end(), -arr[i][2] - arr[j][3]) - lower_bound(acc.begin(), acc.end(), -arr[i][2] - arr[j][3]);
        }
    }
    cout << ans << '\n';
    return 0;
}