#include "bits/stdc++.h"
using namespace std;
#define Lint long long
const int mod = 1e9 + 7;
signed main(void)
{
    int N, K;
    while (cin >> N >> K)
    {
        int M = 500;
        vector<vector<Lint>> dyn(M + 1, vector<Lint>(M * (M + 1) / 2 + 1, 0));
        for (int i = 1; i <= N; i++)
        {
            int inv = i * (i - 1) / 2;
            dyn[i][0] = dyn[i][inv] = 1;
            for (int j = 1; j <= inv / 2; j++)
            {
                dyn[i][j] = (dyn[i - 1][j] + dyn[i][j - 1] + mod) % mod;
                if (j >= i)
                    dyn[i][j] = (dyn[i][j] - dyn[i - 1][j - i] + mod) % mod;
            }
            for (int j = inv / 2 + 1; j < inv; j++)
            {
                dyn[i][j] = dyn[i][inv - j];
            }
        }
        cout << dyn[N][K] << '\n';
    }
    return 0;
}