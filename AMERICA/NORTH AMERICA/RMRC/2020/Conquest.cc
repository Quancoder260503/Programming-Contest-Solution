#include "bits/stdc++.h"
using namespace std;
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    while (cin >> N >> M)
    {
        vector<vector<int>>adj(N); 
        vector<int>W(N); 
        for(int i = 0; i < M; i++) 
        {
            int U, V;
            cin >> U >> V; 
            --U, --V; 
            adj[U].push_back(V); 
            adj[V].push_back(U); 
        }
        for(int i = 0; i < N; i++) cin >> W[i];
        using pii = pair<int, int>; 
        priority_queue<pii, vector<pii>, greater<pii>>pq;
        int src = 0; 
        vector<bool>vis(N, 0);
        vis[src] = 1;  
        int64_t ret = W[src];
        for(auto v : adj[src]) pq.push({W[v], v}); 
        while(pq.size())
        {
            auto [w, u] = pq.top();
            pq.pop();
            if(w < ret && !vis[u])
            {
                vis[u] = 1; 
                ret += w; 
                for(auto v : adj[u]) if(!vis[v])
                {
                    pq.push({W[v], v}); 
                }
            }

        }
        cout << ret << '\n'; 
    }
    return 0;
}