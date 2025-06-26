
 #include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
long long n,k,p;
long long a[N + 1]; 
int main(){
    scanf("%d%lld%lld",&n,&p,&k); 
    for(int i = 1; i <= n; i++) scanf("%lld",&a[i]);
    map<long long,long long>mp; 
    long long ans = 0; 
    for(int i = 1; i <= n; i++){
         long long mod = ((1ll) * a[i] % p * a[i] % p * a[i] % p * a[i] % p) - k % p * a[i] % p; 
         mod = (mod + p) % p; 
         ans += mp[mod];
         mp[mod]++; 
    }
    printf("%lld\n",ans); 
}