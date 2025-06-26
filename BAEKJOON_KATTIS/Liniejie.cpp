#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e6 + 10
#define x first 
#define y second
#define pii pair<int,int>
#define mp make_pair
int n; 
pair<int,int>arr[MAXN]; 
vector<int>adj[MAXN]; 
bool vis[MAXN]; 
int match[MAXN]; 
bool dfs(int u)
{
    if(vis[u]) return false;
    vis[u] = true;  
    for(int i = 0; i < adj[u].size(); i++)
    {
         int v = adj[u][i]; 
         if(!match[v] || dfs(match[v]))
         {
            match[v] = u; 
            return true; 
         }
    } 
    return false; 
}
signed main(void)
{     
    scanf("%d", &n);
    vector<int>dx, dy; 
    for(int i = 1; i <= n; i++)
    {
       scanf("%d %d", &arr[i].x, &arr[i].y);
       dx.push_back(arr[i].x);
       dy.push_back(arr[i].y);  
    }      
    sort(dx.begin(), dx.end());
    sort(dy.begin(), dy.end()); 
    dx.erase(unique(dx.begin(), dx.end()), dx.end());
    dy.erase(unique(dy.begin(), dy.end()), dy.end());
    for(int i = 1; i <= n; i++)
    {
         arr[i].x = lower_bound(dx.begin(), dx.end(), arr[i].x) - dx.begin() + 1; 
         arr[i].y = lower_bound(dy.begin(), dy.end(), arr[i].y) - dy.begin() + 1; 
         adj[arr[i].x].push_back(arr[i].y);  
    }
    for(int i = 1; i <= dx.size(); i++)
    {
        fill(vis + 1, vis + n + 1, false); 
        dfs(i); 
    }
    vector<pii>matches;
    for(int i = 1; i <= dy.size(); i++)
    {
        if (match[i] == 0)
            continue;
        matches.push_back(mp(i, match[i])); 
    }
    if(matches.size() == dx.size() && dy.size() == dx.size())
    {
        printf("Slavko\n");
    }
    else 
    {
        printf("Mirko\n"); 
    }
    return 0;
}