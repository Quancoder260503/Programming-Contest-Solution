#include "bits/stdc++.h"
using namespace std;
int main(void)
{
    int N, M;
    const int dx[4] = {0, 0, -1, 1};
    const int dy[4] = {-1, 1, 0, 0};  
    while(cin >> N >> M)
    {
        vector<vector<char>>g(N, vector<char>(M)); 
        for(int i = 0; i < N; i++) for(int j = 0; j < M; j++)
        {
            cin >> g[i][j];
        }
        queue<pair<int, int>>q;
        vector<vector<int>>dyn(N, vector<int>(M, -1)); 
        for(int i = 0; i < N; i++) for(int j = 0; j < M; j++)
        {
            if(g[i][j] == '-') continue; 
            int chk = 0; 
            for(int dir = 0; dir < 4; dir++) 
            {
                int px = dx[dir] + i; 
                int py = dy[dir] + j; 
                if(0 <= px && px < N && 0 <= py && py < M)
                {
                    chk = chk | (g[px][py] == '-'); 
                }
            }
            if(chk || i == 0 || j == 0 || i == N - 1 || j == M - 1) 
            {
                q.push({i, j}); 
                dyn[i][j] = 0; 
            }
        }
        int ret = 1; 
        while(q.size())
        {
            auto [x, y] = q.front();
            q.pop(); 
            for(int dir = 0; dir < 4; dir++)
            {
                int px = dx[dir] + x;
                int py = dy[dir] + y;
                if (0 <= px && px < N && 0 <= py && py < M && g[px][py] == 'X' && dyn[px][py] == -1)
                {
                    dyn[px][py] = dyn[x][y] + 1; 
                    q.push({px, py}); 
                    ret = max(ret, dyn[px][py] + 1); 
                }
            }
        }
        cout << ret << '\n'; 
    }
    return 0;
}