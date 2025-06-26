#include "bits/stdc++.h"

using namespace std;
const int maxf = 2e5 + 10;

map<int, vector<int>>g[maxf]; 
int vis[maxf], from[maxf]; 

void doit(int src, int to)
{
    if(vis[to]) return; 
    if(from[to] == 0)
    {
        from[to] = src; 
        for(auto adj : g[to])
        {
            for(auto v : adj.second) if(v != src) doit(to, v); 
        }
    }
    else if(from[to] != src)
    {
        vis[to] = 1; 
        doit(to, from[to]); 
    }
}

int main(void)
{
    int N;
    while (cin >> N)
    {
        for (int i = 0; i < N - 1; i++)
        {
            int U, V, C;
            cin >> U >> V >> C;
            g[U][C].push_back(V);
            g[V][C].push_back(U);
        }
        memset(vis, 0, sizeof(vis)); 
        for(int i = 1; i <= N; i++) if(!vis[i])
        {
            for (auto adj : g[i]) if (adj.second.size() > 1)
            {
                for (auto v : adj.second) doit(i, v);
            }
        }
        int ctr = 0; 
        for(int i = 1; i <= N; i++) ctr += (!from[i]);
        cout << ctr << '\n'; 
        for(int i = 1; i <= N; i++) if(!from[i]) cout << i << '\n'; 
    }
    return 0;
}
