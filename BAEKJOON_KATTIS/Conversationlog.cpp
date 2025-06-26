#include "bits/stdc++.h"
using namespace std;
map<string, set<string>> dict;
map<string, int> cnt_word2;
map<string, int> cnt_word;
bool cmp(const pair<int, string> &a, const pair<int, string> &b)
{
    return a.first == b.first ? a.second < b.second : a.first > b.first;
}
signed main(void)
{
    int n;
    cin >> n;
    string s;
    getline(cin, s);
    for (int i = 0; i < n; i++)
    {
        getline(cin, s);
        int at = 0;
        string name = "";
        while (at < s.length() && s[at] != ' ')
        {
            name += s[at];
            at++;
        }
        string acc = "";
        for (int j = at + 1; j < s.length(); j++)
        {
            if (s[j] == ' ')
            {
                dict[name].insert(acc);
                cnt_word2[acc]++;
                acc = "";
            }
            else
            {
                acc += s[j];
            }
        }
        cnt_word2[acc]++;
        dict[name].insert(acc);
    }
    int N = dict.size();
    for (auto [_, word_lst] : dict)
    {
        for (auto word : word_lst)
        {
            cnt_word[word]++;
        }
    }
    vector<pair<int, string>> ans;
    for (auto [word, cnt] : cnt_word)
    {
        if (cnt == N)
        {
            // cout << word << " " << cnt << '\n';
            ans.push_back({cnt_word2[word], word});
        }
    }
    sort(ans.begin(), ans.end(), cmp);
    if (ans.size() == 0)
    {
        puts("ALL CLEAR");
    }
    for (auto [cnt, word] : ans)
    {
        cout << word << '\n';
    }
    return 0;
}