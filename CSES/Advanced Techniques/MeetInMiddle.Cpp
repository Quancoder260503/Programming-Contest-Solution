#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e7 + 100;
const int INF = 1e7 + 10; 
const int mod = 1e9 + 7;
long long n,m,q,dsz,M,k,x;
int timer = 1;
long double dp[N + 1]; 
long long a[N + 1]; 
long long d[N + 1];
vector<long long>subset(int l,int r){
    int n = r - l + 1;
    vector<long long>res;
    for(int mask = 0; mask < (1 << n); mask++){
         long long sum = 0; 
         for(int j = l; j <= r; j++){
              if(mask & (1 << (j - l))){
                   sum += a[j]; 
              }
         }
         res.push_back(sum); 
    }
    sort(res.begin(),res.end());
    return res;
}
int main(){
       scanf("%d%lld",&n,&x); 
       for(int i = 1; i <= n; i++) scanf("%lld",&a[i]);
       vector<long long>left = subset(1 ,n / 2);
       vector<long long>right = subset(n / 2 + 1, n); 
       long long ans = 0; 
       for(int i = 0; i < left.size(); i++){
             int lb = lower_bound(right.begin(),right.end(),x - left[i]) - right.begin();
             int rb = upper_bound(right.begin(),right.end(),x - left[i]) - right.begin(); 
             ans += (rb - lb); 
       }
       printf("%lld",ans); 
}