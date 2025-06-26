#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int n;
    string s;
    while (cin >> n >> s)
    {
        for (int i = 1; i <= n; i++)
        {
            string at;
            for (int j = 1; j <= n; j++)
            {
                if (i == j) continue;
                at += to_string(j);
            }
            if (at == s)
            {
                cout << i << '\n';
                return 0;
            }
        }
    }
    return 0;
}
