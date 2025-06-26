#include "bits/stdc++.h"
using namespace std;
#define lint long long
signed main(void)
{
    int n, K;
    cin >> n >> K;
    // How many ways are there to select problems such that the kth and (k - 1) th problems are i and j (i > j)
    vector<int> diff(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> diff[i];
    }
    sort(diff.begin(), diff.end()); 
    vector<vector<vector<lint>>> dyn(n, vector<vector<lint>>(n, vector<lint>(K + 1, 0)));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            dyn[i][j][2]++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            for (int k = 0; k < j; k++)
            {
                for (int prob = 3; prob <= K; prob++)
                {
                    if (diff[i] <= diff[j] + diff[k])
                    {
                        dyn[i][j][prob] += dyn[j][k][prob - 1];
                    }
                }
            }
        }
    }
    lint ans = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            ans += dyn[i][j][K]; 
        }
    }
    cout << ans << '\n'; 
    return 0;
}