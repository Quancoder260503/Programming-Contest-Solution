#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii; 
const int N = 5e5 + 5;
vector<pair<int,int>>adj[N + 1];
int n,m,timer; 
int indeg[N + 1];
int outdeg[N + 1];
bool vis[N + 1], use[N + 1]; 
list<int> EulerWalk(int u){
      list<int>ans;
      ans.push_back(u);
      timer++; 
      while(adj[u].size()){
           auto v = adj[u].back();
           adj[u].pop_back();
           if(use[v.second]) continue;
           use[v.second] = 1; 
           ans.push_back(v.first); 
           u = v.first; 
      }
      for(list<int>:: iterator it = ++ans.begin(); it != ans.end(); it++){ 
            auto re = EulerWalk(*it);
            re.pop_back();
            ans.splice(it,re); 
      }
      return ans; 
 }
int main(){
     scanf("%d%d",&n,&m);
     for(int i = 0; i < m; i++){
          int u,v; scanf("%d%d",&u,&v);
          adj[u].push_back({v,i});
          outdeg[u]++; indeg[v]++; 
     }
     if(indeg[1] + 1 != outdeg[1] or indeg[n] != outdeg[n] + 1){
          cout<<"IMPOSSIBLE";
          return 0; 
     }
     for(int i = 2; i < n; i++){
         if(outdeg[i] != indeg[i]){
             cout<<"IMPOSSIBLE";
             return 0; 
         }
     }
     adj[n].push_back({1,m}); 
     list<int>cyc = EulerWalk(1); 
     if(cyc.size() < m + 1){
          cout<<"IMPOSSIBLE";
          return 0; 
     }
     for(auto it1 = cyc.begin(), it2 = ++cyc.begin(); it2 != cyc.end(); it1++,it2++){
           if(*it1 == n and *it2 == 1){
                for(auto it = it2 ; it != cyc.end(); it++) cout<<(*it)<<' ';
                ++it1;
                for(auto it = ++cyc.begin(); it != it1; it++) cout<<(*it)<<' ';
           }
     }
     return 0; 
}