#include "bits/stdc++.h"
using namespace std;
#define lint long long
signed main(void)
{
    int T, n, m;
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        map<vector<int>, vector<int>> L, R;
        vector<int> corr(n);
        vector<string> S(n);
        for (int i = 0; i < n; i++)
        {
            cin >> S[i] >> corr[i];
        }
        int Ls = m / 2; 
        int Rs = m / 2 + 1;
        vector<int>LM; 
        vector<int>RM;
        for(int i = 0; i < n; i++)
        { 
            int ret = 0; 
            for(int k = 0; k <= Ls; k++)
            {
                ret = ret | ((1 << k) * (S[i][k] - '0')); 
            }
            LM.push_back(ret); 
            ret = 0; 
            for(int k = Rs; k < m; k++)
            {
                ret = ret | ((1 << (k - Rs)) * (S[i][k] - '0')); 
            }
            RM.push_back(ret); 
        }
        auto solve = [&](int l, int r, map<vector<int>, vector<int>>&P, vector<int>&M)
        {
            int N = r - l + 1; 
            int rmask = (1 << N) - 1;
            for(int mask = 0; mask < (1 << N); mask++)
            {
                vector<int>correct; 
                for(int i = 0; i < n; i++)
                {
                    correct.push_back(__builtin_popcount(M[i] xor mask xor rmask)); 
                }
                P[correct].push_back(mask);  
            }
        };
        solve(0, Ls, L, LM);
        solve(Rs, m - 1, R, RM);
        pair<int, int>res; 
        int ans = 0; 
        for(auto [ret, left] : L)
        {
            vector<int>rret; 
            for(int i = 0; i < n; i++)
            {
                rret.push_back(corr[i] - ret[i]); 
            }
            if(R.count(rret) == 0) continue; 
            auto right = R[rret]; 
            ans += (int) right.size() * (int)left.size(); 
            res = {left[0], right[0]}; 
        }
        if(ans == 1)
        {
            for(int i = 0; i <= Ls; i++)
            {
                cout << ((res.first >> i) & 1); 
            }
            for(int i = Rs; i < m;  i++)
            {
                cout << ((res.second >> (i - Rs)) & 1); 
            }
            cout << '\n';
        }
        else 
        {
             cout << ans << " solutions\n"; 
        }
    }
    return 0;
}