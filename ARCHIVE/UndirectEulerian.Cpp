#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii; 
const int N = 5e5 + 5;
set<int>adj[N + 1];
int n,m; 
int deg[N + 1]; 
bool vis[N + 1]; 
list<int>cyc;
void Eulerian(list<int>::iterator it, int u){
      while(adj[u].size()){
             auto itr = adj[u].begin();
             int v = (*itr);
             if(adj[v].count(u)) adj[v].erase(u);
             adj[u].erase(v); 
             Eulerian(cyc.insert(it,u) , v); 
      } 
 }
int main(){
     scanf("%d%d",&n,&m);
     for(int i = 0; i < m; i++){
          int u,v; scanf("%d%d",&u,&v);
          adj[u].insert(v);
          adj[v].insert(u);
          deg[u]++; deg[v]++; 
     }
     int cnt = 0; 
     for(int i = 1; i <= n; i++){
          if(deg[i] & 1) cnt++; 
     }  
     if(cnt > 1){
          cout<<"IMPOSSIBLE";
          return 0; 
     }
     cyc.clear(); 
     int start = 1;
     Eulerian(cyc.begin(),start); 
     cyc.insert(cyc.begin(),start);
     if(cyc.size() != m + 1){
          cout<<"IMPOSSIBLE";
          return 0; 
     }
     for(list<int>::iterator it = cyc.begin(); it != cyc.end(); it++){
            cout<<(*it)<<' ';
     }
     return 0; 
}