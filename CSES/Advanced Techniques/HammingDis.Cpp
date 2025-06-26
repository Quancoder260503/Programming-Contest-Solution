#include <stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 5;
const int M = 1e6 + 5;
const int mod = (1 << 32); 
long long n,m,k,q,x;
long long dp[N + 1]; 
long long bit[N + 1]; 
int main(){
     scanf("%d%d",&n,&m); 
     for(int i = 1; i <= n; i++){
          string s; cin>>s;
          for(int j = 0; j < m; j++){
                if((s[j] - '0')){
                     bit[i] += (1ll << j); 
                }
          }
     }
     int ans = INT_MAX; 
     for(int i = 1; i <= n; i++){
          for(int j = i + 1; j <= n; j++){
               ans = min(ans, __builtin_popcount(bit[i] xor bit[j])); 
          }
     }
     printf("%d \n",ans); 
     return 0; 
}