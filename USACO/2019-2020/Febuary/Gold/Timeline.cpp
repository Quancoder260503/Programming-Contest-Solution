#include "bits/stdc++.h"
using namespace std;
#define N 1000005
#define mp make_pair
vector<pair<int,int> >adj[N];
int n,m,c;
int A[N];    
long long ans[N]; 
int deg[N];
bool vis[N]; 
vector<int>topo; 
void dfs(int u){
     vis[u] = 1; 
     for(int i = 0; i < adj[u].size(); i++){
         int v = adj[u][i].first; 
         if(vis[v]) continue; 
         dfs(v); 
     }
     topo.push_back(u);
}
signed main(void){
     scanf("%d%d%d",&n,&m,&c);
     for(int i = 1; i <= n; i++){
          scanf("%d",&A[i]); 
     }
     for(int i = 0; i < c; i++){
         int u,v,w; 
         scanf("%d%d%d",&u,&v,&w);
         adj[u].push_back(mp(v,w)); 
     }
     for(int i = 1; i <= n; i++){
         if(!vis[i]) dfs(i);
     }
     reverse(topo.begin(),topo.end());
     for(int i = 0; i < topo.size(); i++){
           int u =  topo[i]; 
           for(int j = 0; j < adj[u].size(); j++){
               int v = adj[u][j].first; 
               int w = adj[u][j].second;
               A[v] = max(A[v], A[u] + w); 
           }
     }
     for(int i = 1; i <= n; i++){
         printf("%lld\n",A[i]); 
     }
}
