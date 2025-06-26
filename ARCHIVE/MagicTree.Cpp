#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
#define blksz 500;
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
const int N = 3e5 + 10;
const int inf = 1e7 + 5;
const int mod = 1e9 + 7;
long long n,m,k,q,p,d;
vector<int>adj[N + 1];
long long w[N + 1];
long long r[N + 1]; 
map<long long,long long>dfs(int u,int p){
      map<long long,long long>cur; 
      for(int i = 0; i < adj[u].size(); i++){
             int v = adj[u][i];
             if(v == p) continue; 
             map<long long,long long> chld = dfs(v,u); 
             if(cur.size() < chld.size()) swap(cur,chld); 
             for(auto it : chld){
                  cur[it.first] += it.second; 
             }
      }
      cur[r[u]] += w[u];
      auto it = cur.find(r[u]); 
      long long remain = w[u];
      while(remain > 0 && next(it) != cur.end()){
             auto nxt = next(it);
             if(remain >= nxt -> second){
                  remain = remain - nxt -> second; 
                  cur.erase(nxt); 
             }
             else{
                  cur.at(nxt -> first) = cur.at(nxt -> first) -  remain; 
                  break; 
             }
      }
      return cur;
}
signed main(){
      ios_base::sync_with_stdio(0);
	    cin.tie(0);
      scanf("%d%d%d",&n,&m,&d);
      for(int i = 2; i <= n; i++){
           int u; scanf("%d",&u);
           adj[u].push_back(i);
      }
      for(int i = 0; i < n; i++){
            int v; scanf("%d",&v);
            scanf("%lld%lld",&r[v],&w[v]); 
      }
      map<long long,long long>res = dfs(1,0);
      long long ans = 0;
      for(auto it : res) ans += it.second;
      printf("%lld\n",ans); 
      return 0;
}