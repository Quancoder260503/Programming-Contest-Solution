#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        /* 
        function<int(int64_t)>grundy; 
        map<int64_t, int>dyn; 
        grundy = [&](int64_t n) -> int
        {
            if(n <= 3) return 0; 
            if(dyn.count(n)) return dyn[n]; 
            int64_t R = floor(sqrt(n)); 
            int64_t L = ceil(sqrt(sqrt(n)));
            set<int>g; 
            for(int64_t i = L; i <= R; i++)
            {
                g.insert(grundy(i)); 
            }
            int mex = 0;
            while(g.count(mex)) mex++;
            return dyn[n] = mex;  
        };
        */ 
        vector<pair<int64_t, int>> magic_value = {{3, 0}, {15, 1}, {81, 2}, {6723, 0}, {50625, 3}, {2562991875LL, 1}, {INT64_MAX, 2}};
        int ret = 0; 
        for(int i = 0; i < N; i++)
        {
            int64_t x; 
            cin >> x; 
            pair<int64_t,int> val = {x, 0}; 
            auto at = lower_bound(magic_value.begin(), magic_value.end(), val) - magic_value.begin(); 
            ret = ret xor magic_value[at].second; 
        }
        cout << (ret ? "Furlo" : "Rublo") << '\n'; 
    }
    return 0; 
}