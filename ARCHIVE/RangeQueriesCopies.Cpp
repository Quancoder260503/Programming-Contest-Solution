#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const int INF = 1e7 + 10;
const int mod = 1e9 + 7; 
long long n,m,q,k;
int timer = 1;
long long a[N + 1];
long long dp[N + 1]; 
struct node{
     long long val;
     node *l, *r;
     node(long long x): val(x), l(nullptr), r(nullptr) {}
     node(node *ll, node *rr){
          l = ll; r = rr; 
          val = 0;
          if(l)val += l -> val; 
          if(r) val += r -> val; 
     }
     node(node *cur): val(cur -> val), l(cur -> l), r(cur -> r) {}
};
node *root[N + 1];
node *build(int l = 1, int r = n){
      if(l == r) return new node(a[l]); 
      int mid = (l + r) >> 1;
      return new node(build(l,mid),build(mid + 1,r));
}
node *update(node *cur,int val,int pos,int l = 1,int r = n){
      if(l == r) return new node(val);
      int mid = (l + r) >> 1;
      if(pos > mid) return new node(cur -> l, update(cur -> r,val,pos,mid + 1,r));
      return new node(update(cur -> l, val,pos,l,mid), cur -> r); 
}
long long query(node *cur, int L, int R,int l = 1,int r = n){
      if(L > r or R < l) return 0;
      if(L <= l and r <= R) return cur -> val; 
      int mid = (l + r) >> 1; 
      return query(cur -> l, L, R, l, mid) + query(cur -> r,L,R, mid + 1,r);
}
int main(){ 
     scanf("%d%d",&n,&q);
     for(int i = 1; i <= n; i++) scanf("%lld",&a[i]); 
     root[timer++] = build(); 
     for(int i = 0; i < q; i++){
          int t; scanf("%d",&t);
          if(t == 1){
              int k,p,x; scanf("%d%d%d",&k,&p,&x);     
              root[k] = update(root[k],x,p);
          } 
          if(t == 2){
              int k,l,r; scanf("%d%d%d",&k,&l,&r);
              long long ans = query(root[k],l,r); 
              printf("%lld \n",ans); 
          }
          if(t == 3){
              int k; scanf("%d",&k);
              root[timer++] = new node(root[k]); 
          }
     }
     return 0; 
}