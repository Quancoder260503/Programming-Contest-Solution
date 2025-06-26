#include "bits/stdc++.h"
using namespace std;
struct fenwick
{
    int N;
    vector<int> bit;
    void init(int _N)
    {
        N = _N;
        bit.resize(N);
    }
    int sum(int i)
    {
        int c = 0;
        for (++i; i > 0; i -= (i & -i))
        {
            c = c + bit[i];
        }
        return c;
    }
    int query(int L, int R)
    {
        if(L > R) return 0;
        return sum(R) - sum(L - 1); 
    }
    void upd(int i, int dif)
    {
        for (++i; i < N; i += (i & -i))
        {
            bit[i] = dif + bit[i];
        }
    }
};
// Let H[i] > H[k] < H[j] and i < k < j
// Then how many point inside (H[i], i)  
signed main(void)
{
    int n, T;
    while (cin >> T)
    {
        vector<int> ret;
        for (int prob = 0; prob < T; prob++)
        {
            cin >> n;
            vector<int> arr(n);
            vector<int>sortme; 
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
                sortme.push_back(arr[i]);  
            }
            sort(sortme.begin(), sortme.end()); 
            fenwick fenw; 
            fenw.init(n + 2); 
            int good = 0; 
            vector<int>suff(n + 1);
            for(int i = n - 1; i >= 0; i--)
            {
                suff[i] = max(suff[i + 1], arr[i]); 
            }
            for(int i = 0; i < n; i++)
            {
                int R = lower_bound(sortme.begin(), sortme.end(), suff[i + 1]) - sortme.begin() + 1;
                int L = lower_bound(sortme.begin(), sortme.end(), arr[i])      - sortme.begin() + 1;  
                good = good | (fenw.query(L, R) > 0);
                fenw.upd(L, 1);  
            }
            if(good) ret.push_back(prob + 1); 
        }
        cout << ret.size() << '\n'; 
        for(int i = 0; i < ret.size(); i++) cout << ret[i] << '\n'; 
        break; 
    }
    return 0;
}