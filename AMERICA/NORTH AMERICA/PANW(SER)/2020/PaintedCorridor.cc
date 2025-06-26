#include "bits/stdc++.h"
using namespace std;
const int MAX = 200; 
int N, M, R, B, Y;
int ev[MAX * MAX]; 
int vis[MAX][MAX][MAX]; 
vector<tuple<int, int, int>>adj[MAX]; 
void doit(int r, int y, int b, int c)
{
    if(c != -1) ev[c] = 1;
    if(vis[r][y][b]) return; 
    vis[r][y][b] = 1;  
    for(int cc : {r, y, b})
    {
        for(auto [to, col, e] : adj[cc])
        {
            if((col == 'R' || col == 'X') && (cc == r))  doit(to, y, b, e);
            if((col == 'Y' || col == 'X') && (cc == y))  doit(r, to, b, e);
            if((col == 'B' || col == 'X') && (cc == b))  doit(r, y, to, e);
            if(col == 'O' && (r == y && cc == r))        doit(to, to, b, e);
            if(col == 'G' && (y == b && cc == y))        doit(r, to, to, e); 
            if(col == 'P' && (r == b && cc == b))        doit(to, y, to, e); 
        }
    }
}
int main(void)
{
    while(cin >> N >> M >> R >> B >> Y)
    {
        vector<char>color(M); 
        for(int i = 0; i < M; i++)
        {
            int U, V; 
            char C; 
            cin >> U >> V >> C; 
            adj[U].push_back({V, C, (C == 'X' ? -1 : i)}); 
            adj[V].push_back({U, C, (C == 'X' ? -1 : i)}); 
            color[i] = C; 
        }
        doit(R, Y, B, -1); 
        int ret = 1; 
        for(int i = 0; i < M; i++) if(color[i] != 'X') ret = ret & ev[i]; 
        cout << ret << '\n'; 
    }
    return 0;
}