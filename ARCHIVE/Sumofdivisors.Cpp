#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=4e5+1;
const int sz1=1e6+900000;
const int mod = 1e9 + 7;
const int mod2 = 5e8 + 4; 
const int inf=1e7+5;
long long ans = 0;
bool prime[sz1];
long long pw[sz];
long long n,m,k,t;
long long a[sz];
long long d[sz1];
int main(){
     scanf("%lld",&n);
     long long cur = 1; 
     while(cur <= n){
      long long div = n / cur;
      long long val = n / div;
      long long calc = (((val - cur + 1) % mod) * ((val + cur) % mod) % mod) * (mod2 % mod) % mod ;
      ans = (ans + div % mod * calc % mod)% mod;
      cur = val + 1;
     }
     cout<<ans<<endl;
}