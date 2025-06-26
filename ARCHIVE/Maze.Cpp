#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii; 
const int N = 5e5 + 5;
vector<pair<int,int>>adj[N + 1];
int n,m,timer; 
int deg[N + 1]; 
bool vis[N + 1], use[N + 1]; 
long long prefix[N + 1];
int weight[301][301]; 
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
          long long w; cin>>w; 
          adj[u].push_back({v,i});
          adj[v].push_back({u,i});
          weight[u][v] = weight[v][u] = w;
          deg[u]++; deg[v]++;
     }
     for(int i = 1; i <= n; i++){
          if(deg[i] % 2 != 0){
               cout<< -1;
               return 0; 
          }
     }
     list<int>cyc = EulerWalk(1);  
     if(cyc.size() < m + 1){
          cout<< -1; 
          return 0; 
     }
     int u = *cyc.begin(); 
     int plus = 1;
     for(auto it = ++cyc.begin(); it != cyc.end(); it++){
           prefix[plus] = prefix[plus - 1] + weight[u][*it];
           u = *it; plus++; 
     }
     long long start = 1;
     long long curmn = LLONG_MAX; 
     plus = 1; 
     list<int>::iterator ptr;
     for(auto it = ++cyc.begin(); it != cyc.end(); it++){
           if(curmn > prefix[plus]){
                curmn = prefix[plus];
                start = *it; 
                ptr = it; 
           }
           plus++; 
     }
     list<int>ans; ans.clear(); 
     for(auto it = cyc.begin(); it != ptr; it++) ans.push_back(*it); 
     ans.push_back(*ptr);
     ans.insert(ans.begin(),ptr,--cyc.end()); 
     for(auto it = ans.begin(); it != ans.end(); it++) cout<<(*it)<<' '; 
     return 0; 
}