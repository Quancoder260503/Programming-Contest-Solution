#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
const int N = 5e4;
int n,m; 
bitset<N>dp[N / 2]; 
vector<int>comp[1000001]; 
signed main(){
       int n; 
       cin >> n;
       long long ans = 0;  
       for(int i = 0; i < n; i++){
            for(int j = 0; j < 5; j++){
                  int fla; cin >> fla;
                  comp[fla].push_back(i); 
            }
       }
       for(int i = 1; i <= 1000000; i++){
             if(!comp[i].size()) continue;
             bitset<N>cur;
             for(int j = 0; j < comp[i].size(); j++){
                  int u = comp[i][j];
                  cur[u] = 1;
             } 
             for(int j = 0; j < comp[i].size(); j++){
                  int u = comp[i][j]; 
                  if(u < 25000) dp[u] |= cur; 
             }
       }
       for(int i = 0; i < 25000; i++){
             ans += dp[i].count();
             dp[i].reset(); 
       }
       for(int i = 1; i <= 1000000; i++){
             if(!comp[i].size()) continue;
             bitset<N>cur;
             for(int j = 0; j < comp[i].size(); j++){
                  int u = comp[i][j];
                  cur[u] = 1; 
             } 
             for(int j = 0; j < comp[i].size(); j++){
                  int u = comp[i][j]; 
                  if(u >= 25000) dp[u - 25000] |= cur; 
             }
       } 
       for(int i = 0; i < 25000; i++){
             ans += dp[i].count();
             dp[i].reset(); 
       }
       cout <<  ((1ll) * n * n - ans) / 2 << endl; 
       return 0;
}