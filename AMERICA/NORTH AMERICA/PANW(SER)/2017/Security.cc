#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int N, M, Q;
    int src, dst;
    while(cin >> N >> M >> Q)
    {
        cin >> src >> dst;
        --src, --dst;
        vector<vector<array<int, 3>>>g(N);
        vector<int>W; 
        for(int i = 0; i < M; i++)
        {
            int U, V, A, B;
            cin >> U >> V >> A >> B; 
            --U, --V; 
            g[U].push_back({V, A, B});
            W.push_back(A);
            W.push_back(B + 1);  
        }
        sort(W.begin(), W.end()); 
        W.erase(unique(W.begin(), W.end()), W.end()); 
        auto bfs = [&](int d)
        {
            vector<int>dist(N, -1); 
            dist[src] = 0; 
            queue<int>q;
            q.push(src); 
            while(q.size())
            {
                auto u = q.front();
                q.pop(); 
                for(auto [v, a, b] : g[u])
                {
                    if(a <= d && d <= b && dist[v] == -1)
                    {
                        dist[v] = dist[u] + 1; 
                        q.push(v); 
                    }
                }
            }
            return dist[dst] != -1; 
        }; 
        int ret = 0; 
        for(int i = 0; i + 1 < W.size(); i++)
        {
            if(bfs(W[i]))
            {
                ret += (W[i + 1] - W[i]); 
            }
        }
        cout << ret << '\n'; 
    }
    return 0; 
}