#include "bits/stdc++.h"
using namespace std;
const int N = 2e5 + 10;
const int INF = 1e7;
signed main(void)
{
    int n, L, R;
    cin >> n >> L >> R;
    vector<int> pf(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        int c;
        cin >> c;
        pf[i] = pf[i - 1] + c;
    }
    auto get = [&](int L, int R)
    {
        return pf[R] - pf[L - 1]; 
    }; 
    int maxx, minn; 
    maxx = -INF; 
    minn = INF;
    for(int dist = L; dist <= R; dist++)
    {
        for(int i = 1; i <= dist; i++)
        {
            int cc = (pf[i] > 0); 
            for(int j = i; j <= n; j += dist)
            {
                cc += (get(j + 1, min(j + dist, n)) > 0); 
            }
            maxx = max(maxx, cc); 
            minn = min(minn, cc); 
        }
    }
    cout << minn << " " << maxx << '\n'; 
    return 0;
}
// use segment tree :))
