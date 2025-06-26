#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N;
    while(cin >> N)
    {
        string S, T;
        cin >> S >> T; 
        vector<vector<int>>dyn(N, vector<int>(26)); 
        vector<vector<int>>dyn2(N, vector<int>(26)); 
        for(int i = 0; i < N; i++)
        { 
            dyn[i][S[i] - 'a']  += 1; 
            dyn2[i][T[i] - 'a'] += 1;
            if(i)
            {
                for(int j = 0; j < 26; j++)
                {
                    dyn2[i][j] += max(dyn2[i - 1][j], dyn[i - 1][j]); 
                    dyn[i][j]  += max(dyn[i - 1][j], dyn2[i - 1][j]); 
                }
            } 
        }
        int ret = 0; 
        for(int j = 0; j < 26; j++) ret = max(ret, max(dyn[N - 1][j], dyn2[N - 1][j])); 
        cout << ret << '\n'; 
    } 
    return 0; 
}