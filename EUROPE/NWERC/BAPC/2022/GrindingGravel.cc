#include "bits/stdc++.h"

using namespace std; 

const int maxf = 2e5 + 10; 
const int INF = 1e9; 

int ctr[maxf]; 

int main(void)
{
    int N, K; 
    while(cin >> N >> K) 
    {
        vector<int>a(N); 
        for(int i = 0; i < N; i++)
        {
            cin >> a[i]; 
            ctr[a[i] % K]++; 
        }
        int64_t sum = accumulate(a.begin(), a.end(), 0LL);
        sum = sum / K; 
        int64_t g = 0; 
        for(int i = 1; 2 * i < K; i++)
        {
            int c = min(ctr[i], ctr[K - i]); 
            g += c; 
            ctr[i]     -= c; 
            ctr[K - i] -= c; 
        }
        if(K % 2 == 0)
        {
            g += (ctr[K / 2] / 2); 
            ctr[K / 2] = ctr[K / 2] & 1;
        } 
        map<int, int>state; 
        for(int i = 0; i < K; i++) if(ctr[i]) state[i] = ctr[i]; 
        map<map<int, int>, int>dyn; 
        function<int(map<int, int>)>doit = [&](map<int, int>curr) -> int
        {
            if(dyn.count(curr)) return dyn[curr]; 
            int tot = 0, ret = 0; 
            for(auto p : curr)
            {
                tot += p.first * p.second; 
            }
            int rem = tot % K; 
            map<int, int>n_curr = curr; 
            for(auto p : curr)
            {
                n_curr[p.first]--; 
                if(n_curr[p.first] == 0) n_curr.erase(p.first); 
                ret = max(ret, doit(n_curr) + (rem == p.first)); 
                n_curr[p.first]++;   
            } 
            return dyn[curr] = ret;  
        };  
        cout << sum - g - doit(state) << '\n'; 
    }
    return 0; 
}