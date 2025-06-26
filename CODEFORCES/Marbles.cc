#include "bits/stdc++.h"
using namespace std;
using Lint = long long; 
const int M = 20;
const Lint INF = 1e14; 
signed main(void)
{ 
    int N;
    while(cin >> N)
    {
        vector<vector<Lint>> d(M, vector<Lint>(M));
        vector<Lint>c(M);
        for(int i = 0; i < N; i++)
        {
            int x; 
            cin >> x;
            --x; 
            for(int j = 0; j < M; j++)
            {
                d[x][j] += c[j]; 
            }
            c[x]++; 
        }
        vector<Lint>dyn((1 << M), INF); 
        dyn[0] = 0;
        for(int mask = 0; mask < (1 << M); mask++)
        {
            for(int i = 0; i < M; i++)
            {
                if((mask & (1 << i)) == 0) 
                {
                    Lint tot = 0; 
                    for(int j = 0; j < M; j++)
                    {
                        if(mask & (1 << j))
                        {
                            tot += d[i][j]; 
                        }
                    }
                    dyn[mask | (1 << i)] = min(dyn[mask | (1 << i)], dyn[mask] + tot); 
                }
            }
        }
        cout << dyn[(1 << M) - 1] << '\n'; 
    }
    return 0; 
}