#include "bits/stdc++.h"

using namespace std;

struct fenwick
{
    int N;
    vector<int64_t> bit;
    void init(int _N)
    {
        N = _N;
        bit.resize(N);
    }
    int64_t sum(int i)
    {
        int64_t c = 0;
        for (++i; i > 0; i -= (i & -i))
        {
            c = max(c, bit[i]);
        }
        return c;
    }
    void upd(int i, int64_t dif)
    {
        for (++i; i < N; i += (i & -i))
        {
            bit[i] = max(dif, bit[i]);
        }
    }
};

const int maxf = 1e6 + 2; 
int64_t dyn[maxf]; 

int main(void)
{
    int N;
    while(cin >> N)
    {
        vector<pair<int, int>>arr(N);
        vector<int>coord;  
        for(int i = 0; i < N; i++)
        {
            cin >> arr[i].first >> arr[i].second; 
            coord.push_back(arr[i].first); 
            coord.push_back(arr[i].second); 
        }
        sort(coord.begin(), coord.end());
        coord.erase(unique(coord.begin(), coord.end()), coord.end());
        fenwick fenw; 
        fenw.init(maxf);
        for(int i = 0; i < arr.size(); i++)
        {
            int u = lower_bound(coord.begin(), coord.end(), arr[i].first)  - coord.begin(); 
            int v = lower_bound(coord.begin(), coord.end(), arr[i].second) - coord.begin() + 1; 
            dyn[v] = max(dyn[v], fenw.sum(u) + arr[i].second - arr[i].first + 1);  
            fenw.upd(v, dyn[v]); 
        }
        cout << fenw.sum(maxf - 1) << '\n'; 
    }
    return 0;
}