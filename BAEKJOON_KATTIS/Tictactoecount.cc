#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    map<string, pair<int, int>>dict; 
    string ret = ".........";
    vector<string> win = {"XXX......", "X...X...X", "X..X..X..",
                          "..X..X..X", "......XXX", "..X.X.X..",
                          ".X..X..X.", "...XXX..."};
    function<pair<int, int>(char)> doit;
    doit = [&](char turn) -> pair<int, int>
    {
        if(dict.count(ret)) return dict[ret]; 
        int i, j; 
        for(i = 0; i < 8; i++) 
        { 
            for(j = 0; j < 9; j++)
            {
                if(win[i][j] == 'X' && ret[j] != 'X') break; 
            }
            if(j == 9) return dict[ret] = {1, 0}; 
            for(j = 0; j < 9; j++)
            {
                if(win[i][j] == 'X' && ret[j] != 'O') break; 
            }
            if(j == 9) return dict[ret] = {0, 1}; 
        }
        for(int i = 0; i < 9; i++)
        {
            if(ret[i] == '.')
            {
                ret[i] = turn; 
                auto curr = doit(turn == 'X' ? 'O' : 'X'); 
                ret[i] = '.';
                dict[ret].first += curr.first;
                dict[ret].second += curr.second;
            }
        }
        return dict[ret]; 
    }; 
    doit('X'); 
    int tc;
    cin >> tc; 
    while(tc--)
    {
        string S;
        cin >> S;
        if(dict.count(S))
        {
            auto res = dict[S];
            cout << res.first << " " << res.second << '\n';
        }
        else 
        {
            cout << -1 << " " << -1 << '\n'; 
        }
    }
    return 0;
}