#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
long long n,k,p,m,q;
long long a[N + 1]; 
pair<int,int>edge[N + 1];
pair<int,int>query[N + 1];
vector<int>adj[N + 1]; 
bool del[N + 1]; 
int fa[N + 1]; 
int in[N + 1];
int timer = 1;
void dfs(int u,int p){
     in[u] = timer++;
     for(int i = 0; i < adj[u].size(); i++){
           int v = adj[u][i];
           if(v == p) continue;
           dfs(v,u);
     }
}
bool cmp(int a,int b){
     return in[a] > in[b];
}
int main(){
    scanf("%d",&n); 
    for(int i = 0; i < n - 1; i++){
         int u,v; scanf("%d%d",&u,&v);
         adj[u].push_back(v);
         adj[v].push_back(u); 
    }
    vector<int>ans;
    for(int i = 1; i <= n; i++){
        if(adj[i].size() == 1) ans.push_back(i); 
    }
    dfs(1,0); 
    sort(ans.begin(),ans.end(),cmp); 
    int res = ans.size() % 2 == 0 ? ans.size() / 2 : ans.size() / 2 + 1; 
    printf("%d\n",res); 
    for(int i = 0; i < res; i++){
         printf("%d %d\n",ans[i],ans[(i + res) % ans.size()]); 
    }
    return 0; 
}