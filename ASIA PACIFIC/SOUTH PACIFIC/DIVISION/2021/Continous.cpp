#include "bits/stdc++.h"
using namespace std;
int n, k;
signed main(void)
{
    int n, k;
    cin >> n >> k;
    vector<pair<char, int>> ch;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < min(k, (int)s.length()); j++)
        {
            ch.push_back({s[j], i});
        }
    }
    sort(ch.begin(), ch.end());
    int N = ch.size();
    pair<int, int> ans = {0, 0};
    for (int i = 0; i < N; i++)
    {
        int j = i;
        vector<int> lst;
        vector<int> opt(102, 0);
        while (ch[i].first == ch[j].first && j < N)
        {
            lst.push_back(ch[j].second);
            j++;
        }
        opt[lst[0]] = 1;
        for (int at = 1; at < lst.size(); at++)
        {
            opt[lst[at]] = 1 + opt[lst[at] - 1];
        }
        int curr = 0;
        for (int j = 0; j < lst.size(); j++)
        {
            curr = max(curr, opt[lst[j]]);
        }
        if(curr > ans.first)
        {
            ans.first = curr;
            ans.second = 1;  
        }
        else if(curr == ans.first)
        {
            ans.second++;
        }
        i = j - 1;
    }
    cout << ans.first << " " << ans.second << '\n';
    return 0;
}