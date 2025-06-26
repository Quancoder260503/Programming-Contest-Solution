#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int64_t B; 
    while(cin >> B && B)
    {
        string S, M;  
        cin >> S >> M; 
        int N = S.length();
        int n = M.length(); 
        int64_t mod  = 0;
        int64_t coef = 1;  
        reverse(S.begin(), S.end());
        reverse(M.begin(), M.end()); 
        for(int i = 0; i < n; i++) 
        { 
            mod += (M[i] - '0') * coef; 
            coef = coef * B; 
        } 
        coef = 1;
        int64_t ret = 0;  
        for(int i = 0; i < N; i++)
        {
            ret = (ret + coef % mod * (S[i] - '0') % mod) % mod; 
            coef = coef % mod * B % mod;
        }
        string res; 
        while(ret)
        {
            res = res + (char)(ret % B + '0'); 
            ret = (ret - ret % B) / B; 
        }
        reverse(res.begin(), res.end()); 
        if(res.size() == 0) res += '0'; 
        cout << res << '\n'; 
    }
    return 0;
}