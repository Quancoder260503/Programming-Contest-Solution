#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <cstring>
#include <map>

#define sz(x) int(x.size())
#define ll long long 

using namespace std; 

map<int, string>dp[2][2][11]; 

string S;
int M; 

__int128_t stoll_128(string &s) { 
 __int128_t ret = 0; 
 for(int i = 0; i < sz(s); i++) { 
  ret = ret * 10 + (s[i] - '0'); 
 }    
 return ret; 
}


string memo(int pos, int last, int weird, int equal) { 
 if(pos == M) return (!weird && !equal) ? "" : "-1"; 
 if(dp[weird][equal][1 + last].count(pos)) return dp[weird][equal][1 + last][pos]; 
 string &ret = dp[weird][equal][1 + last][pos]; 
 ret = "-1"; 
 for(int i = (equal ? S[pos] - '0' : 0); i < 10; i++) {
  string next = memo(pos + 1, i, weird | (last == i), equal & (i == (S[pos] - '0')));
  if(next == "-1") continue; 
  next = (char)(i + '0') + next; 
  if(ret == "-1" || stoll_128(ret) > stoll_128(next)) { 
   ret = next;
  }
 }
 return ret; 
}

int main(void) {
 cin >> S; 
 M = sz(S); 
 string ret = memo(0, -1, 0, 1); 
 if(ret != "-1") cout << ret, exit(0); 
 for(int i = 0; i < 11; i++)
 for(int j = 0; j < 2; j++) 
 for(int k = 0; k < 2; k++) { 
  dp[k][j][i].clear(); 
 }
 S = '0' + S; 
 M = sz(S); 
 ret = memo(0, -1, 0, 1); 
 if(ret != "-1" && stoll_128(ret) > stoll_128(S)) cout << ret, exit(0); 
 S = '0' + S; 
 M = sz(S); 
 for(int i = 0; i < 11; i++)
 for(int j = 0; j < 2; j++) 
 for(int k = 0; k < 2; k++) { 
  dp[k][j][i].clear(); 
 }
 cout << memo(0, -1, 0, 1); 
 return 0; 
}