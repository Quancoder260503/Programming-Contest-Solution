#include "bits/stdc++.h"
using namespace std;
#define lint long long
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
    void upd(int i, int dif)
    {
        for (++i; i < N; i += (i & -i))
        {
            bit[i] = dif + bit[i];
        }
    }
};
signed main(void)
{
    int n;
    while(cin >> n)
    {
        vector<int>arr(n); 
        vector<pair<int, int>>coord;
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
            coord.push_back({arr[i], i + 1});  
        }
        sort(coord.rbegin(), coord.rend());
        lint ret = 0;
        fenwick fenw; 
        fenw.init(n + 2); 
        for(int i = 0; i < n; i++)
        {
            auto [_, at] = coord[i]; 
            ret += min(fenw.sum(at), i - fenw.sum(at));
            fenw.upd(at, 1); 
        }
        cout << ret << '\n'; 
    }
    return 0;
}