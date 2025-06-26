#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
signed main(void)
{
    int N, M, K;
    while (cin >> N >> K)
    {
        vector<vector<int>> S(N, vector<int>(N));
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> S[i][j];
            }
        }
        cin >> M;
        --M;
        vector<int> P(M);
        vector<int64_t> dyn(N, 1), ndyn(N);
        for (int i = 0; i < M; i++)
        {
            cin >> P[i];
        }
        for (int i = 0; i < M; i++)
        {
            fill(ndyn.begin(), ndyn.end(), 0);
            for (int j = 0; j < N; j++)
            {
                int L = lower_bound(S[j].begin(), S[j].end(), P[i] - K) - S[j].begin();
                int R = upper_bound(S[j].begin(), S[j].end(), P[i] + K) - S[j].begin() - 1;
                if (L <= R)
                {
                    ndyn[L] += dyn[j]; 
                    if(R < N - 1) ndyn[R + 1] -= dyn[j]; 
                }
            }
            for (int j = 0; j < N; j++)
            {
                ndyn[j] = (ndyn[j] + mod + (j ? ndyn[j - 1] : 0)) % mod; 
            }
            ndyn.swap(dyn);
        }
        int64_t ret = 0;
        for (int i = 0; i < N; i++) ret = (ret + mod + dyn[i]) % mod;
        cout << ret << '\n';
    }
    return 0;
}

// d