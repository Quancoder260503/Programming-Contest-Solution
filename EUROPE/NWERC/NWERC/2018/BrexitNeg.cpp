#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define mp make_pair
#define N 1500000
#define inf 10000000000
#define x first 
#define y second
typedef pair<long long,long long> Vec; 
typedef long double ldb;
const int mod = 1e9 + 7; 
vector<int> adj[N];
int A[N];  
int n,k;
int deg[N]; 
signed main(void){
     scanf("%d",&n);
     for(int i = 1; i <= n; i++){
          int e,d; scanf("%d%d",&e,&d); 
          A[i] = e; 
          for(int j = 0; j < d; j++){
                int v; scanf("%d",&v);
                adj[i].push_back(v); 
                deg[v] += 1; 
          }
     }
     priority_queue<pair<int,int> >pq;
     for(int i = 1; i <= n; i++){
        if(!deg[i]) pq.push(mp(-A[i],i));  
     }
     long long ans = 0;
     int ord = n; 
     while(pq.size()){
          pair<int,int> node = pq.top();
          pq.pop();
          int w = -node.first; 
          int u = node.second; 
          ord--; 
          ans = max(ans, 1ll * (w + ord));
          for(int i = 0; i < adj[u].size();  i++){
               int v = adj[u][i];
               deg[v]--; 
               if(!deg[v]) pq.push(mp(-A[v],v)); 
          }
     }
     printf("%lld\n",ans); 
     return 0; 
}