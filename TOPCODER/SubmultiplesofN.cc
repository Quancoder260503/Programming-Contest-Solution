#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
#define Lint long long
class SubmultiplesOfN 
{
    public: 
    int solve(string S, int N)
    {
        S = " " + S;
        Lint M = S.length();
        vector<vector<int>> pos(M, vector<int>(10, -1));
        for (int i = 1; i < M; i++)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                pos[j][S[i] - '0'] = i;
                if (S[i] == S[j])
                    break;
            }
        }
        // dyn[i][j] = {the number of subsequence ending at ith with remainder jth}
        vector<vector<Lint>> dyn(M, vector<Lint>(N, 0));
        dyn[0][0] = 1;
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                for (int k = (i == 0); k < 10; k++)
                {
                    if (pos[i][k] == -1) continue;
                    dyn[pos[i][k]][(j * 10 + k) % N] = (dyn[pos[i][k]][(j * 10 + k) % N] + dyn[i][j] + mod) % mod;
                }
            }
        }
        Lint ret = 0;
        for (int i = 1; i < M; i++)
        {
            ret = (ret + mod + dyn[i][0]) % mod;
        }
        return (int)ret;
    }
}; 