#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2001;
long long n,L,m; 
long long A[N]; 
bool vis[N]; 
int adj[N][N];
int col[N]; 
int cnt[2]; 
bitset<N>dp; 
void dfs(int u, bool c){
      if(col[u] > - 1){
            if(col[u] != c){
                 printf("%d\n",-1); 
                 exit(0); 
            }
            return;
      }
      col[u] = c; 
      cnt[c] += 1; 
      for(int i = 1; i <= n; i++){
           if(u == i || adj[u][i]) continue; 
           dfs(i, !c); 
      }
}
signed main(){
     scanf("%d%d",&n,&m);
     for(int i = 0; i < m; i++){
           int u,v; scanf("%d%d",&u,&v);
           adj[u][v] = adj[v][u] = 1; 
     }
     memset(col,-1,sizeof(col));
     dp[0] = 1; 
     for(int i = 1; i <= n; i++){
          if(col[i] < 0){
               cnt[0] = cnt[1] = 0; 
               dfs(i, 1); 
               dp = (dp << cnt[0] | dp << cnt[1]);
          }
     }
     int ans = INT_MAX; 
     for(int i = 0; i <= n; i++){
          if(dp[i]) ans = min(ans, abs((int) n - 2 * i)); 
     }
     printf("%d\n",ans); 
     return 0; 
} 