#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 2e5 + 10
#define mp make_pair
int n; 
vector<int>arr[MAXN]; 
vector<int>adj[MAXN]; 
vector<int>value;
int fa[MAXN]; 
int find(int u)
{
     return u == fa[u] ? u : fa[u] = find(fa[u]); 
}
signed main(void)
{
    scanf("%d",&n);  
    for(int i = 1; i <= n; i++)
    {
         fa[i] = i;
    }
    for(int i = 1; i <= n; i++)
    {
         int sz; scanf("%d",&sz);
         for(int j = 0; j < sz; j++)
         {
             int x; scanf("%d",&x); 
             arr[i].push_back(x);    
             value.push_back(x); 
         }
    }
    sort(value.begin(),value.end()); 
    value.erase(unique(value.begin(),value.end()),value.end()); 
    for(int i = 1; i <= n; i++)
    {
        for(int j = 0; j < arr[i].size(); j++)
        {
             int pos = lower_bound(value.begin(),value.end(), arr[i][j]) - value.begin(); 
             adj[pos].push_back(i);
        }
    }
    vector<pair<pair<int,int>,int> > ans; 
    for(int i = 0; i < value.size(); i++)
    {
        int curr = lower_bound(value.begin(), value.end(), value[i]) - value.begin(); 
        for(int j = 0; j + 1 < (int) adj[curr].size(); j++)
        {
             int u = adj[curr][j];
             int v = adj[curr][j + 1]; 
             if(find(u) == find(v)) continue; 
             fa[find(u)] = find(v);
             ans.push_back(mp(mp(u,v), value[i])); 
        }
    }
    if((int) ans.size() != n - 1)
    {
         puts("impossible");
         return 0; 
    }
    for(int i = 0; i < (int) ans.size(); i++)
    {
         printf("%d %d %d\n",ans[i].first.first, ans[i].first.second, ans[i].second); 
    }
    return 0; 
}