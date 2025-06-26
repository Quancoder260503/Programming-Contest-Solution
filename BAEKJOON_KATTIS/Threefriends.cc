#include "bits/stdc++.h"
using namespace std;
#define Lint long long
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>arr(N); 
        vector<Lint>modulo(5); 
        for(int i = 0; i < N; i++)
        {
            cin >> arr[i]; 
        }
        vector<vector<int>>prefix(N, vector<int>(5)); 
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < 5; j++)
            {
                prefix[i][(arr[i] + j) % 5] += modulo[j]; 
            }
            modulo[arr[i] % 5]++;  
        }
        fill(modulo.begin(), modulo.end(), 0); 
        Lint ret = 0; 
        for(int i = 0; i < N; i++)
        {
            ret += modulo[(5 - arr[i] % 5) % 5];
            for(int j = 0; j < 5; j++)
            {
                modulo[j] += prefix[i][j]; 
            } 
        }
        cout << ret << '\n'; 
    }
    return 0; 
}