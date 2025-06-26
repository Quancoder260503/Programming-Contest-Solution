#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 10; 
long long n,m;
long long a[N + 1];
int msk[N + 1]; 
vector<int>adj[N + 1];
int in[N + 1];
int out[N + 1];
int dp[62]; 
bool pos[62];
void solve(){
     scanf("%lld",&n);
     scanf("%d",&m);
     long long tot = 0;
     for(int i = 0; i < 62; i++) pos[i] = 0, dp[i] = 0;  
     for(int i = 1; i <= m; i++){
     	  scanf("%d",&a[i]);
     	  tot += a[i]; 
    }
    if(tot < n){
    	  printf("%d \n",-1);
    	  return; 
    }
    for(int i = 0; i < 62; i++){
     	   if((1LL << i) & n) pos[i] = 1;
    }
    int cnt = 0;
    for(int i = 0; i < 62; i++){
    	for(int j = 1; j <= m; j++){
            if(a[j] & (1LL << i)) dp[i]++; 
    	}
    }
    for(int i = 0; i < 62; i++){
    	  if(pos[i]){
    	  	   if(!dp[i]){
    	  	   	   int nxt = i + 1; 
    	  	   	   while(!dp[nxt] and nxt < 62) nxt++;
    	  	   	   //cout<<nxt<<' '<<i<<endl; 
    	  	   	   for(int j = nxt; j > i; j--){
    	  	   	   	    cnt++;
    	  	   	   	    dp[j]--;
    	  	   	   	    dp[j - 1] += 2;
    	  	   	   }
    	  	   }
    	  	   dp[i]--;
    	  }
    	  dp[i + 1] += (dp[i] >> 1); 
    }
    printf("%d \n",cnt); 
}
int main(){
	   int t; scanf("%d",&t);
	   while(t--){
	   	    solve();
	   }
}