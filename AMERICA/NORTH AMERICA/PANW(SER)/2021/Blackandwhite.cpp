#include "bits/stdc++.h"
using namespace std;
const int N = 22;
int n;
double p[N];
double dp[1 << N];
double state[1 << N][2];
double f(int mask)
{
    if (dp[mask] != -1.0)
        return dp[mask];
    double expected = 0;
    double prob = 0;
    for (int i = 0; i < n; i++)
    {
        if (mask & (1 << i))
        {
            double pprob = (1.0 - p[i]) * state[mask xor (1 << i)][0] + p[i] * state[mask xor (1 << i)][1];
            expected += f(mask xor (1 << i)) * pprob;
            prob += pprob;
        }
    }
    return dp[mask] = (1.0 + expected) / prob; 
}
signed main(void)
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }
    for (int i = 0; i < (1 << n); i++)
    {
        dp[i] = -1.0;
        state[i][0] = state[i][1] = 1.0; 
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                state[i][0] *= p[j];
                state[i][1] *= 1.0 - p[j];
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            dp[(1 << i) | (1 << j)] = 0;
        }
    }
    f((1 << n) - 1); 
    cout << fixed << setprecision(10) << dp[(1 << n) - 1] << '\n'; 
    return 0;
}