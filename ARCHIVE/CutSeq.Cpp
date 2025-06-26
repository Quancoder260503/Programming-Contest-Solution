#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int N = 1e5 + 10;
const int M = 110;
const long long INF = 1e17; 
long long n,k,m;
long long dp[N + 1];
long long a[N + 1];
long long pf[N + 1]; 
long long ls[N + 1]; 
multiset<long long>S;
int main(){
      scanf("%d%lld",&n,&m);
      for(int i = 1; i <= n; i++){ 
           scanf("%lld",a + i);
           pf[i] = pf[i - 1] + a[i]; 
           if(a[i] > m){
                printf("%d\n",-1);
                return 0; 
           }
      }
      int l = 1;
      int r = 0; 
      for(int i = 1, j = 0; i <= n; i++){
           while(pf[i] - pf[j] > m) j++;
           while(l <= r && ls[l] <= j){
                 if(l < r) S.erase(a[ls[l + 1]] + dp[ls[l]]); 
                 l++;
           }
           while(l <= r && a[ls[r]] <= a[i]){
                 if(l < r) S.erase(a[ls[r]] + dp[ls[r - 1]]);
                 r--; 
           }
           ls[++r] = i; 
           if(l < r) S.insert(a[i] + dp[ls[r - 1]]);
           dp[i] = dp[j] + a[ls[l]];
           if(l < r) dp[i] = min(dp[i], *S.begin());           
      }
      printf("%lld\n", dp[n]); 
      return 0; 
}