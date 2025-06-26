#include "bits/stdc++.h"
using namespace std;
const int M = 1e4 + 10; 
double EPS = 1e-7; 
signed main(void)
{
    double N;
    int Q; 
    while(cin >> N >> Q)
    {
        vector<vector<double>>dyn(M, vector<double>((int)N + 1)); 
        dyn[0][0] = 1; 
        for(int i = 1; i < M; i++)
        {
            for(int j = 1; j <= N; j++)
            {
                dyn[i][j] = dyn[i - 1][j - 1] * (N - j + 1) / N + dyn[i - 1][j] * j / N; 
            }
        }  
        for(int i = 0; i < Q; i++)
        {
            double P; 
            cin >> P; 
            for(int i = 1; i < M; i++)
            {
                if(dyn[i][N] * 2000 > P)
                {
                    cout << i << '\n'; 
                    break; 
                }
            }
        }
    }
    return 0; 
}