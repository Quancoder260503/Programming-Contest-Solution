#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N, T;
    cin >> T; 
    while(T--)
    {
        cin >> N; 
        vector<int32_t>arr(N); 
        int sum = 0; 
        for(int i = 0; i < N; i++) 
        {
            cin >> arr[i]; 
            sum += arr[i]; 
        }
        if(sum % 4 != 0)
        {
            cout << "no" << '\n'; 
            continue; 
        }
        int side = sum / 4; 
        function<int(int, int, int)>doit; 
        vector<int>vis(1 << N); 
        doit = [&](int at, int tot, int mask) -> int 
        {
            if(vis[mask])   return 0; 
            if(tot >  side) return 0; 
            if(tot == side) tot = 0;
            if(at == N && tot == 0) return 1;
            vis[mask] = 1;
            for(int i = 0; i < N; i++)
            {
                if(mask & (1 << i)) continue;
                if(doit(at + 1, tot + arr[i], mask | (1 << i)))
                {
                    return 1; 
                }
            }
            return 0; 
        };
        cout << (doit(0, 0, 0) ? "yes" : "no") << '\n'; 
    }
    return 0; 
}