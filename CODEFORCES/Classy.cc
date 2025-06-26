#include "bits/stdc++.h"
using namespace std;
int64_t doit(int at, int eq, int nzeros, string S, vector<vector<int64_t>>&dyn)
{
    if (nzeros > 3) return 0;
    if (at == -1) return 1;
    if (!eq && dyn[at][nzeros]) return dyn[at][nzeros];
    int ubound = eq ? (S[at] - '0') : 9;
    int64_t ret = 0;
    for (int i = 0; i <= ubound; i++)
    {
        ret += doit(at - 1, eq & (i == ubound), nzeros + (i > 0), S, dyn);
    }
    if(!eq) dyn[at][nzeros] = ret; 
    return ret; 
};
signed main(void)
{
    int T; 
    cin >> T;
    while(T--)
    {
        int64_t l, r;
        string L, R;
        cin >> l >> r;
        L = to_string(l - 1); 
        R = to_string(r); 
        auto calc = [&](string S)
        {
            int N = S.length();
            reverse(S.begin(), S.end()); 
            vector<vector<int64_t>>dyn(N, vector<int64_t>(4, 0));  
            return doit(N - 1, 1, 0, S, dyn); 
        }; 
        cout << calc(R) - calc(L) << '\n'; 
    }
    return 0; 
}