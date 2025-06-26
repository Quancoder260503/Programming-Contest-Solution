#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=4e5+1;
const int sz1=1e6+1;
const int inf=1e7+5;
int n,m;
long long a[sz1];
long long d[sz1];
int main(){
      scanf("%d",&n);
      int bound = 0;
      for(int i = 1; i <= n; i++){
           int x; scanf("%d",&x); 
           bound = max(x,bound);
           d[x]++;
      }
      int ans = 1;
      for(int i = 2; i <= bound; i++){
           int cnt = 0;
           for(int j = i; j <= bound; j+=i){
                cnt+=d[j];
                if(cnt >= 2){
                     ans = i;
                     break;
                }
           }
      }
      cout<<ans<<endl;
}