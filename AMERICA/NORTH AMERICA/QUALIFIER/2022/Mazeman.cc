#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N, M; 
    while(cin >> N >> M)
    {
        vector<string>G(N); 
        vector<pair<int, int>>st; 
        vector<pair<int, int>>dot; 
        string temp;
        getline(cin, temp); 
        for(int i = 0; i < N; i++)
        {
            getline(cin, G[i]); 
            for(int j = 0; j < M; j++)
            {
                if(G[i][j] == 'X') continue; 
                if(65 <= G[i][j] && G[i][j] <= 90) st.push_back({i, j});
                if(G[i][j] == '.') dot.push_back({i, j});
            }
        }
        auto chk = [&](int i, int j)
        {
            return (0 <= i && i < N && 0 <= j && j < M && (G[i][j] == ' ' || G[i][j] == '.')); 
        }; 
        auto to = [&](int i, int j) { return i * M + j;};
        function<int(int)>find; 
        vector<int>fa(N * M); 
        iota(fa.begin(), fa.end(), 0); 
        find = [&](int u) -> int
        {
            return (u == fa[u] ? u : fa[u] = find(fa[u])); 
        }; 
        auto join = [&](int u, int v)
        {
            u = find(u), v = find(v); 
            if(u == v) return 0; 
            if(65 <= G[v / M][v % M] && G[v / M][v % M] <= 90) fa[u] = v; 
            else fa[v] = u; 
            return 1; 
        }; 
        vector<int>vis(N * M); 
        const int dx[4] = {1, -1, 0, 0};
        const int dy[4] = {0, 0, -1, 1}; 
        auto doit = [&](int sx, int sy)
        {
            queue<pair<int, int>>q; 
            q.push({sx, sy}); 
            int ctr = 0; 
            while(q.size())
            {
                auto [u, v] = q.front();
                q.pop();
                for(int dir = 0; dir < 4; dir++)
                {
                    int px = u + dx[dir]; 
                    int py = v + dy[dir];  
                    if(chk(px, py) && !vis[to(px, py)])
                    {
                        join(to(px, py), to(u, v)); 
                        vis[to(px, py)] = 1; 
                        q.push({px, py}); 
                        ctr += (G[px][py] == '.');
                    }
                }
            }
            return (ctr > 0); 
        };
        int ret = 0; 
        auto cmp = [&](pair<int, int>&a, pair<int, int>&b)
        {
            return G[a.first][a.second] < G[b.first][b.second]; 
        }; 
        sort(st.begin(), st.end(), cmp); 
        for(auto [u, v] : st) ret += doit(u, v);
        int dots = (int) dot.size(); 
        for(auto [u, v] : dot) dots = dots - (find(to(u, v)) != to(u, v)); 
        cout << (dots == (int) dot.size() ? 0 : ret) << " " << dots << '\n'; 
    }
    return 0; 
}