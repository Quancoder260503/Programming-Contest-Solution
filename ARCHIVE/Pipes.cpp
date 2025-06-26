#include "./stdc++.h"
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1e5 + 1;
long long n,m,dsz;
vector<int>adj[N + 1];
int a[N + 1],low[N + 1]; 
struct DSU{
    int fa[N + 1];
    void init(int n){
        for(int i = 1; i <= n; i++) fa[i] = i; 
    }
    int find(int u){
        if(u == fa[u]) return u;
        return fa[u] = find(fa[u]);
    }
    bool unite(int u,int v){
        u = find(u); v = find(v);
        if(u == v) return 0;
        fa[v] = u;
        return 1;
    } 
} dsu_cc, dsu_2ecc; 
void dfs(int u,int p){
    a[u] = low[u] = ++dsz;
    bool chk = 0;
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i]; 
        if(v != p or chk){
          if(!a[v]){
              dfs(v,u);
              low[u] = min(low[u] , low[v]);
            //if(low[v] > a[u]) printf("%d %d\n",u,v); 
             }
          else low[u] = min(a[v] , low[u]);
       } 
       else chk = 1; 
    }
    //cout<<low[u]<<' '<<a[u]<<' '<<u<<endl;
    if(low[u] == a[u] and p) printf("%d %d\n",u,p); 
}
int main(){
    scanf("%d%d",&n,&m); 
    dsu_cc.init(n); 
    dsu_2ecc.init(n);
    for(int i = 1; i <= m; i++){
         int a,b; scanf("%d%d",&a,&b); 
         if(dsu_cc.unite(a,b) or dsu_2ecc.unite(a,b)){
               adj[a].push_back(b); 
               adj[b].push_back(a);
         }
    }    
    printf("\n");
    for(int i = 1; i <= n; i++) if(!a[i]) dfs(i,0);
}