#include "bits/stdc++.h"

using namespace std; 
const int maxf = 1e6 + 2; 

int deg[maxf], to[maxf];
vector<int>g[maxf]; 

int main(void)
{
    int N, M; 
    while(cin >> N >> M)
    {
        vector<pair<int, int>>edge;
        for(int i = 0; i < M; i++)
        {
            int U, V; 
            cin >> U >> V;
            deg[U]++; deg[V]++; 
            edge.push_back({U, V}); 
        }
        int64_t ret = 0; 
        for(auto [U, V] : edge)
        {
            ret += 1LL * (deg[U] - 1) * (deg[U] - 2) * (deg[U] - 3) * (deg[V] - 1) / 6;
            ret += 1LL * (deg[V] - 1) * (deg[V] - 2) * (deg[V] - 3) * (deg[U] - 1) / 6;
            if(deg[U] < deg[V] || (deg[U] == deg[V] && U < V))
            {
                g[U].push_back(V); 
            }
            else 
            {
                g[V].push_back(U); 
            }
        }
        for(int i = 1; i <= N; i++)
        {
            for(auto j: g[i]) 
            {
                to[j] = i; 
            }
            for(auto j : g[i]) for(auto k : g[j]) if(to[k] == i)
            {
                ret = ret - (deg[i] - 2) * (deg[i] - 3);
                ret = ret - (deg[j] - 2) * (deg[j] - 3);
                ret = ret - (deg[k] - 2) * (deg[k] - 3);
            }
        }
        cout << ret << '\n'; 
    }
    return 0; 
}