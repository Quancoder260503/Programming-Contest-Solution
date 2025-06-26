#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 5;
const int M = 1e6 + 5;
const int mod = (1 << 32); 
long long n,m,k,q;
long long a[N + 1];
vector<int>adj[N + 1]; 
int up[21][N + 1];
int deg[N + 1]; 
bool vis[N + 1];
vector<int>topo; 
int main(){
      scanf("%d%d",&n,&m);
      for(int i = 0; i < m; i++){
           int u,v; scanf("%d%d",&u,&v);
           adj[v].push_back(u);
           deg[u]++; 
      }
      priority_queue<int>pq;  
      for(int i = 1; i <= n; i++){
           if(!deg[i]) pq.push(i); 
      }
      while(pq.size()){
           int node = pq.top();
           pq.pop();
           topo.push_back(node); 
           for(int i = 0; i < adj[node].size(); i++){
                  int u = adj[node][i];
                  deg[u]--; 
                  if(!deg[u]) pq.push(u); 
           }
      }
      for(int i = topo.size() - 1; i >= 0; i--) printf("%d ",topo[i]); 
      return 0; 
}