#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 10010
#define x first 
#define y second
#define mp make_pair
typedef pair<long long,long long> Vec; 
typedef long double ldb;
const int mod = 1e9 + 7; 
vector<pair<int,pair<int,int> > >adj[N]; 
map<string,int>id;
long long DP[N];
long long dp[N];  
long long f[N]; 
int n,m;
int deg[N]; 
signed main(void){
     scanf("%d%d",&m,&n);
     int cnt = 0;
     for(int i = 0; i < n; i++){
          string u,v,t;
          int cost,pre;
          cin >> u >> v >> t >> cost >> pre; 
          if(!id.count(v)) id[v] = ++cnt; 
          if(!id.count(u)) id[u] = ++cnt; 
          adj[id[v]].push_back(mp(id[u],mp(cost,pre))); 
          deg[id[u]]++;
     }
     queue<int>q;
     memset(dp,63,sizeof(dp));  
     memset(DP,-1,sizeof(DP)); 
     for(int i = 1; i <= cnt; i++){
        if(!deg[i]){
              dp[i] = DP[i] = 0;
              q.push(i); 
        }
     }
     while(q.size()){
           int node = q.front();
           q.pop();
           for(int i = 0; i < adj[node].size(); i++){
                 int v = adj[node][i].first;
                 int cost = adj[node][i].second.first;
                 int pro = adj[node][i].second.second;
                 if(dp[v] > dp[node] + cost || (dp[v] == dp[node] + cost && DP[v] < DP[node] + pro)){
                       dp[v] = dp[node] + cost;
                       DP[v] = DP[node] + pro;
                 }
                 deg[v]--;
                 if(!deg[v]){
                    q.push(v); 
                 }
           }
     }
     memset(f,-1,sizeof(f));
     f[0] = 0;
     for(int i = 1; i <= cnt; i++){
          for(int j = m; j >= dp[i]; j--){
                f[j] = max(f[j], f[j - dp[i]] + DP[i]); 
          }
     }
     pair<long long,long long> ans;
     ans.first = -1; 
     ans.second = 0;
     for(int i = 0; i <= m; i++){
           if(ans.first < f[i]){
              ans.first = f[i];
              ans.second = i;
           }
     }
     printf("%lld\n%lld\n",ans.first,ans.second); 
     return 0; 
}