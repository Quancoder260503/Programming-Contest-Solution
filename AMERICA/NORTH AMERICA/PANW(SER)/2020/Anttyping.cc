#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    string S;
    while (cin >> S)
    {
        int N = S.length();
        vector<int> key(9); 
        vector<vector<int>>mat(10, vector<int>(10, 0)); 
        for(int i = 1; i < N; i++)
        {
            mat[S[i - 1] - '0'][S[i] - '0']++; 
        }
        iota(key.begin(), key.end(), 1);
        int ret = INT_MAX;
        do
        {
            vector<int>at(10);
            for(int i = 0; i < 9; i++)
            {
                at[key[i]] = i; 
            }
            int curr = (at[S[0] - '0']) + 1;
            for(int i = 1; i < 10; i++)
            {
                for(int j = 1; j < 10; j++)
                {

                    curr += mat[i][j] * (abs(at[i] - at[j]) + 1); 
                }
            }
            ret = min(curr, ret);
        }  
        while (next_permutation(key.begin(), key.end()));
        cout << ret << '\n'; 
    }
    return 0;
}