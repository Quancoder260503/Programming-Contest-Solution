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
        bit.clear();
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
signed main(void)
{
    int n;
    while (cin >> n)
    {
        vector<pair<int, int>> coord;
        for (int i = 1; i <= n; i++)
        {
            int x;
            cin >> x; 
            coord.push_back({x, i});
        }
        sort(coord.rbegin(), coord.rend());
        auto doit = [&](void) -> lint
        {
            fenwick fenw;
            fenw.init(n + 2);
            lint ret = 0;
            for(int i = 0; i < coord.size(); i++)
            {
                auto [_, at] = coord[i]; 
                ret += min(fenw.sum(at), i - fenw.sum(at));
                fenw.upd(at, 1); 
            }
            return ret;
        };
        cout << doit() << '\n';
    }
    return 0;
}