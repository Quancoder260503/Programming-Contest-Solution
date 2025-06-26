#include "bits/stdc++.h"
using namespace std;

const int mod = 998244353;
const int maxf = 3e5 + 2; 

int main(void)
{
    string S;
    while(cin >> S)
    {
        int N = S.length(); 
        vector<int64_t>dyn(N / 2 + 1, 0); 
        vector<int64_t>coef(maxf, 1); 
        dyn[0] = 1; 
        int64_t ret = 0; 
        for(int y = 0; y < dyn.size(); y++)
        {
            for(int x = 0; x < y; x++) dyn[y] = (dyn[y] + dyn[x] * coef[x + y] % mod) % mod;
            for(int i = 0, j = N - 1 - y, sum = y + 1; i <= y; i++, sum++)
            {
                if(S[i] != '?' && S[j] != '?' && S[i] != S[j]) coef[sum] = 0; 
                if(S[i] == '?' && S[j] == '?') coef[sum] = coef[sum] * 26 % mod;
            }
            for(int i = y, j = N - 1, sum = y + 1; j > N - 1 - y; j--, sum++)
            {
                if (S[i] != '?' && S[j] != '?' && S[i] != S[j]) coef[sum] = 0;
                if (S[i] == '?' && S[j] == '?') coef[sum] = coef[sum] * 26 % mod;
            } 
            int64_t curr = dyn[y];
            for(int i = y; i + y < N; i++)
            {
                if(S[i] == '?') curr = curr * 26 % mod; 
            }
            //cout << curr << " " << dyn[y] << '\n'; 
            ret += curr; 
            ret %= mod; 
        }
        cout << ret << '\n'; 
    }
    return 0; 
}