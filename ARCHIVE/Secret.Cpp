#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int sz = 4e5 + 1;
const int N = 2e5 + 10;
const int M = 1e6 + 10;
const int mod = (1 << 32);
long long n,m,k,q,x;
vector<pii>adj[N + 1];
struct Node{
      Node *c[2];
      int cnt, tot; 
};
int dfs(Node *node){
      if(node == NULL) return 0; 
      node -> tot = dfs(node -> c[0]) + dfs(node -> c[1]); 
      return node -> tot + node -> cnt; 
}
int main(){
     scanf("%d%d",&n,&m);
     Node *root = new Node();
     for(int i = 1; i <= n; i++){
          int x; scanf("%d",&x);
          Node *p = root; 
          for(int j = 0; j < x; j++){
               int y; scanf("%d",&y);
               if(!p -> c[y]) p -> c[y] = new Node(); 
               p = p -> c[y]; 
          }
          p -> cnt++; 
     }
     dfs(root);
     for(int i = 0; i < m; i++){
          int x; scanf("%d",&x);
          Node *p = root; 
          int res = 0; 
          int loop = 0; 
          for(int j = 0; j < x; j++){
                int k; scanf("%d",&k);
                if(!p -> c[k]){ 
                     for(int t = j + 1; t < x; t++) scanf("%d",&k); 
                     break; 
                }
                p  = p -> c[k]; 
                res += p -> cnt; 
                loop++; 
          }
          if(loop == x) res += p -> tot;
          printf("%d\n",res); 
     } 
     return 0; 
}