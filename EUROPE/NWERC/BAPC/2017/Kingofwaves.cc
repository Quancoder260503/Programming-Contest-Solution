#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<vector<char>>g(N, vector<char>(N)); 
        for(int i = 0; i < N; i++) for(int j = 0; j < N; j++)
        {
            cin >> g[i][j]; 
        }
        vector<vector<int>>adj(N); 
        for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) if(g[i][j] == '1')
        {
            adj[i].push_back(j); 
        }
        vector<bool>vis(N); 
        vector<int>topo; 
        function<void(int)>doit = [&](int u) -> void
        {
            vis[u] = 1;
            for(auto v : adj[u])
            {
                if(vis[v]) continue; 
                doit(v); 
            }
            topo.push_back(u); 
        }; 
        doit(0); 
        if(topo.size() == N)
        {
            for(int i = 0; i < topo.size(); i++) cout << topo[i] << " ";
        }
        else 
        {
            cout << "impossible" << '\n'; 
        }
    }
    return 0; 
}