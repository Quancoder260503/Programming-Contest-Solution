#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int M, N, T;
    cin >> T;
    while (cin >> M >> N)
    {
        vector<string> S(N);
        for (int i = 0; i < N; i++)
        {
            cin >> S[i];
        }
        string ret = S[0];
        for (int k = 1; k < N; k++)
        {
            int at;
            for (int i = 0; i <= min((int) ret.size(), M); i++)
            {
                if(S[k].substr(0, i) == ret.substr(ret.size() - i, ret.size()))
                {
                    at = i; 
                }           
            }
            ret += S[k].substr(at, M);
        }
        cout << ret.size() << '\n';
    }
    return 0;
}