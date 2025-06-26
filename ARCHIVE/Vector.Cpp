#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<long long,long long> pi;
const int N = 1e7 + 100;
const int INF = 1e7 + 10; 
const int mod = 1e9 + 7;
long long n,U,V;
int timer = 1;
long double dp[N + 1]; 
pair<long long,long long>a[N + 1]; 
long long d[N + 1];
map<pi,int>subset(int l,int r){
    int n = r - l + 1;
    map<pi,int>mp; 
    for(int mask = 0; mask < (1 << n); mask++){
         long long sumx = 0; 
         long long sumy = 0; 
         for(int j = l; j <= r; j++){
              if(mask & (1 << (j - l))){
                   sumx += a[j].first; 
                   sumy += a[j].second; 
              }
         }
         mp[{sumx,sumy}]++; 
    }
    return mp;
}
int main(){
       scanf("%d",&n); 
       for(int i = 1; i <= n; i++) scanf("%lld%lld",&a[i].first,&a[i].second);
       scanf("%lld%lld",&U,&V); 
       map<pi,int> left = subset(1 ,n / 2);
       map<pi,int> right = subset(n / 2 + 1, n); 
       long long ans = 0; 
       for(auto &it : left){
             pi cor = it.first;
           //  cout<<cor.first<<' '<<cor.second<<endl; 
             ans += right[{U - cor.first, V - cor.second}] * it.second;
       }
       printf("%lld",ans); 
}