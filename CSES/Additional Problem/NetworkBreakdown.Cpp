#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
long long n,k,p,m,q;
long long a[N + 1]; 
pair<int,int>edge[N + 1];
pair<int,int>query[N + 1];
bool del[N + 1]; 
int fa[N + 1]; 
int find(int u){
     if(u == fa[u]) return u;
     return fa[u] = find(fa[u]); 
}
void unite(int u,int v){
     u = find(u); v = find(v);
     if(u == v) return; 
     fa[v] = u; 
}
int main(){
    scanf("%d%d%d",&n,&m,&q); 
    map<pair<int,int>,int>mp;
    for(int i = 1; i <= n; i++) fa[i] = i; 
    for(int i = 0; i < m; i++){
         scanf("%d%d",&edge[i].first,&edge[i].second);
         int u = edge[i].first;
         int v = edge[i].second;
         if(u > v) swap(u,v); 
         mp[{u,v}] = i;
    }
    for(int i = 0; i < q; i++){
         scanf("%d%d",&query[i].first,&query[i].second);
         int u = query[i].first;
         int v = query[i].second;
      //   cout<<u<<' '<<v<<' '<<mp[{u,v}]<<endl; 
         if(u > v) swap(u,v); 
         del[mp[{u,v}]] = 1; 
    }
    for(int i = 0; i < m; i++){
          if(del[i]) continue; 
          //cout<<edge[i].first<<' '<<edge[i].second<<endl; 
          unite(edge[i].first,edge[i].second); 
    }
    int comp = 0;   
    for(int i = 1; i <= n; i++) if(fa[i] == i) comp++; 
    vector<int>res;
    for(int i = q - 1; i >=0; i--){
           int u = query[i].first;
           int v = query[i].second;
           ///cout<<comp<<' '<<u<<' '<<v<<endl; 
           res.push_back(comp);
           if(find(u) != find(v)){
                unite(u,v);
                comp--; 
           }  
    }
    reverse(res.begin(),res.end());
    for(int i = 0; i < res.size(); i++) printf("%d ",res[i]); 
    return 0; 
}