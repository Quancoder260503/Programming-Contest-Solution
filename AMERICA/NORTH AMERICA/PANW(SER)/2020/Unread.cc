#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int n, m; 
    while(cin >> n >> m)
    {
        map<int, int> lst; 
        long long ret = 0; 
        for(int i = 0; i < m; i++)
        {
            int x; 
            cin >> x; 
            ret += i + 1 - lst[x]; 
            lst[x] = i + 1; 
            cout << 1LL * n * (i + 1) - ret << '\n'; 
        }
    }
    return 0; 
}