#include "bits/stdc++.h"
using namespace std;
#define N 1000005
vector<int>adj[N];
int in[N];
int out[N];
int timer = 1; 
int n; 
long long ans[N]; 
struct employee{ 
    int key;
    int value; 
    int to;
} A[N]; 
long long tree[N * 4]; 
void dfs(int u, int p){
     in[u] = timer++; 
     for(int i = 0; i < adj[u].size(); i++){
         int v = adj[u][i];
         if(v == p) continue; 
         dfs(v,u); 
     }
     out[u] = timer - 1; 
} 
void update(long long val,int pos,int l = 1, int r = n, int p = 1){
      if(l == r){
         tree[p] += val; 
         return; 
      }
      int mid = (l + r) / 2; 
      if(pos <= mid) update(val,pos,l,mid,2 * p);
      else update(val,pos,mid + 1,r, 2 * p + 1);
      tree[p] = tree[2 * p + 1] + tree[2 * p]; 
}
long long query(int L,int R,int l = 1,int r = n, int p = 1){
       if(L > r || R < l) return 0; 
       if(L <= l && r <= R) return tree[p];
       int mid = (l + r) / 2;
       return query(L,R,l,mid,2 * p) + query(L,R,mid + 1,r,2 * p + 1); 
}
bool cmp(employee &a, employee &b){
    return a.key == b.key ?  in[a.to] < in[b.to] : a.key < b.key;
} 
signed main(void){
      scanf("%d",&n);
      int root = -1; 
      for(int i = 1; i <= n; i++)
      {
         int u;
         scanf("%d%d%d",&u,&A[i].key,&A[i].value);
         A[i].to = i;
         if(u == - 1){
            root = i; 
         }
         else{
             adj[u].push_back(i); 
         }
      }
      dfs(root,0);
      sort(A + 1, A + n + 1,cmp); 
      for(int i = 1; i <= n; i++)
      {
         int curr = A[i].to;
         ans[curr] = query(in[curr],out[curr]); 
         update(A[i].value, in[curr]);
      }
      for(int i = 1; i <= n; i++)
      {
         printf("%lld\n",ans[i]); 
      }
      return 0; 
}