#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N;
    while(cin >> N)
    { 
        vector<int64_t>G(N);
        int64_t sum = 0; 
        for(int i = 0; i < N; i++) {cin >> G[i]; sum += G[i];}
        sum = sum / N;  
        auto solve = [&](void)
        {
            vector<pair<int64_t, int64_t>>dyn(2 * N); 
            dyn[0] = {G[0] - sum, G[0] - sum}; 
            deque<pair<int, int64_t>>dq;
            dq.push_back({0, G[0] - sum});
            int64_t ret = INT64_MAX; 
            for(int i = 1; i < 2 * N; i++) 
            {
                dyn[i].first  = dyn[i - 1].first + G[i % N] - sum;
                dyn[i].second = dyn[i - 1].second + dyn[i].first; 
                while(dq.size() && dq.back().second >= dyn[i].first) dq.pop_back(); 
                dq.push_back({i, dyn[i].first}); 
                if(dq.front().first <= i - N) dq.pop_front(); 
                if(i >= N)
                {
                    if(dq.front().second < dyn[i - N].first) continue; 
                    ret = min(ret, dyn[i].second - dyn[i - N].second - dq.front().second * N); 
                }
            }
            return ret; 
        };  
        int64_t res = solve(); 
        reverse(G.begin(), G.end());
        res = min(res, solve()); 
        cout << res << '\n'; 
    }
    return 0; 
}