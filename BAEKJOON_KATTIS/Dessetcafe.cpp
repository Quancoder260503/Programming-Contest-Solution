#include "bits/stdc++.h"
using namespace std;
#define N 100005 
#define mp make_pair
vector<pair<int,int> >adj[N];
int n,k;  
long long P[N]; 
int key[N];
bool vis[N]; 
int timer = 1; 
int ans = 0;
/* Root the tree arbitialy */
/* Observation 1 : an apartment is a good node itself*/
/* Observation 2 : a node is good if there is at least one key node outside its
   the subtree and at least one key node in a subtree*/ 
/* Observation 3:  if the nodes has exactly k keys some paths then it's not a good node */
void dfs(int u, int p)
{
    for(int i = 0; i < adj[u].size(); i++)
    {
         int v = adj[u][i].first;
         if(v == p) continue; 
         dfs(v,u); 
         key[u] += key[v]; 
    }
}
void dfs2(int u,int p, bool flag)
{
     if(!key[u]) return;
     ans += 1; 
     for(int i = 0; i < adj[u].size(); i++)
     {
         int v = adj[u][i].first; 
         if(v == p) continue; 
         if(flag == true || vis[v]) dfs2(v,u,true);
         else{  
              dfs2(v,u,false); 
         }
         if(key[v] == k)
         {
            ans--;
         }
     }
}
signed main(void){
    scanf("%d%d",&n,&k); 
    for(int i = 0; i < n - 1; i++)
    {
         int u,v,w; scanf("%d%d%d",&u,&v,&w);
         adj[u].push_back(mp(v,w));
         adj[v].push_back(mp(u,w)); 
    }
    for(int i = 1; i <= k; i++)
    {
        scanf("%d",&P[i]); 
        vis[P[i]] = 1;
        key[P[i]] += 1;  
    }
    dfs(1,0);  
    dfs2(1,0,false); 
    printf("%d\n",ans); 
    return 0; 
}