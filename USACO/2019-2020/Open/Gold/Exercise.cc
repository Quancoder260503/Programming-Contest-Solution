#include "bits/stdc++.h"
using namespace std;
const int maxf = 1e4 + 10;
int mod, N, M;
vector<int> prime;
void init(void)
{
    vector<bool> vis(maxf);
    prime.push_back(1);
    for (int i = 2; i < maxf; i++)
        if (!vis[i])
        {
            prime.push_back(i);
            for (int j = 2 * i; j < maxf; j += i) vis[j] = 1;
        }
    M = prime.size();
    return;
}
int main(void)
{
    init();
    while (cin >> N >> mod)
    {
        vector<vector<int64_t>> dyn(M, vector<int64_t>(N + 1));
        for(int i = 0; i <= N; i++) dyn[0][i] = 1; 
        for (int i = 1; i < M; i++) for (int j = 0; j <= N; j++)
        {
            int pp = prime[i]; 
            for (int k = 0; pp <= j; k++)
            {
                dyn[i][j] = (dyn[i][j] + mod + 1LL * dyn[i - 1][j - pp] * pp) % mod; 
                pp = pp * prime[i]; 
            }
            dyn[i][j] = (dyn[i][j] + dyn[i - 1][j] + mod) % mod; 
        }
        cout << dyn[M - 1][N] << '\n'; 
    }
    return 0;
}