#include "bits/stdc++.h"
using namespace std;
const int INF = 1e9; 
const int maxf = 3e5 + 2; 
int main(void)
{
    int N, X; 
    int L = 8 * 60; 
    while(cin >> N >> X)
    { 
        vector<int>prefix(maxf); 
        for(int i = 0; i < N; i++)
        {
            int L, R; 
            cin >> L >> R; 
            prefix[L]++; 
            prefix[L + R + 1]--; 
        }
        for(int i = 1; i < maxf; i++) prefix[i] += prefix[i - 1]; 
        pair<int, int>ret = {INF, INF};  
        for(int i = 0; i <= L; i++)
        {
            int ctr = 0; 
            for(int j = i; j < maxf; j += X)
            {
                ctr += (prefix[j] > 0); 
            }
            ret = min(ret, {ctr, i}); 
        }
        cout << ret.second << " " << ret.first << '\n'; 
    }
    return 0; 
}