#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 80002
#define x first 
#define y second
typedef pair<long long,long long> Vec; 
typedef long double ldb;
const int mod = 1e9 + 7; 
int n,m,sz;
int tree[N * 30]; 
int Last[N]; 
vector<int>adj[N]; 
set<int>col[N]; 
int ans[N]; 
typedef struct {
    long long cor,lb,rb,type,id;
} node;
node P[N * 30]; 
void push_down(int p){
    if(tree[p] != -1){
        tree[2 * p] = tree[2 * p + 1] = tree[p];
        tree[p] = -1;
    }
    return;
}
void update(long long x,int L,int R,int l = 0,int r = n,int p = 1){
    if(L > r || R < l) return;
    if(L <= l and r <= R){
        tree[p] = x; 
        return;
    }
      int mid = (l + r) >> 1;
      push_down(p);
      update(x,L,R,l,mid,2*p);
      update(x,L,R,mid+1,r,2*p+1);
}
int query(int L,int R,int l = 0, int r = n, int p = 1){
    if(L > r || R < l) return 0;
    if(L <= l and r <= R) return tree[p]; 
    push_down(p);
    int mid = (l + r) >> 1; 
    return query(L,R,l,mid, 2 * p) + query(L,R,mid + 1,r, 2 * p + 1); 
}
bool cmp(const node &a, const node &b){
      return a.cor == b.cor ? a.type < b.type : a.cor < b.cor;  
}
void dfs(int u, int p){
    for(int i = 0; i < adj[u].size(); i++){
         int v = adj[u][i];
         if(v == p) continue; 
         dfs(v,u);
         if(col[u].size() < col[v].size()) swap(col[u],col[v]);
         for(auto it : col[v]){
             col[u].insert(it); 
         }
    }
    ans[u] = (int) col[u].size(); 
}
signed main(void){
    scanf("%d%d",&n,&m);
    vector<long long>point;
    for(int i = 0; i < n; i++){
          long long xa,ya,xb,yb;
          scanf("%lld%lld%lld%lld",&xa,&ya,&xb,&yb);
          P[++sz].cor = xa; P[sz].lb = ya; P[sz].rb = yb; P[sz].id = i + 1; P[sz].type = 1; 
          P[++sz].cor = xb, P[sz].lb = ya; P[sz].rb = yb; P[sz].id = i + 1; P[sz].type = 3; 
          point.push_back(ya);
          point.push_back(yb); 
    }
    for(int i = 0; i < m; i++){
         long long xa,ya,col; 
         scanf("%lld%lld%lld",&xa,&ya,&col); 
         P[++sz].cor = xa; P[sz].lb = ya; P[sz].rb = ya; P[sz].id = col; P[sz].type = 2; 
         point.push_back(ya);  
    }    
    sort(point.begin(),point.end());
    point.erase(unique(point.begin(),point.end()),point.end()); 
    sort(P + 1, P + sz + 1,cmp); 
    int old_n = n;
    n = point.size() - 1; 
    memset(tree,-1,sizeof(tree)); 
    tree[1] = 0;
    for(int i = 1; i <= sz; i++){
        int posl = lower_bound(point.begin(),point.end(),P[i].lb) - point.begin(); 
        int posr = lower_bound(point.begin(),point.end(),P[i].rb) - point.begin();
        if(P[i].type == 1){
              int curp = query(posl,posl);
              adj[curp].push_back(P[i].id);
              Last[P[i].id] = curp; 
              update(P[i].id,posl,posr); 
        }
        else if(P[i].type == 2){
              int curp = query(posl,posl);
              col[curp].insert(P[i].id);
        }
        else{
             update(Last[P[i].id],posl,posr); 
        }
    }
    dfs(0,-1);
    for(int i = 1; i <= old_n; i++){
        printf("%lld\n",ans[i]); 
    } 
    return 0; 
}