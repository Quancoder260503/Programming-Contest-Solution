#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int tc;
    cin >> tc;
    for (int _ = 0; _ < tc; _++)
    {
        int N;
        cin >> N;
        map<vector<int>, int> mp;
        int nodes = 0;
        vector<vector<vector<int>>> g(N, vector<vector<int>>(2));
        for (int turn = 0; turn < 2; turn++)
        {
            for (int i = 0; i < N - 1; i++)
            {
                int U, V;
                cin >> U >> V;
                U--, V--;
                g[U][turn].push_back(V);
                g[V][turn].push_back(U);
            }
        }
        function<int(int, int, int)> doit = [&](int turn, int u, int p) -> int
        {
            vector<int> res;
            for (auto v : g[u][turn]) if (v != p)
            {
                res.push_back(doit(turn, v, u));
            }
            sort(res.begin(), res.end());
            if (mp.count(res) == 0) mp[res] = nodes++;
            return mp[res];
        };
        vector<int>fa(N), dist(N), ord(N);
        iota(ord.begin(), ord.end(), 0);  
        function<void(int, int, int)>dfs = [&](int turn, int u, int p) -> void
        {
            fa[u] = p; 
            for(auto v : g[u][turn])
            {
                if(v == p) continue;
                dist[v] = dist[u] + 1; 
                dfs(turn, v, u); 
            }
        }; 
        vector<vector<int>>root(2); 
        for(int turn = 0; turn < 2; turn++)
        {
            dfs(turn, 0, -1); 
            sort(ord.begin(), ord.end(), [&](int i, int j){ return dist[i] < dist[j]; }); 
            int c = ord.back(); 
            dist[c] = 0; 
            dfs(turn, c, -1);
            sort(ord.begin(), ord.end(), [&](int i, int j){ return dist[i] < dist[j]; });
            int cc = ord.back(); 
            vector<int>path; 
            while(cc != c)
            {
                path.push_back(cc); 
                cc = fa[cc]; 
            }
            path.push_back(cc); 
            int sz = path.size();
            root[turn].push_back(path[sz / 2]);
            if(sz % 2 == 0) root[turn].push_back(path[sz / 2 - 1]);
        }
        for(auto ra : root[0]) for(auto rb : root[1])
        {
            mp.clear(); 
            if(doit(0, ra, -1) == doit(1, rb, -1))
            {
                cout << "YES" << '\n'; 
                goto done; 
            }
        }
        cout << "NO" << "\n"; 
    done:; 
    }
    return 0;
}