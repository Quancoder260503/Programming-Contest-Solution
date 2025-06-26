#include "bits/stdc++.h"

using namespace std; 

#define double long double

const int maxf = 2e5 + 2; 

vector<pair<int, double>>g[maxf]; 

int main(void)
{
    int N, M; 
    cin >> N >> M;
    cin.ignore();  
    map<string, int>mp;
    int ctr = 0; 
    for(int i = 0; i < N; i++)
    {
        string s1, s2, eq; 
        double x1, x2; 
        cin >> x1 >> s1 >> eq >> x2 >> s2; 
        if(mp.count(s1) == 0) mp[s1] = ctr++; 
        if(mp.count(s2) == 0) mp[s2] = ctr++; 
        int u = mp[s1], v = mp[s2]; 
        g[u].push_back({v, x2}); 
        g[v].push_back({u, 1.0 / x2}); 
    }
    vector<int>vis(ctr); 
    vector<double>dist(ctr); 
    function<void(int)>doit = [&](int u) -> void
    {
        vis[u] = 1; 
        for(auto [v, w] : g[u])
        {
            if(vis[v]) continue; 
            dist[v] = dist[u] * w; 
            doit(v); 
        }
        return; 
    }; 
    cout << fixed << setprecision(15); 
    for(int i = 0; i < M; i++)
    {
        fill(vis.begin(), vis.end(), 0);
        fill(dist.begin(), dist.end(), -1.0);
        string s1, s2, to;
        double x;
        cin >> x >> s1 >> to >> s2;
        int src = mp[s1], dst = mp[s2]; 
        dist[src] = x; 
        doit(src); 
        if(dist[dst] == -1.0) cout << "impossible" << '\n'; 
        else cout << dist[dst] << '\n'; 
    }
    return 0; 
}