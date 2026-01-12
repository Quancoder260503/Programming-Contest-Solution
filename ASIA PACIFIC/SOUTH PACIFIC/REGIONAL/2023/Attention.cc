#include <iostream>
#include <algorithm> 
#include <vector> 
#include <cstring>
#include <climits> 
#include <assert.h> 

using namespace std; 

#define ll long long 

ll k, dp[300005][2], a[300005]; 
int n;

ll memo(int pos, int who) { 
 if(pos == 0) { 
  return a[pos] % (k + 1) != 0 && (n - pos) % 2 == 1; 
 } 
 ll &ret = dp[pos][who]; 
 if(ret != -1) return ret; 
 ret = 0; 
 if((n - pos) % 2 == 0 || a[pos] % (k + 1) == 0) return ret = memo(pos - 1, who); 
 if(a[pos] % (k + 1) == 1) return ret = memo(pos - 1, 1 - who) ^ 1; 
 return ret = memo(pos - 1, who) | (memo(pos - 1, 1 - who) ^ 1); 
} 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 cin >> n >> k; 
 for(int i = 0; i < n; i++) { 
  cin >> a[i];  
 } 
 memset(dp, -1, sizeof dp); 
 cout << (memo(n - 1, 0) ? "Aaron" : "Bertha") << '\n'; 
 return 0;    
}