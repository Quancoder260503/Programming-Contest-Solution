#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 5e5 + 5;
int up[21][N + 1];
int dp[N + 1];
int a[N + 1];
int n,m,q;
long long res,cnt; 
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
int trs,dsz,psz;
bool vis[N + 1]; 
int st[N + 1],low[N + 1];
int comsize = 0; 
void dfs(int u,int p){
    a[u] = low[u] = ++dsz;
    st[++psz] = u;
    comsize++; 
    for(int i = 0; i < tadj[u].size(); i++){
        int v = tadj[u][i];
        if(v == p) continue;
        if(!a[v]){
            dfs(v,u);
            low[u] = min(low[u] , low[v]);
            if( low[v] >= a[u]){
                int j = u;
                cnt = 1 ; 
                while(j != v){
                    j = st[psz--];
                    ++cnt; 
               } 
               res = max(cnt, res);
            }
        }
        else low[u] = min(a[v] , low[u]);
    }
}
int main(){
     scanf("%d%d",&n,&m);
     if(m == 0){
          cout<<1<<endl; 
          return 0; 
     }
     for(int i = 0; i < m; i++){
         int u,v; scanf("%d%d",&u,&v);
         tadj[u].push_back(v);
         tadj[v].push_back(u); 
     }
     for(int i = 1; i <= n; i++) if(!a[i]) dfs(i,0); 
     cout<<res<<endl; 
}