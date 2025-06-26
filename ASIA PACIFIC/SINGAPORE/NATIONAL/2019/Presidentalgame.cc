#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N, K; 
    while(cin >> N >> K)
    {
        int ret = 0; 
        for(int i = 0; i < N; i++)
        {
            int x;
            cin >> x;
            ret = ret xor (x & 1); 
        }
        cout << (ret ? "John" : "Preston") << '\n'; 
    }
    return 0; 
}