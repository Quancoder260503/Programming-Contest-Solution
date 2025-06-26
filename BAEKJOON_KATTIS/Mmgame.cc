#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        int ret = 0; 
        int one = 0; 
        for(int i = 0; i < N; i++)
        {
            int x; 
            cin >> x; 
            ret = ret xor x; 
            one += (x == 1); 
        }
        if(one == N)
        {
            cout << (one % 2 == 0 ? "koosaga" : "cubelover") << '\n'; 
        }
        else 
        {
            cout << (ret ? "koosaga" : "cubelover") << '\n'; 
        }
    }
    return 0; 
}