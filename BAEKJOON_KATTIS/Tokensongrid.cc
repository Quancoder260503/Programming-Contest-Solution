#include "bits/stdc++.h"
using namespace std;
const int maxf = (1 << 21);
const int mod = 1e9 + 7;
int64_t fpow(int64_t a, int64_t k)
{
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k)
    {
        if (k & 1)
        {
            res = (int64_t)res * tmp % mod;
        }
        tmp = (int64_t)tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}
void add(int64_t &a, int64_t b)
{
    a = (a + b + mod) % mod;
    return; 
}
void FWHT(int64_t *P, int deg, bool invert)
{
    for (int len = 1; 2 * len <= deg; len = len * 2)
    {
        for (int i = 0; i < deg; i += 2 * len)
        {
            for (int j = 0; j < len; j++)
            {
                int64_t u = P[i + j];
                int64_t v = P[i + j + len];
                if(!invert) add(P[i + j + len], P[i + j]);
                else        add(P[i + j + len], -P[i + j]); 
            }
        }
    } 
}
int64_t P[maxf], P2[maxf], ret[maxf]; 
int main(void)
{
    int N, M;
    while (cin >> N >> M)
    {
        vector<vector<char>>S(N, vector<char>(M)); 
        P[0] = 1; 
        FWHT(P, (1 << N), 0); 
        for(int i = 0; i < N; i++) for(int j = 0; j < M; j++)
        {
            cin >> S[i][j]; 
        }
        for(int j = 0; j < M; j++) 
        {
            vector<int64_t>mask(26); 
            for (int i = 0; i < N; i++) if(S[i][j] != '.')
            {
                mask[S[i][j] - 'a'] += (1 << i); 
            }
            for (int i = 0; i < (1 << N); i++) P2[i] = 0;
            P2[0] = 1;  
            for(int i = 0; i < 26; i++)
            {
                for(int j = mask[i]; j > 0; j = (j - 1) & mask[i])
                {
                    P2[j]++; 
                }
            }
            FWHT(P2, (1 << N), 0); 
            for(int i = 0; i < (1 << N); i++) P[i] = P[i] * P2[i] % mod; 
        }
        FWHT(P, (1 << N), 1); 
        for(int i = 0; i < (1 << N); i++) 
        {
            add(ret[__builtin_popcount(i)], P[i]);
        }
        for(int i = N; i >= 0; i--) cout << ret[i] << ' '; 
    }
    return 0;
}