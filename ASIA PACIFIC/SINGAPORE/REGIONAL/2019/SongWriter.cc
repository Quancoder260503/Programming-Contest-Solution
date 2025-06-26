#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int n, l, r, k; 
    cin >> n >> l >> r >> k; 
    vector<int>marked(n - 1), a(n); 
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    for(int i = 0; i < n - 1; i++) { 
        marked[i] = (a[i] == a[i + 1] ? 0 : (a[i] < a[i + 1] ? 1 : -1));
    }
    vector<pair<int, int>>f(n); 
    f[n - 1] = {l, r}; 
    for(int i = n - 2; i >= 0; i--)
    {
        if(marked[i] == 0) f[i] = f[i + 1]; 
        else if(marked[i] == 1)
        {
            if(f[i + 1].second <= l) 
            {
                puts("-1");
                return 0; 
            }
            f[i].first  = max(l, f[i + 1].first - k);
            f[i].second = f[i + 1].second - 1;  
        }
        else 
        {
            if(f[i + 1].first >= r)
            {
                puts("-1"); 
                return 0; 
            }
            f[i].second = min(r, f[i + 1].second + k);
            f[i].first  = f[i + 1].first + 1; 
        }
    }
    int ret = f[0].first; 
    auto get_union = [&](pair<int, int>a, pair<int, int>b)
    {
        if(a.second < b.first || a.first > b.second) return make_pair(-1, -1);
        return make_pair(max(a.first, b.first), min(a.second, b.second)); 
    };
    cout << ret << " "; 
    for(int i = 0; i < n - 1; i++)
    {
        if(marked[i] == 1)
        {
            auto p = get_union(make_pair(ret + 1, ret + k), f[i + 1]); 
            ret = p.first;
        }
        else if(marked[i] == -1)
        {
            auto p = get_union(make_pair(ret - k, ret - 1), f[i + 1]); 
            ret = p.first; 
        }
        cout << ret << " "; 
    }
    cout << '\n'; 
    return 0;
}