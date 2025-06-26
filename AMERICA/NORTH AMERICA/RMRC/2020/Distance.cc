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
            c = c + bit[i];
        }
        return c;
    }
    int64_t query(int L, int R)
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
int main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>sx, sy;
        vector<int>rx(N), ry(N); 
        for(int i = 0; i < N; i++) 
        { 
            cin >> rx[i] >> ry[i]; 
            sx.push_back(rx[i]); 
            sy.push_back(ry[i]); 
        } 
        sort(sx.begin(), sx.end());
        sort(sy.begin(), sy.end()); 
        sx.erase(unique(sx.begin(), sx.end()), sx.end());
        sy.erase(unique(sy.begin(), sy.end()), sy.end()); 
        fenwick fenx, feny, xfen, yfen;
        fenx.init(N + 2);
        feny.init(N + 2); 
        xfen.init(N + 2);
        yfen.init(N + 2);   
        for(int i = 0; i < N; i++)
        {
            int posx = lower_bound(sx.begin(), sx.end(), rx[i]) - sx.begin() + 1; 
            int posy = lower_bound(sy.begin(), sy.end(), ry[i]) - sy.begin() + 1; 
            fenx.upd(posx, rx[i]); 
            feny.upd(posy, ry[i]); 
            xfen.upd(posx, 1); 
            yfen.upd(posy, 1); 
        }
        int64_t ret = 0;
        for(int i = 0; i < N; i++)
        {
            int posx = lower_bound(sx.begin(), sx.end(), rx[i]) - sx.begin();
            int posy = lower_bound(sy.begin(), sy.end(), ry[i]) - sy.begin();
            ret += 1LL * xfen.sum(posx) * rx[i] - fenx.sum(posx);
            ret += fenx.query(posx + 1, N) - 1LL * xfen.query(posx + 1, N) * rx[i];
            ret += 1LL * yfen.sum(posy) * ry[i] - feny.sum(posy);
            ret += feny.query(posy + 1, N) - 1LL * yfen.query(posy + 1, N) * ry[i];
        }
        ret = ret / 2; 
        cout << ret << '\n'; 
    }
    return 0;
}