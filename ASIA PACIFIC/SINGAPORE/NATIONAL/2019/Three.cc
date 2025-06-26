#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>a(N), b(N); 
        for(int i = 0; i < N; i++) cin >> a[i]; 
        for(int i = 0; i < N; i++) cin >> b[i]; 
        int ret = 0; 
        for(int i = 0; i < N; i++)
        {
            if(a[i] < b[i]) continue; 
            ret += (a[i] > b[i] ? 3 : 1); 
        }
        cout << ret << '\n'; 
    }
    return 0; 
}