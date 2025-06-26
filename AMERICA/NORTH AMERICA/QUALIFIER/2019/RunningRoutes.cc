#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int n; 
    cin >> n; 
    vector<vector<int>>g(n, vector<int>(n)), dyn(n, vector<int>(n)); 
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++)
    {
        cin >> g[i][j]; 
        dyn[i][j] = g[i][j]; 
    }
    for(int dist = 2; dist < n; dist++) for(int i = 0; i < n; i++) 
    {
        int j  = (i + dist)  % n;
        int ii = (i + 1) % n;  
        int jj = (j + n - 1) % n;
        for(int k = i; k != j; k = (k + 1) % n)
        {
            dyn[i][j] = max(dyn[i][j], dyn[i][k] + dyn[(k + 1) % n][j]); 
        }
        if(!g[i][j]) continue; 
        dyn[i][j] = max(dyn[i][j], dyn[ii][jj] + 1); 
    }
    cout << dyn[1][0] << '\n'; 
    return 0; 
}