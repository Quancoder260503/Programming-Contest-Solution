#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int sz = 4e5 + 1;
const int N = 2e5 + 10;
const int M = 1e6 + 10;
const int mod = (1 << 32);
long long n,m,k,q,x;
vector<pair<int,pii>>adj[N + 1];
int timer = 1;
void solve(){
     scanf("%d",&n);
     long long sum = 0;
     for(int i = 1;  i  <= n; i++){
           long long x; scanf("%d",&x);
           sum = sum xor x; 
     }
     if(sum) printf("first\n");
     else printf("second\n"); 
}
int main(){
     int t;
     scanf("%d",&t); 
     while(t--){
         solve();
     }
     return 0; 
}