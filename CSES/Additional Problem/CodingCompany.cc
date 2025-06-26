#include<bits/stdc++.h>
#include<vector>
using namespace std;
typedef long long ll;
int n,x;
const int sz=10003;
ll a[sz];
ll pre[52][sz];
ll dp[52][sz];
const int M=1e9+7;
int main(){
  cin>>n>>x;
  for(int i=0;i<n;i++){
      cin>>a[i];
  } 
  sort(a,a+n);
  pre[0][5000]=1;
  for(int i=0;i<n;i++){
      for (int j=0;j<51;j++){
          for (int k=0;k<=10001;k++){
                dp[j][k]+=pre[j][k];
                dp[j][k]+=pre[j][k]*j;
                if (j+1<=51 and k>=a[i])dp[j][k]+=(j+1)*pre[j+1][k-a[i]];
                if (j>0 and k+a[i]<=10001) dp[j][k]+=pre[j-1][k+a[i]];
                dp[j][k]%=M;
          }     
      } for (int p=0;p<51;p++){
          for (int j=0;j<10001;j++){
              pre[p][j]=dp[p][j];
              dp[p][j]=0;
          }
      }
   } 
    ll res=0; 
    for (int i=5000;i<=5000+x;i++){
        res+=pre[0][i];
        res%=M;
    } cout <<res;
}