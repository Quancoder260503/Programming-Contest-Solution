#include "bits/stdc++.h"
using namespace std;
#define lint long long
signed main(void)
{
    string S, T;
    while (cin >> S >> T)
    {
        S = " " + S;
        int N = S.length();
        int M = T.length();
        vector<vector<int>> pos(N, vector<int>(26, -1));
        for (int i = 1; i < N; i++)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                pos[j][S[i] - 'a'] = i;
                if (S[i] == S[j])
                    break;
            }
        }
        auto chk = [&](int at) 
        {
            for (auto &c : T)
            {
                at = pos[at][c - 'a'];
                if (at == -1) return -1; 
            }
            return at; 
        };
        int at = 0;
        lint ans = 0;
        while (true)
        {
            int ret = chk(at); 
            if(ret == -1)
            {
                break;
            }
            else 
            {
                ans += 1LL * (N - ret) * (pos[at][T[0] - 'a'] - at);
                at = pos[at][T[0] - 'a']; 
                if (at == -1) break;
            }
        }
        cout << ans << '\n'; 
    }
    return 0;
}