#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<long long,long long> pii;
const int N = 1e7 + 100;
const int INF = 1e7 + 10; 
const int mod = 1e9 + 7;
long long n,m,tot;
int timer = 1;
long long W[36];
vector<long long> subset(int l,int r){
    int n = r - l + 1;
    vector<long long> res; 
    for(int mask = 0; mask < (1 << n); mask++){
         long long sum = 0; 
         for(int j = l; j <= r; j++){
              if(mask & (1 << (j - l))){
                   sum += W[j]; 
              }
         }
         sum %= m; 
         res.push_back(sum); 
    }
    return res; 
}
int main(){
       scanf("%d%lld",&n,&m);
       for(int i = 1; i <= n; i++) scanf("%lld",&W[i]);
       vector<long long> lf = subset(1, n / 2);
       vector<long long> ri = subset(n / 2 + 1, n);  
       sort(lf.begin(),lf.end());
       sort(ri.begin(),ri.end());
       int ptr = ri.size() - 1;
       long long ans = 0;
       for(int i = 0; i < lf.size(); i++){
             while(lf[i] + ri[ptr] >= m and ptr >= 0) ptr--; 
             if(lf[i] + ri[ptr] < m and ptr >= 0){
                  ans = max(ans,lf[i] + ri[ptr]);
             }
       }
       printf("%lld \n",ans);
}