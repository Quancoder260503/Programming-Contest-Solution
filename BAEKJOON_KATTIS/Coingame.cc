#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N, K, T;
    cin >> T;  
    while(cin >> N >> K)
    {
        if(K % 2 == 1)
        {
            cout << (N % 2) << '\n'; 
        }
        else 
        {
            int ret = N % (K + 1);
            if(ret == K)
            {
                cout << K << '\n'; 
            }
            else 
            {
                cout << ret % 2 << '\n'; 
            }
        }
    }
    return 0; 
}