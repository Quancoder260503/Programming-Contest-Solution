#include "bits/stdc++.h"
using namespace std;
const int INF = 1e9;
signed main(void)
{
    int K;
    while (cin >> K)
    {
        vector<int> dyn(K, INF);
        dyn[1] = 1;
        deque<int> q;
        q.push_front(1);
        while (q.size())
        {
            int u = q.front();
            q.pop_front();
            int nxt = u * 10 % K;
            if (dyn[nxt] > dyn[u])
            {
                dyn[nxt] = dyn[u];
                q.push_front(nxt);
            }
            nxt = (u + 1) % K;
            if (dyn[nxt] > dyn[u] + 1)
            {
                dyn[nxt] = dyn[u] + 1;
                q.push_back(nxt);
            }
        }
        cout << dyn[0] << '\n'; 
    }
    return 0;
}