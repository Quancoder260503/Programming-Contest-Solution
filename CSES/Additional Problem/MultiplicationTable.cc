#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int sz = 1e6 + 10;
const int N = 3e5 + 10;
const int M = 1e6 + 10;
const long long INF = 1e17; 
const int mod = 998244353;
long long a[N + 1];
long long dp[N + 1];
long long n,x;
int timer = 1;
vector<pii>adj[N + 1];
long long ans[N + 1]; 
int in[N + 1];
int out[N + 1]; 
char s[N + 1];
bool f(long long x){
     long long ans = 0; 
     for(int i = 1; i <= n; i++){
           ans += min(x / i, n);
     }
     return (ans >= ((1ll) * n * n + 1) / 2); 
}
int main(){
      scanf("%lld",&n);
      long long low = 0;
      long long high = (1ll) * n * n; 
      while(low < high){
            long long mid = low + (high - low) / 2; 
           // cout << low << ' ' << high << endl; 
            if(f(mid)){
                 high = mid; 
            }
            else{
                 low = mid + 1;
            }
      }
      printf("%lld\n",low); 
      return 0; 
}