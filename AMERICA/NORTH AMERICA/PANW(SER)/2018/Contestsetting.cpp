#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int MAXN = 2e3 + 10;
const int mod = 998244353;
int n, k;
lint dp[MAXN][MAXN];
int a[MAXN];
int cnt[MAXN];
lint C[MAXN][MAXN];
signed main(void)
{
    cin >> n >> k;
    vector<int> arr;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        arr.push_back(a[i]);
    }
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    for (int i = 0; i < n; i++)
    {
        a[i] = lower_bound(arr.begin(), arr.end(), a[i]) - arr.begin() + 1;
        cnt[a[i]]++;
    }
    int N = arr.size();
    dp[0][0] = 1; 
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            if(j > 0) dp[i][j] = (dp[i][j] + mod + 1LL * dp[i - 1][j - 1] * cnt[i]) % mod; 
            dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod; 
        }
    }
    cout << dp[N][k] % mod << endl;
    return 0;
}