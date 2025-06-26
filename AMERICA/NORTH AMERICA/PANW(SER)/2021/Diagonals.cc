#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int n;
    cin >> n;
    vector<vector<char>> g(n + 1, vector<char>(n + 1));
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            cin >> g[i][j];
        }
    }
    function<bool(int, int, int, int)> doit;
    vector<vector<bool>> vis(n + 1, vector<bool>(n + 1));
    vector<vector<char>> grid(n, vector<char>(n, '*'));
    doit = [&](int r, int c, int rt, int ct) -> bool
    {
        if (r == rt && c == ct) return true;
        if (vis[r][c]) return false;
        vis[r][c] = true;
        if (r < n && c < n && grid[r][c] == '\\'         && doit(r + 1, c + 1, rt, ct)) return true;
        if (0 < r && 0 < c && grid[r - 1][c - 1] == '\\' && doit(r - 1, c - 1, rt, ct)) return true;
        if (0 < r && c < n && grid[r - 1][c] == '/'      && doit(r - 1, c + 1, rt, ct)) return true;
        if (r < n && 0 < c && grid[r][c - 1] == '/'      && doit(r + 1, c - 1, rt, ct)) return true;
        return false;
    };
    auto path = [&](int r, int c, int rt, int ct)
    {
        for (int i = 0; i < n + 1; i++)
        {
            fill(vis[i].begin(), vis[i].end(), 0);
        }
        return doit(r, c, rt, ct);
    };
    auto addLine = [&](char p, char to, int &at, int &nxt)
    {
        if (p == to) at++;
        else if (p == '*') nxt++;
    };
    auto chk = [&](int r, int c)
    {
        if (g[r][c] == '+') return true;
        int curr = 0;
        int poss = 0;
        if (r < n && c < n) addLine(grid[r][c], '\\',         curr, poss);
        if (0 < r && 0 < c) addLine(grid[r - 1][c - 1], '\\', curr, poss);
        if (0 < r && c < n) addLine(grid[r - 1][c], '/',      curr, poss);
        if (r < n && 0 < c) addLine(grid[r][c - 1], '/',      curr, poss);
        return curr <= (g[r][c] - '0') && (g[r][c] - '0') <= curr + poss;
    };
    auto ok = [&](int r, int c, char s)
    {
        if (s == '\\' && path(r, c, r + 1, c + 1)) return false;
        if (s == '/'  && path(r, c + 1, r + 1, c)) return false;
        grid[r][c] = s;
        bool ret = (chk(r, c) && chk(r + 1, c + 1) && chk(r, c + 1) && chk(r + 1, c));
        grid[r][c] = '*';
        return ret;
    };
    function<bool(void)>tryit;
    auto put = [&](int r, int c, char s)
    {
        grid[r][c] = s;
        if (tryit()) return true;
        grid[r][c] = '*';
        return false;
    };
    tryit = [&](void) -> bool
    {
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                if(grid[r][c] == '*')
                {
                    bool at = ok(r, c, '\\');
                    bool bt = ok(r, c, '/');
                    if( at && !bt)  return put(r, c, '\\');
                    if(!at &&  bt)  return put(r, c, '/');
                    if(!at && !bt)  return false;
                }
            }
        }
        for(int r = 0; r < n; r++)
        {
            for(int c = 0; c < n; c++)
            {
                if(grid[r][c] == '*')
                {
                    if(put(r, c, '\\')) return true; 
                    if(put(r, c, '/'))  return true; 
                    return false; 
                }
            }
        }
        return true; 
    };
    tryit(); 
    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < n; c++)
        {
            cout << grid[r][c]; 
        }
        cout << '\n'; 
    }
    return 0;
}