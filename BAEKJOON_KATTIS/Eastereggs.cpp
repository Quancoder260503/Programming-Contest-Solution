#include "bits/stdc++.h"
#include "grader.h"
using namespace std; 
#define MAXN (int) 1e6 + 5 
#define mp make_pair
#define pii pair<int,int>
vector<int> order; 
vector<int>adj[MAXN]; 
void dfs(int u, int p)
{
     order.push_back(u); 
     for(int i = 0; i < (int) adj[u].size(); i++)
     {
         int v = adj[u][i];
         if(v == p) continue; 
         dfs(v,u); 
     }
}
int findEgg(int n, vector<pii> bridges)
{
     for(int i = 1; i <= n; i++) adj[i].clear(); 
     order.clear(); 
     for(int i = 0; i < (int) bridges.size(); i++)
     {
         int u = bridges[i].first; 
         int v = bridges[i].second;
         adj[u].push_back(v);
         adj[v].push_back(u); 
     }
     dfs(1, 0); 
     int l = 0; 
     int r = n - 1; 
     while(l < r)
     {
         int mid = (l + r + 1) / 2;
         if(query(vector<int>(order.begin(), order.begin() + mid))) r = mid - 1; 
         else l = mid; 
     }
     return order[l]; 
}
signed main(void)
{
    return 0; 
}