#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<long long,long long> pii;
const int N = 1e5 + 100;
const int INF = 1e7 + 10; 
const int mod = 1e9 + 7;
long long n,m,k,tot,w;
int timer = 1;
vector<long long>lf,ri; 
long long a[N + 1]; 
long long V[N + 1],W[N + 1],C[N + 1];
long long dp[N + 1]; 
int main(){
      scanf("%d%d",&n,&w);
      for(int i = 1; i <= n; i++) scanf("%d",&W[i]);
      for(int i = 1; i <= n; i++) scanf("%d",&V[i]);
      for(int i = 1; i <= n; i++) scanf("%d",&C[i]);  
      fill(dp, dp + w + 1, -INT_MAX);
      dp[0] = 0; 
      for(int i = 1; i <= n; i++){
            for(long long c = 1; C[i] > 0; c++){
                 long long copy = min(c,C[i]); 
                 C[i] -= copy;
                 for(int j = w; j >= 0; j--){
                      if(j >= copy * W[i] and dp[j - copy * W[i]] >= 0){
                           dp[j] = max(dp[j], dp[j - copy * W[i]] + copy * V[i]); 
                      }
                 }
            }
      }
      for(int i = 1; i <= w; i++) dp[i] = max(dp[i],dp[i - 1]); 
      printf("%lld \n",dp[w]); 
}