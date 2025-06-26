#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        int ret = 0; 
        for(int i = 0; i < N; i++)
        {
            int x;
            cin >> x; 
            ret = ret xor x; 
        }
        cout << (ret ? "koosaga" : "cubelover") << '\n'; 
    }
    return 0; 
}