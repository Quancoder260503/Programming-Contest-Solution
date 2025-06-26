#include "bits/stdc++.h"
using namespace std;
map<int, int> sq, cb, sqc;
int L, R;
signed main(void)
{
    cin >> L >> R;
    for (int i = 1; i * i <= R; i++)
    {
        if (L <= i * i)
        {
            sq[i * i]++;
        }
    }
    for (int i = 1; i * i * i <= R; i++)
    {
        if (L <= i * i * i)
        {
            cb[i * i * i]++;
        }
    }
    for (auto it : sq)
    {
        if (cb.count(it.first))
        {
            sqc[it.first]++;
        }
    }
    cout << sq.size() << " " << cb.size() << " " << sqc.size() << endl;
    return 0;
}