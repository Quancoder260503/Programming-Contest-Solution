#include "bits/stdc++.h"
#include <iostream> 
#include<vector>
#define blksz 500;
using namespace std;
const int N = 3e5 + 10;
const int inf = 1e7 + 5;
const int mod = 1e9 + 7;
long long n,m,k,q,p,d;
vector<int>adj[N + 1];  
vector<int>dv[N + 1]; 
map<pair<int,int>,int>dp[N + 1];
long long A[N + 1];
int calc(long double r){
      long double ans = 0; 
      for(int i = 1; i <= (int) r; i++){
             ans += (int) sqrt(r * r - i * i);
      }
      return ans * 4;
}
signed main(){
      scanf("%d",&n);
      long double low = 1;
      long double high = 19000;
      for(int i = 0; i < 200; i++){
             long double mid = (low + high)/ 2; 
             if(calc(mid) > n) high = mid;
             else low = mid;
      }
      cout << setprecision(15) << low << endl; 
      return 0;
}