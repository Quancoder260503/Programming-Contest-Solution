#include "bits/stdc++.h"

using namespace std;

int64_t llabs(int64_t x) {return x < 0 ? -x : x; }

int main(void)
{
    int n;
    cin >> n;
    vector<int64_t> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        a[i] = a[i] - (i + 1);
    }
    set<pair<int64_t, int64_t>> s;
    s.insert({a[0], 1});
    for (int i = 1; i < n; i++)
    {
        auto it = s.lower_bound({a[i], (i + 1)});
        pair<int64_t, int64_t> ret = {LLONG_MAX, LLONG_MAX};
        if (it != s.end())
        {
            ret.first = llabs((*it).first - a[i]); 
            auto tmp = it; 
            while(it != s.end() && llabs(a[i] - (*it).first) == ret.first) {
                ret.second = min(ret.second, -(*it).second); 
                it++; 
            }
            it = tmp; 
        }
        if (it != s.begin())
        {
            --it;
            if(ret.first > llabs(a[i] - (*it).first)) {
                ret.second = LLONG_MAX; 
                ret.first = llabs(a[i] - (*it).first); 
            }
            while(it != s.begin() && llabs(a[i] - (*it).first) == ret.first){
                ret.second = min(ret.second, -(*it).second);
                it--;  
            }
            if(llabs(a[i] - (*it).first) == ret.first){
                ret.second = min(ret.second, -(*it).second);
            }
        }
        cout << -ret.second << ' '; 
        s.insert({a[i], (i + 1)});
    }
    return 0;
}