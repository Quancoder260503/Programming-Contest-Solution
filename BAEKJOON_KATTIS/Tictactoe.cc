#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    function<void(char)>doit; 
    set<string>s; 
    string ret = ".........";
    vector<string>win = { "XXX......", "X...X...X", "X..X..X..", 
                          "..X..X..X", "......XXX", "..X.X.X..",
                          ".X..X..X.", "...XXX..."}; 
    doit = [&](char turn) -> void
    { 
        if(s.count(ret)) return; 
        s.insert(ret);
        int i, j;
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < 9; j++)
            {
                if(win[i][j] == 'X' && ret[j] != 'X') break; 
            }
            if(j == 9) return;
            for(j = 0; j < 9; j++)
            {
                if(win[i][j] == 'X' && ret[j] != 'O') break; 
            }
            if(j == 9) return;
        }
        for(int i = 0; i < 9; i++)
        {
            if(ret[i] == '.')
            {
                ret[i] = turn;
                doit(turn == 'X' ? 'O' : 'X');  
                ret[i] = '.'; 
            }
        }
    }; 
    doit('X'); 
    int tc; 
    cin >> tc; 
    while(tc--)
    {
        string res; 
        for(int i = 0; i < 3; i++)
        {
            string cur; 
            cin >> cur; 
            res += cur; 
        }
        cout << (s.count(res) ? "yes" : "no") << '\n'; 
    }
    return 0; 
}