#include "bits/stdc++.h"

using namespace std; 

const int maxf = 750; 

int64_t dist[maxf][maxf]; 
int64_t state[maxf]; 

int main(void)
{
    int n, m, t, d; 
    cin >> n >> m >> t >> d;
    for(int i = 1; i <= t; i++) cin >> state[i]; 
    for(int i = 0; i < maxf; i++) for(int j = 0; j < maxf; j++)
    {
        dist[i][j] = INT64_MAX; 
    } 
    for(int i = 0; i < m; i++)
    {
        int u, v;
        int64_t w;  
        cin >> u >> v >> w;
        dist[v][u] = min(dist[v][u], w);  
        dist[u][v] = min(dist[u][v], w); 
    }
    for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
    {
        if(dist[i][k] == INT64_MAX || dist[k][j] == INT64_MAX) continue; 
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    }
    state[0] = 1; 
    state[t + 1] = n;
    t += 2;  
    for(int i = 0; i < t; i++) for(int j = 0; j < t; j++)
    {
        //cout << state[i] << " " << state[j] << " " << dist[state[i]][state[j]] << '\n'; 
        if(dist[state[i]][state[j]] > d) dist[state[i]][state[j]] = INT64_MAX; 
    }
    for(int k = 0; k < t; k++) for(int i = 0; i < t; i++) for(int j = 0; j < t; j++)
    {
        if(dist[state[i]][state[k]] == INT64_MAX || dist[state[k]][state[j]] == INT64_MAX) continue; 
        dist[state[i]][state[j]] = min(dist[state[i]][state[j]], dist[state[i]][state[k]] + dist[state[k]][state[j]]); 
    }
    if(dist[1][n] == INT64_MAX) cout << "stuck\n"; 
    else cout << dist[1][n] << '\n'; 
    return 0; 
}