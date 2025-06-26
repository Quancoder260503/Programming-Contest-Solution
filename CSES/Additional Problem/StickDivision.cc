#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int sz = 4e5 + 1;
const int N = (1 << 19);
const int M = 1e6 + 10;
const int mod = (1 << 32);
long long n,l,r,ans,x;
vector<pii>adj[N + 1];
bool vis[N + 1];
long long a[N + 1]; 
long long b[N + 1]; 
long long bit[N + 1];
int main(){
     scanf("%d%d",&x,&n);
     priority_queue<int,vector<int>,greater<int>>pq;
     for(int i = 1; i <= n; i++){ 
          scanf("%lld",a + i);
          pq.push(a[i]); 
     }
     for(int i = 1; i < n; i++){
          int x,y; x = y = 0;
          if(pq.size()){
               x = pq.top(); 
               pq.pop();
          }
          if(pq.size()){
              y = pq.top(); 
              pq.pop();
          }
          pq.push(x + y);
        //  cout << x << ' ' << y <<' '<< x + y << endl; 
          ans += x + y; 
          
     }
     printf("%lld\n",ans); 
}