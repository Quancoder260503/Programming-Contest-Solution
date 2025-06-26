#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10 
#define pii pair<int,int> 
#define mp make_pair
vector<int>adj[MAXN]; 
int n, k, ans;
int dfs(int u, int p)
{    
     vector<int>trs; 
     for(int i = 0; i < adj[u].size(); i++)
     {
          int v = adj[u][i]; 
          if(v == p) continue;
          trs.push_back(1 + dfs(v, u)); 
     }
     sort(trs.begin(), trs.end()); 
     while(trs.size() && trs.back() > k)
     {
         ans += 1; 
         trs.pop_back(); 
     }
     while(trs.size() > 1 && trs.back() + trs[trs.size() - 2] > k)
     {
         ans += 1; 
         trs.pop_back(); 
     }
     return trs.size() ? trs.back() : (int) trs.size(); 
}
signed main(void)
{
    cin >> n >> k ;
    for(int i = 0; i < n - 1; i++)
    {
         int u, v; 
         cin >> u >> v; 
         adj[u].push_back(v);
         adj[v].push_back(u); 
    }
    k = 2 * k; 
    ans = 1;
    dfs(1, 0); 
    cout << ans << '\n'; 
    return 0; 
}