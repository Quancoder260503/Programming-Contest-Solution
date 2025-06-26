#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int mod = 1e9 + 9;
signed main(void)
{
    int K, N;
    while (cin >> K >> N)
    {
        vector<vector<lint>> dyn(N + 1, vector<lint>(K, 0));
        vector<vector<lint>> c(N + 1, vector<lint>(K, 0));
        c[0][0] = 1;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < K; j++)
            {
                c[i + 1][(2 * j) % K] = (c[i + 1][2 * j % K] + mod + c[i][j]) % mod;
                c[i + 1][(2 * j + 1) % K] = (c[i + 1][(2 * j + 1) % K] + c[i][j] + mod) % mod;
                dyn[i + 1][(2 * j) % K] = (dyn[i + 1][2 * j % K] + dyn[i][j] + mod) % mod;
                dyn[i + 1][(2 * j + 1) % K] = (dyn[i + 1][(2 * j + 1) % K] + c[i][j] + dyn[i][j] + mod) % mod;
            }
        }
        cout << dyn[N][0] << '\n';
    }
    return 0;
}