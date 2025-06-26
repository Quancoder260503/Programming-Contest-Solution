#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e7 + 100;
const int INF = 1e7 + 10; 
const int mod = 1e9 + 7;
long long n,m,q,dsz,M,k;
int timer = 1;
long double dp[N + 1]; 
long long a[N + 1]; 
long long d[N + 1];
string s;
int main(){
      cin>>s;
      int n = s.length(); 
      if(s.length() < 9){
          n = stoi(s);
          dp[0] = 1;
          for(int i = 1; i <= 10; i++){
               dp[i] = dp[i - 1] * i;
               if(dp[i] == n){
                    printf("%d \n",i);
                    return 0; 
               }
          }
      }
      for(int i = 1; i <= N; i++){
          dp[i] = dp[i - 1] + (long double) log10(i); 
      }
      for(int i = 1; i <= N; i++){
          if(n - 1 <= dp[i] and dp[i] <= n + 1){
               printf("%d \n",i);
               return 0; 
          }
      }
}