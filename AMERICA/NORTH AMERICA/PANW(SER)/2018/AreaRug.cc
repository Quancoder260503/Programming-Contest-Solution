#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int N, M; 
    cin >> N >> M; 
    vector<vector<int>>g(N + 1, vector<int>(N + 1));
    vector<int>ctr((N + 1) * (N + 1), 0); 
    for(int i = 1; i <= N; i++) for(int j = 1; j <= N; j++)
    {
        char c;
        cin >> c; 
        g[i][j] = (c == 'D') - (i && j ? g[i - 1][j - 1] : 0) + (i ? g[i - 1][j] : 0) + (j ? g[i][j - 1] : 0); 
    }
    for(int i = 1; i <= N; i++) for(int j = 1; j <= N; j++)
    {
        if(i >= M && j >= M)
        {
            int c = g[i][j] + g[i - M][j - M] - g[i][j - M] - g[i - M][j];
            ctr[c]++; 
        }
    }
    for(int i = 0; i <= N * N; i++) if(ctr[i]) cout << i << " " << ctr[i] << '\n'; 
    return 0; 
}