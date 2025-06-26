#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
const int64_t oo = 1e18 + 10; 
 
const int LOG = 20;
 
class MediumFermatTheorem { 
 public :
   vector<vector<int64_t>>pw; 
   set<int64_t>ans;
   
   int num_digit;
   int64_t sum; 
   vector<int64_t>ret; 
   vector<int>cnt, cnt_buff; 
   void rec(int pos, int last_d, int pow) {
    if(pos == num_digit) { 
     string cc = to_string(sum);
     fill(cnt_buff.begin(), cnt_buff.end(), 0); 
     for(int i = 0; i < sz(cc); i++) { 
      cnt_buff[cc[i] - '0']++; 
     }
     int fermat = true; 
     for(int i = 0; i < 10; i++) {
      fermat = fermat & (cnt_buff[i] == cnt[i]);  
     }
     if(fermat) {
      ans.insert(sum); 
     }
     return; 
    }
    for(int d = last_d; d < 10; d++) { 
      if(pow < sz(pw[d])) { 
       sum += pw[d][pow];
       cnt[d]++; 
       if(0 <= sum && sum < oo) { 
        rec(pos + 1, max(last_d, d), pow); 
       } 
       sum -= pw[d][pow];  
       cnt[d]--; 
      } 
    } 
  } 
   void preprocess() { 
    pw.resize(10); ; 
    cnt.resize(10); 
    cnt_buff.resize(10);
    for(int i = 0; i < 10; i++) { 
      pw[i].push_back(i > 0); 
      for(int j = 0; j < 62; j++) { 
       if(i > 0 && pw[i].back() > oo / i) break; 
       pw[i].push_back(1LL * pw[i].back() * i); 
      }
    }
    sum = 0; 
    for(int i = 1; i < LOG; i++) {
      for(int j = -2; j < 2; j++) {  
       num_digit = i + j; 
       if(num_digit > 0) rec(0, 0, i);
      } 
    }
    for(auto &x : ans) { 
    // cout << x << '\n'; 
     ret.push_back(x); 
    } 
    return; 
   }
   void solve(int64_t N, int64_t M) { 
    int posR = upper_bound(ret.begin(), ret.end(), M) - ret.begin() - 1; 
    int posL = upper_bound(ret.begin(), ret.end(), N - 1) - ret.begin();
    cout << posR - posL + 1 << '\n'; 
    return; 
   }
}; 
 
int main(void) { 
  MediumFermatTheorem fermat; 
  fermat.preprocess(); 
  int T; 
  cin >> T; 
  int64_t N, M; 
  for(int i = 0; i < T; i++) { 
   cin >> N >> M; 
   fermat.solve(N, M); 
  } 
  return 0; 
}