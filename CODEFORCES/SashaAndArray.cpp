#include "bits/stdc++.h"
#include <stdio.h>
#include <array>
#include <algorithm>
using namespace std;
#define N 1500000
#define inf 10000000000
#define x first 
#define y second
typedef pair<long long,long long> Vec; 
typedef long double ldb;
const int mod = 1e9 + 7; 
long long finv[N];
long long fac[N];
long long inv[N]; 
int n,k,q;  
using Matrix = array<array<long long,2>,2>;
long long lz[N];
array<long long,2>tree[N];
Matrix F[N]; 
Matrix FibBase;
array<long long,2>multiplication(array<long long,2> &a,Matrix &b) {
        array<long long,2>c = {0,0};
        for (int j = 0; j < 2; ++j){
            for(int k = 0; k < 2; k++){
                 c[j] +=  a[k] % mod * b[k][j] % mod;
                 c[j] %= mod;
            }
        }
        return c;
}
Matrix matrix_multiplication(Matrix &a, Matrix &b) {
        Matrix c = {{{0,0},{0,0}}};
        for (int i = 0; i < 2; ++i){
            for (int j = 0; j < 2; ++j){
                for(int k = 0; k < 2; ++k){
                    c[i][j] +=  a[i][k] % mod * b[k][j] % mod;
                    c[i][j] %= mod;
                }
            }
        }
        return c;
}
Matrix mpow(long long exp) {
        Matrix ans = FibBase;
        for(int mask = 0; mask < 55; mask++){
              if(exp & (1ll << mask)){
                   ans = matrix_multiplication(ans , F[mask]); 
              }
        }
        return ans;
}
void merge(int p){
     tree[p][0] = (tree[2 * p][0] + tree[2 * p + 1][0] ) % mod;
     tree[p][1] = (tree[2 * p][1] + tree[2 * p + 1][1] ) % mod;
}
void build(int l = 1, int r = n, int p = 1){
    if(l == r){
        tree[p] = {0,1}; 
        return; 
    }
    int mid = (l + r) >> 1;
    build(l,mid,2 * p);
    build(mid + 1, r, 2 * p + 1); 
    merge(p); 
}
void mul(int p, Matrix b){
     array<long long,2> a = tree[p]; 
     a = multiplication(a,b);
     tree[p] = {a[0],a[1]}; 
     return;
}
void push_down(int p){
     if(lz[p] != 0){
         mul(2 * p, mpow(lz[p] - 1));
         mul(2 * p + 1, mpow(lz[p] - 1)); 
         lz[2 * p] += lz[p];
         lz[2 * p + 1] += lz[p];
         lz[p] = 0;
     }
     return;
}
void update(int x, int L, int R, int l = 1, int r = n,int p = 1){
     if(L > r || R < l) return;
     if(L <= l && r <= R){
          mul(p, mpow(x - 1));
          lz[p] += x;
          return;
     }
     push_down(p);
     int mid = (l + r) >> 1; 
     update(x,L,R,l,mid,2 * p);
     update(x,L,R,mid + 1,r, 2 * p + 1); 
     merge(p); 
}
long long query(int L,int R,int l = 1, int r = n,int p = 1){
     if(L > r || R < l) return 0;
     if(L <= l && r <= R) return tree[p][0]; 
     int mid = (l + r) >> 1; 
     push_down(p);
     return (query(L,R,l,mid,2 * p) + query(L,R,mid + 1,r,2 * p + 1) + mod) % mod;
}
signed main(void){
     scanf("%d%d",&n,&q);
     build();
     FibBase = {{{0,1},{1,1}}};
     for(int i = 0; i < 55; i++){
           if(i > 0) F[i] = matrix_multiplication(F[i - 1],F[i - 1]);
           else F[i] = FibBase;
     }
     for(int i = 1; i <= n; i++){
          int x; scanf("%d",&x);
           update(x,i,i); 
     }
     for(int i = 0; i < q; i++){
         int type; scanf("%d",&type);
         if(type == 1){
              int l,r,x; scanf("%d%d%d",&l,&r,&x);
              update(x,l,r); 
         }
         else{
              int l,r; scanf("%d%d",&l,&r);
              long long ans = query (l,r) % mod;
              printf("%lld\n",ans); 
         }
     }
     return 0;
}