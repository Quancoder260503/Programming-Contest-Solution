#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int R, C; 
    while(cin >> R >> C)
    {
        vector<vector<int>>g(R, vector<int>(C)); 
        vector<int>vis(R * C); 
        vector<tuple<int, int, int>>arr;
        for(int i = 0; i < R; i++) for(int j = 0; j < C; j++)
        {
            cin >> g[i][j]; 
            arr.push_back({g[i][j], i, j}); 
        }
        sort(arr.rbegin(), arr.rend()); 
        const int dx[4] = {1, -1, 0, 0}; 
        const int dy[4] = {0, 0, -1, 1}; 
        function<void(int, int)>doit = [&](int x, int y) -> void
        {
            if(vis[x * C + y]) return; 
            vis[x * C + y] = 1; 
            for(int k = 0; k < 4; k++) 
            {
                int px = x + dx[k], py = y + dy[k]; 
                if(0 <= px && px < R && 0 <= py && py < C && g[x][y] >= g[px][py]) doit(px, py); 
            }
            return; 
        }; 
        int ret = 0; 
        for(auto [p, x, y] : arr)
        {
            if(p <= 1) break;
            if(vis[x * C + y]) continue; 
            doit(x, y); 
            ret++; 
        }
        cout << ret << '\n'; 
    }
    return 0; 
}