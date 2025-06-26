#include "bits/stdc++.h"
using namespace std;
const int INF = 1e9;
struct node
{
    int tot, val;
    string ret;
    node(int _tot, int _val, string _ret) : tot(_tot), val(_val), ret(_ret){};
};
signed main(void)
{
    int s, d;
    while (cin >> d >> s)
    {
        auto doit = [&](void) -> string
        {
            int turn = 0;
            vector<vector<bool>> vis(s + 1, vector<bool>(d, 0));
            queue<node> q;
            q.push(node(0, 0, ""));
            vis[0][0] = 1;
            while (q.size())
            {
                auto u = q.front();
                q.pop();
                if (u.tot <= s)
                {
                    for (int digit = 0; digit < 10; digit++)
                    {
                        if (digit + u.tot <= s && !vis[u.tot + digit][(10 * u.val + digit) % d])
                        {
                            if (digit + u.tot == s && (10 * u.val + digit) % d == 0)
                                return u.ret + (char)(digit + '0');
                            vis[u.tot + digit][(10 * u.val + digit) % d] = 1;
                            q.push(node(u.tot + digit, (10 * u.val + digit) % d, u.ret + (char)(digit + '0')));
                        }
                    }
                }
            }
            return "-1";
        };
        cout << doit() << '\n';
    }
    return 0;
}