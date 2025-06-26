#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int n, x, y; 
    cin >> n >> x >> y; 
    for(int i = 0; i < n; i++)
    {
        int p; cin >> p; 
        p = p * y / x; 
        cout << p << '\n'; 
    }
    return 0; 
}