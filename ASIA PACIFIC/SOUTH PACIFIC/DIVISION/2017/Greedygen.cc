#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    vector<int>coins = {1, 2, 5, 10, 20, 50}; 
    vector<int>C(6); 
    for(int i = 0; i < 6; i++) cin >> C[i]; 
    vector<int>D(C.begin(), C.end()); 
    int N; 
    cin >> N;
    int ret = 0;
    auto chk = [&](vector<int>&val, int amt)
    {
        for (int i = 5; i >= 0; i--)
        {
            int oamt = amt; 
            int cnt  = 0; 
            while(coins[i] <= oamt){oamt -= coins[i], cnt++;};
            if(cnt > val[i]) return false; 
            while(val[i] && coins[i] <= amt){ amt = amt - coins[i]; val[i]--;}
        } 
        return true; 
    };
    for(int i = 0; i < N; i++)
    {
        int M; 
        cin >> M; 
        int tot = 0;
        int x;
        for(int j = 0; j < 6; j++)
        {
            cin >> x; 
            tot  += x * coins[j];  
            D[j] += x; 
        }
        int res  = 0; 
        int change = max(0, tot - M); 
        int ochange = change;
        vector<int>A(D.begin(), D.end()); 
        if(chk(D, change)) continue;
        D = A; 
        while(!chk(D, change)) {D = A; change++;};
        ret += change - ochange; 
        D = C;
    }
    cout << ret << '\n'; 
    return 0; 
}