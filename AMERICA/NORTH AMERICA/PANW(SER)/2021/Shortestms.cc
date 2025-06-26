#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    string pattern;
    string target;
    cin >> pattern >> target;
    target = '.' + target; 
    vector<vector<int>> pos(target.length(), vector<int>(26, -1));
    int mask = 0;
    for (int i = 0; i < pattern.length(); i++)
    {
        mask = mask | (1 << (pattern[i] - 'a'));
    }
    int bmask = 0;
    int sz = 1;
    for (int i = 1; i < target.length(); i++)
    {
        bmask = bmask | (1 << (target[i] - 'a'));
        if (bmask == mask)
        {
            sz++;
            bmask = 0;
        }
        for (int j = i - 1; j >= 0; j--)
        {
            pos[j][target[i] - 'a'] = i;
            if (target[i] == target[j]) break;
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        string S;
        cin >> S;
        int at = 0;
        for (auto c : S)
        {
            at = pos[at][c - 'a'];
            if (at == -1) break;
        }
        bool res = (S.size() == sz && at == -1);
        cout << res << '\n';
    }
    return 0;
}