#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int sz = 4e5 + 1;
const int N = (1 << 19);
const int M = 1e6 + 10;
const int mod = (1 << 32);
long long n,m,k,q,x,ans;
vector<pii>adj[N + 1];
bool vis[N + 1];
long long a[N + 1]; 
char s[N + 1];
int main(){
     scanf("%s",s); 
     n = strlen(s);
     int pos = n; 
     for(int i = n - 3; i >= 0; i--){
          for(int j = 1; i + 2 * j < n; j++){
                if(s[i] == s[i + j] && s[i] == s[i + 2 * j]){
                       pos = min(pos,i + 2 * j);
                       break; 
                }
          }
          if(pos <= n) ans += (n - pos); 
     }
     printf("%lld\n",ans); 
     return 0;     
}