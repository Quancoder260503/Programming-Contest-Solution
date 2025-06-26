#include "bits/stdc++.h"
using namespace std;
#define lint long long
signed main(void)
{
    int n, m, K, mod;
    cin >> n >> m >> K >> mod;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    vector<vector<vector<lint>>> dyn(2, vector<vector<lint>>(m + 1, vector<lint>(K + 1, 0)));
    dyn[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            for (int k = 0; k <= K; k++)
            {
                dyn[1][j][k] = dyn[0][j][k];
                if (j > 0 && k >= arr[i])
                {
                    dyn[1][j][k] = (mod + dyn[1][j - 1][k - arr[i]] + dyn[1][j][k]) % mod;
                }
            }
        }
        dyn[0] = dyn[1]; 
    }
    lint ans = 0;
    for (int i = 0; i <= K; i++)
    {
        ans = (ans + dyn[1][m][i] + mod) % mod;
    }
    cout << ans << '\n';
    return 0;
}
// dyn[i][j][k] = {number of ways to write j lines of code with k bugs created using the first i programmers }