#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N, M; 
    while (cin >> N >> M)
    {
        vector<int>arr(N);
        iota(arr.begin(), arr.end(), 1); 
        for(int i = 0; i < M; i++)
        {
            int u; 
            cin >> u;
            --u; 
            swap(arr[u], arr[u + 1]); 
        }
        for(int i = 0; i < N; i++)
        {
            cout << arr[i] << '\n'; 
        }
    }
    return 0;
}