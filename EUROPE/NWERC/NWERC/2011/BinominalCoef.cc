#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int tc; 
    cin >> tc;
    auto C = [&](int64_t n, int k, int64_t m, bool c)
    {
        int64_t ret = 1; 
        for(int i = 0; i < k; i++)
        {
            ret = 1LL * ret * (n - i) / (i + 1); 
            if(ret > m) return false; 
        }
        return c ? ret <= m : ret == m; 
    };
    auto C2 = [&](int64_t n, int64_t m, bool c)
    {
        int64_t ret = 1LL * n * (n - 1) / 2; 
        return c ? ret <= m : ret == m; 
    };
    auto chk = [&](int n, int64_t m)
    {
        int64_t l = 0; 
        int64_t r = m; 
        if(n != 2)
        {
            while (l < r)
            {
                int64_t mid = (l + r + 1) / 2;
                if (C(mid, n, m, true)) l = mid;
                else r = mid - 1;
            }
            return C(l, n, m, false) ? l : -1;
        }
        l = 0;
        r = 1e9;
        while (l < r)
        {
            int64_t mid = (l + r + 1) / 2;
            if (C2(mid, m, true)) l = mid;
            else  r = mid - 1;
        } 
        return C2(l, m, false) ? l : -1; 
    }; 
    for(int i = 0; i < tc; i++)
    {
        vector<pair<int64_t, int64_t>>ret;
        int64_t m; 
        cin >> m; 
        for(int n = 1; n < 100; n++)
        {
            if(2 * n > m) break; 
            int64_t k; 
            if((k = chk(n, m)) != -1)
            {
                ret.push_back({k, n}); 
                ret.push_back({k, k - n}); 
            }
        }
        sort(ret.begin(), ret.end()); 
        ret.erase(unique(ret.begin(), ret.end()), ret.end()); 
        cout << (int) ret.size() << '\n'; 
        for(auto v : ret) cout << "(" << v.first << "," << v.second << ") ";
        cout << '\n';  
    }
    return 0; 
}