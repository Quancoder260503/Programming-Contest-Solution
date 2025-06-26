#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)1e5 + 10;
const int K = 23;
signed main(void)
{
    int t;
    cin >> t;
    while (t--)
    {
        string s;
        cin >> s;
        int N = s.length();
        int at;
        string ans;
        for (at = 0; at < N; at++)
        {
            ans += s[at];
            if (at + 1 < N && s[at] > s[at + 1])
            {
                break;
            }
        }
        bool change = 0;
        for (int i = at + 1; i < N; i++)
        {
            if(ans[i - 1] >= s[i])
            {
               if(!change) ans += s[i]; 
               else ans += ans[i - 1]; 
            }
            else 
            {
                ans += (ans[i - 1] == '0' ? '0' : ans[i - 1]);
                change = 1; 
            }
        }
        cout << ans << '\n';
    }
    return 0;
}