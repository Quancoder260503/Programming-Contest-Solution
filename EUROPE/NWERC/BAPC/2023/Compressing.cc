#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6; 

map<string, int>g[maxf];
int n, nodes;
int depth[maxf], cost[maxf]; 

void dfs(int u)
{
    for(auto &[str, v] : g[u])
    {
        depth[v] = depth[u] + 1; 
        dfs(v); 
        cost[u] += cost[v];
    }
    return; 
}

int dfs2(int u, int ccost)
{
    int ret = ccost;
    for(auto &[str, v] : g[u])
    {
        int acost = ccost + n - 2 * cost[v];
        if(acost < ccost && g[v].size()) ret = min(ret, dfs2(v, acost)); 
    } 
    return ret; 
}

int main(void) {
    cin >> n; 
    nodes = 1; 
    for(int i = 0; i < n; i++)
    {
        string word;
        cin >> word; 
        int cc = 0; 
        for(int j = 1, k = 1; j < word.size(); j = k + 1, k++)
        {
            string cword; 
            while(k < word.size() && word[k] != '/') k++; 
            cword = word.substr(j, k - j); 
            if(g[cc].count(cword) == 0) g[cc][cword] = nodes++;
            cc = g[cc][cword];  
        }
        cost[cc] += 1; 
    }
    dfs(0); 
    int cc = 0; 
    for(int i = 0; i < nodes; i++) if(g[i].empty()) 
    {
        cc += depth[i] * cost[i]; 
    }
    cout << dfs2(0, cc) << '\n'; 
    return 0;
}