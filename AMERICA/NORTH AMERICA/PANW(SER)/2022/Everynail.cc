#include "bits/stdc++.h"
using namespace std; 
const int INF = 1e9; 
int main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>a(N); 
        for(int i = 0; i < N; i++) cin >> a[i]; 
        vector<vector<int>>ctr(N, vector<int>(3, 0)); 
        for(int i = 0; i < N; i++) 
        {
            ctr[i][a[i]]++; 
            for(int j = 0; j < 3; j++) ctr[i][j] += (i ? ctr[i - 1][j] : 0); 
        }
        vector<int>perm = {0, 1, 2}; 
        vector<vector<int>>dyn(N, vector<int>(3, 0));
        int ret = 0;
        do
        {
            for (int k = 0; k < 3; k++)
            {
                int opt = 0;
                for (int i = 0; i < N; i++)
                {
                    dyn[i][perm[k]] = opt + ctr[i][perm[k]];
                    if (k) opt = max(opt, dyn[i][perm[k - 1]] - ctr[i][perm[k]]);
                }
            }
            ret = max(ret, dyn[N - 1][perm[2]]);
        } 
        while (next_permutation(perm.begin(), perm.end()));
        cout << ret << '\n';
    }
    return 0; 
}