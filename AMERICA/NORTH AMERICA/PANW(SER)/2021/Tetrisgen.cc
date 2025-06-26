#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int T;
    string s;  
    cin >> T;
    while(T--)
    {
        cin >> s; 
        int N = s.length(); 
        int res = 0; 
        for(int i = 0; i < 7; i++)
        {
            int mask = 0; 
            int at = 0;
            for(at = 0; at < N; at++)
            {
                if(mask & (1 << (s[at] - 'A'))) break; 
                mask |= (1 << (s[at] - 'A'));
                if(at % 7 == i) mask = 0; 
            }
            if(at == N)
            {
                res = 1; 
            }
        }
        cout << res << '\n'; 
    } 
    return 0; 
}