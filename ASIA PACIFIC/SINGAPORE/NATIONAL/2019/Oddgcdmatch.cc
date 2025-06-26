#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        int odd, even;
        odd = even = 0; 
        for(int i = 0; i < N; i++)
        {
            int x; 
            cin >> x;
            odd  += (x & 1); 
            even += (x & 1) xor 1; 
        }
        int ret = min(odd, even) + (odd > even ? (odd - even) / 2 : 0); 
        cout << ret << '\n'; 
    }
    return 0; 
}