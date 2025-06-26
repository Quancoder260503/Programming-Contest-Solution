#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    string S;
    while(cin >> S)
    {
        S = " " + S; 
        int N = S.length(); 
        vector<vector<int>>dyn(N, vector<int>(2)); 
        dyn[0][0] = 0; 
        dyn[0][1] = 1; 
        for(int i = 1; i < N; i++)
        {
            dyn[i][0] = min(dyn[i - 1][0] + S[i] - '0',     dyn[i - 1][1] + 10 - (S[i] - '0'));
            dyn[i][1] = min(dyn[i - 1][0] + S[i] - '0' + 1, dyn[i - 1][1] + 10 - (S[i] - '0' + 1));  
        }
        cout << dyn[N - 1][0] << '\n'; 
    }
    return 0; 
}