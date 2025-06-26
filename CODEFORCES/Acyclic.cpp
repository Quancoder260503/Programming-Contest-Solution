#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 3e5 + 10
#define mp make_pair
vector<int>adj[MAXN];  
#define vi vector<int>
char s[MAXN];
int arr[MAXN];
int trs[MAXN];  
int n;
int ans = 0;
int occ = 0;
int trie[MAXN][26]; 
int merge(int u, int v)
{
     int ch = s[v] - 'a'; 
     if(trie[u][ch])
     {
         int tot = 1; 
         for(int i = 0; i < 26; i++)
         {
             if(trie[v][i])
             {
                 tot += merge(trie[u][ch], trie[v][i]); 
             }
         }
         return tot;
     }
     else 
     {
         trie[u][ch] = v; 
         return 0; 
     }
}
void dfs(int u, int p)
{ 
    trs[u] = 1;
    for(int i = 0; i < adj[u].size(); i++)
    {
         int v = adj[u][i]; 
         if(v == p) continue;
         dfs(v, u); 
         trs[u] += trs[v];
         trs[u] -= merge(u, v); 
    }
    if(ans == trs[u] + arr[u])
    {
        occ += 1; 
    }
    else if(ans < trs[u] + arr[u])
    {
        ans = trs[u] + arr[u];
        occ = 1; 
    }
    return; 
}
signed main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
         scanf("%d", &arr[i]);
    }
    scanf(" %s", &s);  
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }
    memset(trs, 0, sizeof(trs)); 
    dfs(0, -1);
    printf("%d\n%d\n", ans, occ); 
}