//boruvka spanning tree
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4e5 + 1;
int n,m;
vector<pair<int,int>>adj[N + 1]; 
int fa[N + 1]; 
bool vis[N + 1]; 
int find(int u){
    if(u == fa[u]) return u;
    return fa[u] = find(fa[u]);
}
void dfs(int u){
      vis[u] = 1; 
      for(int i = 0; i < adj[u].size(); i++){
            if(vis[adj[u][i].first]) continue;
            dfs(adj[u][i].first); 
      }
}
int main(){
      scanf("%d%d",&n,&m); 
      for(int i = 1; i <= m; i++){
           int u,v,w; scanf("%d%d%d",&u,&v,&w); 
           adj[u].push_back({v,w});
           adj[v].push_back({u,w}); 
      }
      int components = n;
      long long ans = 0;
      int cnt = 0; 
      for(int i = 1; i <= n; i++){
           if(!vis[i]){
                dfs(i);
                cnt++;
             }
      }
      if(cnt == 1){
        for(int i = 1; i <= n; i++) fa[i] = i; 
        while(components > 1){
            multiset<pair<int,pair<int,int>>>edge; 
            for(int i = 1; i <= n; i++){
                 int u = i; 
                 int value,node;
                 for(int j = 0; j < adj[u].size(); j++){
                       auto v = adj[u][j];
                       if(find(u) == find(v.first)) continue; 
                       edge.insert({v.second,{u,v.first}});
                 }
            }
            for(auto it = edge.begin(); it != edge.end(); it++){
                  int u = find((*it).second.first);
                  int v = find((*it).second.second);
                  int w = (*it).first;
                  //cout<<edge[i].second.first<<' '<<edge[i].second.second<<' '<<w<<endl; 
                  if(u == v or w == INT_MAX) continue;
                  components--;
                  fa[v] = u; 
                  ans += w;
                  if(components == 1){
                        printf("%lld\n",ans);
                        return 0; 
                  }
              }
          }
      }
      printf("IMPOSSIBLE\n"); 
}