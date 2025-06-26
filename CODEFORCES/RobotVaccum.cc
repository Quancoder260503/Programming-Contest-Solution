#include "bits/stdc++.h"

using namespace std;

int main(void) { 
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0); 
 int N; 
 cin >> N; 
 vector<string>a(N); 
 vector<int>cntH(N), cntS(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i];
  for(int j = 0; j < a[i].size(); j++) { 
   (a[i][j] == 'h' ? cntH[i] : cntS[i])++; 
  }
 } 
 vector<int>ord(N); 
 iota(ord.begin(), ord.end(), 0); 
 sort(ord.begin(), ord.end(), [&](int i, int j) { 
  return 1LL * cntH[i] * cntS[j] < 1LL * cntH[j] * cntS[i]; 
 }); 
 string S = ""; 
 for(int i = 0; i < N; i++) { 
  S += a[ord[i]]; 
 }
 int cnt = 0; 
 int64_t ret = 0; 
 for(int i = 0; i < S.size(); i++) { 
  if(S[i] == 'h') ret += cnt; 
  else cnt++; 
 }
 cout << ret << '\n'; 
 return 0; 
}