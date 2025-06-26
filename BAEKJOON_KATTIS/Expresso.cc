#include "bits/stdc++.h"

using namespace std;

const int INF = 1e9; 

const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};

bool find(int j, vector<vector<int>> &g, vector<int> &btoa, vector<int> &vis)
{
    if (btoa[j] == -1) return 1;
    vis[j] = 1;
    int di = btoa[j];
    for (int e : g[di])
        if (!vis[e] && find(e, g, btoa, vis))
        {
            btoa[e] = di;
            return 1;
        }
    return 0;
}
int dfsMatching(vector<vector<int>> &g, vector<int> &btoa)
{
    vector<int> vis;
    for(int i = 0; i < g.size(); i++)
    {
        vis.assign(btoa.size(), 0);
        for (int j : g[i])
            if (find(j, g, btoa, vis))
            {
                btoa[j] = i;
                break;
            }
    }
    return btoa.size() - (int)count(btoa.begin(), btoa.end(), -1);
}

vector<int> min_cover(vector<vector<int>> &g, int n, int m)
{
    vector<int> match(m, -1);
    int res = dfsMatching(g, match);
    vector<bool> lfound(n, true), seen(m);
    for (int it : match)
        if (it != -1)
            lfound[it] = false;
    vector<int> q, cover;
    for(int i = 0; i < n; i++) if (lfound[i]) q.push_back(i);
    while (!q.empty())
    {
        int i = q.back();
        q.pop_back();
        lfound[i] = 1;
        for (int e : g[i])
            if (!seen[e] && match[e] != -1)
            {
                seen[e] = true;
                q.push_back(match[e]);
            }
    }
    for(int i = 0; i < n; i++) if (!lfound[i]) cover.push_back(i);
    for(int i = 0; i < m; i++) if (seen[i]) cover.push_back(n + i);
    return cover;
}

int main(void)
{
    int r, c; 
    while(cin >> r >> c)
    {
        vector<vector<char>>grid(r, vector<char>(c)); 
        vector<vector<int>>g(r * c); 
        vector<int>id(r * c); 
        int enode = 0;
        int onode = 0;  
        for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) 
        {
            cin >> grid[i][j];
            if(grid[i][j] == '#') continue; 
            id[i * c + j] = ((i + j) % 2 == 0 ? enode : onode)++;
        }
        auto chk = [&](int i, int j)
        {
            return (0 <= i && i < r && 0 <= j && j < c && grid[i][j] == '.'); 
        }; 
        auto to = [&](int i, int j){return id[i * c + j]; }; 
        int ctr = 0; 
        for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) 
        {
            if(grid[i][j] == '#') continue;  
            if((i + j) % 2 == 0)
            {
                ctr++; 
                int px, py; 
                for (int k = 0; k < 4; k++) if(chk(px = i + dx[k], py = j + dy[k]))
                {
                    g[to(i, j)].push_back(to(px, py)); 
                }
            }
        }
        vector<vector<char>>ret(r, vector<char>(c));
        ret = grid; 
        auto cover = min_cover(g, enode, onode); 
        for(int i = 0; i < r; i++) for(int j = 0; j < c; j++)
        {
            if(ret[i][j] == '#') continue; 
            if((i + j) % 2 == 0)
            {
                if(find(cover.begin(), cover.end(), to(i, j)) != cover.end()) continue; 
                ret[i][j] = 'E'; 
            }
            else 
            {
                if (find(cover.begin(), cover.end(), to(i, j) + enode) != cover.end()) continue;
                ret[i][j] = 'E';
            }
        } 
        for(int i = 0; i < r; i++)
        {
            for(int j = 0; j < c; j++) cout << ret[i][j]; 
            cout << '\n'; 
        }
    }
    return 0; 
}