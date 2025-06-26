#include "bits/stdc++.h"
using namespace std;
const int MAXN = 101;
int dp[MAXN][MAXN];
int arr[MAXN];
int n, m;
signed main(void)
{
    cin >> n >> m;
    memset(dp, 63, sizeof(dp));
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    dp[0][0] = 0;
    for (int p = 1; p <= m; p++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                vector<int> curr;
                for (int k = j; k <= i; k++)
                {
                    curr.push_back(arr[k]);
                }
                sort(curr.begin(), curr.end());
                int N = curr.size();
                int mid = N / 2;
                int acc = 0; 
                for(int k = j; k <= i; k++)
                {
                   acc += abs(curr[mid] - arr[k]); 
                }
                dp[i][p] = min(dp[i][p], acc + dp[j - 1][p - 1]); 
            }
        }
    }
    cout << dp[n][m] << endl; 
    return 0;
}