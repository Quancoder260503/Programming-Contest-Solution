#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)1e6 + 10;
string s[MAXN];
int n, L;
signed main(void)
{
    cin >> n >> L;
    int len = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        len += s[i].length();
    }
    if (len > L)
    {
        puts("No");
    }
    else
    {
        L = L - len;
        if (L == 0)
        {
            puts(n == 1 ? "Yes" : "No");
            return 0;
        }
        else
        {
            if (n == 1)
            {
                puts("No");
            }
            else
            {
                puts(L % (n - 1) == 0 ? "Yes" : "No");
            }
        }
    }
    return 0;
}