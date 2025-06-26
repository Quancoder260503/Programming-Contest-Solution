#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    map<string,int>mp; 
    int n, q; 
    cin >> n >> q; 
    for(int i = 0; i < n; i++)
    {
        string s; cin >> s; 
        mp[s] = i; 
    }
    for(int i = 0; i < q; i++)
    {
         string u, v; cin >> u >> v; 
         cout << abs(mp[u] - mp[v]) - 1 << '\n'; 
    }
    return 0;
}