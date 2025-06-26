#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=4e5+1;
const int sz1=1e6+1;
const int inf=1e7+5;
long long n,m,k;
long long ans;
long long a[sz1];
long long d[sz1];
int main(){
      scanf("%lld%lld",&n,&k);
      for(int i = 0; i < k; i++) scanf("%lld", a + i);
      ans = n;
      long double r = log(n) + 0.001;
      for(int mask = 0; mask < (1 << k); mask++){
           bool even = (__builtin_popcount(mask) & 1);
           long long p = 1;
           long double l = 0.0;
           for(int i = 0; i < k; i++){
                if( (1<<i) & mask){
                     l += log(a[i]);
                     p *= a[i]; 
                }
           }
           if(l < r){
                ans = ans + (even ?  1 : -1)*(n / p);
           }
      }
      cout<<ans<<endl; 
}