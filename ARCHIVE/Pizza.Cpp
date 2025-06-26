// Backtracking Solution 
#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 4e5 + 10;
const int mod = 1e9 + 7;
long long n,m,k,q,r,tot;
int res;
char a[N + 1];
int timer = 1;
vector<int>S; 
bool vis[N + 1]; 
int in[N + 1], low[N + 1]; 
int fa[N + 1]; 
long long msk[N + 1]; 
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
vector<int>radj[N + 1];
long long val[N + 1];
struct point{
    int x,y; 
} store[N + 1];
struct house{
    int x,y,p; 
} house[N + 1]; 
int sqr(int x,int y){
     return x * x  + y * y;
}
void solve(){
     scanf("%ld%ld",&n,&r);
     scanf("%ld",&m); 
     for(int i = 1; i <= m; i++) cin>>store[i].x>>store[i].y;
     scanf("%ld",&q); 
     for(int i = 1; i <= q; i++) cin>>house[i].x>>house[i].y>>house[i].p; 
     for(int i = 1; i <= m; i++){
          for(int j = 1; j <= q; j++){
              int pro = sqr(store[i].x - house[j].x,store[i].y - house[j].y); 
              if(pro <= r * r){
                  msk[j] = msk[j] + (long long) (1 << (i - 1)); 
              }
          }
     }
}
void backtracking(int u){
     if(u > n){
            int ans = 0; 
            for(int i = 1; i <= q; i++){
                 if(tot & msk[i]) ans += house[i].p;
            }
            res = max(ans,res); 
            return; 
     }
     for(int i = fa[u - 1] + 1; i <= m - n + u; i++){
            tot += (1LL << (i - 1));
            fa[u] = i;   
            backtracking(u + 1); 
            tot -= (1LL << (i - 1)); 
     }
}
int main(){
     solve();
     backtracking(1);
     printf("%d \n",res); 
}

// Bitmask Solution 
#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 4e5 + 10;
const int mod = 1e9 + 7;
long long n,m,k,q,r;
int res;
char a[N + 1];
int timer = 1;
vector<int>S; 
bool vis[N + 1]; 
int in[N + 1], low[N + 1]; 
int fa[N + 1]; 
long long msk[N + 1]; 
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
vector<int>radj[N + 1];
long long val[N + 1];
struct point{
    int x,y; 
} store[N + 1];
struct house{
    int x,y,p; 
} house[N + 1]; 
int sqr(int x,int y){
     return x * x  + y * y;
}
void solve(){
     scanf("%ld%ld",&n,&r);
     scanf("%ld",&m); 
     for(int i = 1; i <= m; i++) cin>>store[i].x>>store[i].y;
     scanf("%ld",&q); 
     for(int i = 1; i <= q; i++) cin>>house[i].x>>house[i].y>>house[i].p; 
     for(int i = 1; i <= m; i++){
          for(int j = 1; j <= q; j++){
              int pro = sqr(store[i].x - house[j].x,store[i].y - house[j].y); 
              if(pro <= r * r){
                  msk[j] = msk[j] + (long long) (1 << (i - 1)); 
              }
          }
     }
    // for(int i = 1; i <= q; i++) cout<<msk[i]<<' ';
     for(int mask = 0; mask < (1 << m); mask++){
          if(__builtin_popcount(mask) > n) continue;
          int tot = 0; 
          for(int i = 1; i <= q; i++){
                if(mask & msk[i]) tot += house[i].p;
          }
          res = max(res, tot); 
     }
}
int main(){
     solve();
     printf("%d \n",res); 
} 