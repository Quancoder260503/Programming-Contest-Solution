#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 1500000
#define x first 
#define y second
#define mp make_pair
typedef pair<long long,long long> Vec; 
typedef long double ldb;
const int mod = 1e9 + 7; 
int n,k,timer; 
vector<int>adj[N];
vector<int>radj[N]; 
vector<int>skills;
int dep[N]; 
priority_queue<pair<int,int> >pq; 
priority_queue<int>q;
bool vis[N]; 
void dfs(int u, int p){
    for(int i = 0; i < adj[u].size(); i++){
          int v = adj[u][i];
          if(v == p) continue;
          dep[v] = dep[u] + 1; 
          dfs(v,u); 
    }
    pq.push(mp(dep[u],u));
}
void dfs1(int u,int d){
     if(vis[u]){
         q.push(d);
         return; 
     }
     vis[u] = 1; 
     for(int i = 0; i < radj[u].size(); i++){
          int v = radj[u][i];
          dfs1(v,d + 1); 
     }
}
signed main(void){
     scanf("%d%d",&n,&k);
     for(int i = 1; i <= k; i++){ 
        int x; scanf("%d",&x);
        skills.push_back(x); 
     }
     for(int i = 1; i < n; i++){
         int u; scanf("%d",&u);
         adj[u].push_back(i);
         radj[i].push_back(u); 
     }
     sort(skills.rbegin(),skills.rend()); 
     timer = 1;
     dfs(0,-1);
     vis[0] = 1; 
     while(pq.size()){
           pair<int,int> node = pq.top();
           pq.pop(); 
           dfs1(node.second,0); 
     } 
     long long ans = 0;
     int curr = 0;
     while(q.size() && curr < k){
        ans += 1ll * q.top() * skills[curr]; 
        q.pop();
        curr++; 
     }
     for(int i = curr; i < k; i++){
        ans += skills[i]; 
     }
     printf("%lld\n",ans); 
     return 0;
}