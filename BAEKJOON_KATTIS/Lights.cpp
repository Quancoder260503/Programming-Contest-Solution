#include "bits/stdc++.h"
using namespace std; 
#define N 1000005
#define INF 10000000000000
#define mp make_pair
int deg[N]; 
using T = pair<long long,int>;
int n,m; 
long long adj[N]; 
signed main(void){
     scanf("%d%d",&n,&m);
     for(int i = 0; i < n; i++)
     {
         adj[i] = (1LL << i);       
     }
     for(int i = 0; i < m; i++)
     {
        int u,v; scanf("%d%d",&u,&v); 
        --u; --v; 
        adj[u] = adj[u] | (1LL << v);
        adj[v] = adj[v] | (1LL << u); 
     }
     int f = n / 2; 
     int s = n - f;
     vector<T>lef;
     vector<T>rig;
     for(int mask = 0; mask < (1LL << f); mask++)
     {    
          long long sumx = 0; 
          long long tot = 0;
          for(int i =  0; i < f; i++)
          {
             if(mask & (1LL << i)){
                sumx = sumx xor adj[i];
                tot += 1; 
             }
          }  
          lef.push_back(mp(sumx,tot)); 
     }
     sort(lef.begin(),lef.end());
     for(int mask = 0; mask < (1LL << s); mask++)
     {    
          long long sumx = 0; 
          long long tot = 0;
          for(int i =  0; i < s; i++)
          {
             if(mask & (1LL << i)){
                 sumx = sumx xor adj[f + i];
                 tot += 1; 
             }
          }  
          rig.push_back(mp(sumx,tot)); 
     }
     sort(rig.begin(),rig.end());
     long long nmask = (1LL << n) - 1;  
     long long ans = INF;
     for(int i = 0; i < rig.size(); i++){
          int pos = lower_bound(lef.begin(),lef.end(),mp(nmask xor rig[i].first,0)) - lef.begin(); 
          if((lef[pos].first xor rig[i].first) == nmask){
              ans = min(ans, 1LL * (rig[i].second+ lef[pos].second)); 
          }
     }
     printf("%lld\n",ans); 
     return 0; 
}