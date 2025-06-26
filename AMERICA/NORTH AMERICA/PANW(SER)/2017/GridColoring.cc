#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e3 + 2; 
int64_t dyn[maxf][maxf], prefix[maxf][maxf]; 

int main(void)
{
    int N, M; 
    while(cin >> N >> M)
    {
        vector<vector<char>>g(N + 1, vector<char>(M + 1)); 
        vector<int>last_b(M + 1, 0); 
        for(int i = 1; i <= N; i++) for(int j = 1; j <= M; j++)
        {
            cin >> g[i][j]; 
            prefix[i][j] = (g[i][j] == 'R') + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1]; 
            if(g[i][j] == 'B') last_b[j] = max(i, last_b[j]); 
        }
        dyn[0][N] = 1; 
        for(int j = 1; j <= M; j++)
        {   
            for(int i = 0; i <= N && !prefix[i][j]; i++)
            { 
                for(int k = max(i, last_b[j - 1]); k <= N; k++)
                {
                    dyn[j][i] += dyn[j - 1][k]; 
                }
            } 
        }
        int64_t ret = 0; 
        for(int j = last_b[M]; j <= N; j++) ret += dyn[M][j]; 
        cout << ret << '\n'; 
    }
    return 0; 
}