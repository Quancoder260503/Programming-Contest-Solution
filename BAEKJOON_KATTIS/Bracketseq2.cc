#include "bits/stdc++.h"

using namespace std; 
const int mod = 1e9 + 7;

const int maxf = 1e6 + 10;
int64_t fac[maxf], iv[maxf];

int64_t fpow(int64_t a, int64_t k)
{
    if (!k)
        return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k)
    {
        if (k & 1)
        {
            res = (long long)res * tmp % mod;
        }
        tmp = (long long)tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}

void init_C(int n)
{
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = 1LL * fac[i - 1] % mod * i % mod;
    iv[n] = fpow(fac[n], mod - 2);
    for (int i = n - 1; ~i; --i)
        iv[i] = 1LL * iv[i + 1] % mod * (i + 1) % mod;
}

int64_t C(int n, int k)
{
    if(n < k) return 0; 
    return fac[n] % mod * iv[k] % mod * iv[n - k] % mod; 
}

int main(void)
{
    int N; 
    string S; 
    init_C(maxf - 1); 
    while(cin >> N >> S)
    { 
        int flag = 1; 
        int K = S.length(); 
        int open = 0, close = 0;
        for(int i = 0; i < K; i++)
        {
            open  += (S[i] == '(');
            close += (S[i] == ')'); 
            if(open < close)
            {
                cout << 0 << '\n';
                flag = 0; 
                break; 
            }
        }
        if(!flag) continue; 
        if(N & 1 || open > N / 2)
        {
            cout << 0 << '\n';
        } 
        else 
        {
            int64_t ret = C(N - K, N / 2 - open);
            ret = (-C(N - K, N / 2 - open - 1) + ret + mod) % mod;
            cout << ret << '\n';
        }
    }
    return 0; 
}