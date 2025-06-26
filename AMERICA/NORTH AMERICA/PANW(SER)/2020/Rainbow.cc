#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int mod = 998244353;
signed main(void)
{
    string a, b;
    cin >> a >> b;
    auto doit = [&](string a) -> pair<bool, lint>
    {
        if (a.length() < 3 && stoi(a) <= 10)
        {
            return {1, stoi(a)};
        }
        int N = a.length();
        vector<vector<lint>> dyn(N, vector<lint>(10, 0));
        vector<int> arr(N, 1);
        arr[0] = 1;
        for (int i = 1; i < N; i++)
        {
            arr[i] = (arr[i - 1] & (a[i] != a[i - 1]));
        }
        for (int i = 1; i < (a[0] - '0'); i++)
        {
            dyn[0][i]++;
        }
        for (int i = 1; i < N; i++)
        {
            if (arr[i - 1])
            {
                for (int j = 0; j < (a[i] - '0'); j++)
                {
                    if (j == (a[i - 1] - '0')) continue;
                    dyn[i][j]++;
                }
            }
            for (int j = 1; j <= 9; j++)
            {
                dyn[i][j]++;
            }
            for (int j = 0; j <= 9; j++)
            {
                for (int k = 0; k <= 9; k++)
                {
                    if (k == j) continue;
                    dyn[i][j] = (dyn[i][j] + mod + dyn[i - 1][k]) % mod;
                }
            }
        }
        lint ret = arr[N - 1];
        for (int i = 0; i <= 9; i++)
        {
            ret = (ret + mod + dyn[N - 1][i]) % mod;
        }
        return {arr[N - 1], ret};
    };
    auto [_a, reta] = doit(a);
    auto [_, retb] = doit(b);
    cout << (retb - reta + _a + mod) % mod << '\n';
    return 0;
}