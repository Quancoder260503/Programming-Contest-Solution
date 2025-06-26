#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 1500000
#define inf 100000000000
#define x first 
#define y second
typedef pair<long long,long long> Vec; 
typedef long double ldb;
const int mod = 1e9 + 7; 
long long finv[N];
long long fac[N];
long long inv[N]; 
int n,k,a,b,m,t,p,lim;  
long long Dist[N][15]; 
long long DP[N][15][2]; 
vector<pair<long long,int> >adj[N]; 
struct cities{
    int times;
    int loc; 
} C[N]; 
void dijsktra(int src,int id){
      using T = pair<long long,int>;
      priority_queue<T,vector<T>,greater<T> >pq; 
      pq.push(make_pair(0,src)); 
      Dist[src][id] = 0;
      while(pq.size()){
           long long dst;
           int node;
           pair<long long,int> t = pq.top(); 
           dst = t.first; node = t.second;
           pq.pop();
           if(Dist[node][id] != dst) continue;
           for(int i = 0; i < adj[node].size(); i++){
                int v = adj[node][i].first;
                long long w = adj[node][i].second;
                if(Dist[v][id] > Dist[node][id] + w){
                     Dist[v][id] = Dist[node][id] + w;
                     pq.push(make_pair(Dist[v][id],v)); 
                }
           }
      }
}
signed main(void){
     scanf("%d%d%d%d%d",&n,&p,&m,&lim,&t); 
     for(int i = 0; i < p; i++){
         scanf("%d%d",&C[i].loc, &C[i].times); 
     }
     for(int i = 0; i < m; i++){
          int u,v,w; scanf("%d%d%d",&u,&v,&w);
          adj[u].push_back(make_pair(v,w));
          adj[v].push_back(make_pair(u,w)); 
     }
     memset(Dist,63,sizeof(Dist)); 
     memset(DP,63,sizeof(DP)); 
     for(int i = 0; i < p; i++){
         dijsktra(C[i].loc,i); 
     }
     for(int i = 0; i < p; i++){
         DP[(1 << i)][i][0] = Dist[0][i] + C[i].times; 
     }
     for(int mask = 0; mask < (1 << p); mask++){
          for(int i = 0; i < p; i++){
               if(mask & (1 << i)){
                    for(int j = 0; j < p; j++){
                         if(i == j) continue;
                         if(mask & (1 << j)){
                             DP[mask][i][1] = min(DP[mask][i][1], DP[mask xor (1 << i)][j][1] + Dist[C[i].loc][j] + C[i].times);
                             DP[mask][i][1] = min(DP[mask][i][1], DP[mask xor (1 << i)][j][0] + t + C[i].times); 
                             DP[mask][i][0] = min(DP[mask][i][0], DP[mask xor (1 << i)][j][0] + Dist[C[i].loc][j] + C[i].times);
                         }
                    }
               }
          }
     }
     long long ans0 = inf;
     long long ans1 = inf; 
     for(int i = 0; i < p; i++){
          ans0 = min(DP[(1 << p) - 1][i][0] + Dist[0][i], ans0);
          ans1=  min(DP[(1 << p) - 1][i][1] + Dist[0][i], ans1);  
     }
     if(ans0 > lim && ans1 > lim){
          printf("impossible\n"); 
          return 0;    
     }
     if(ans0 <= lim){
           printf("possible without taxi\n"); 
           return 0;
     }
     if(ans1 <= lim){
           printf("possible with taxi\n"); 
     }
     return 0; 
}