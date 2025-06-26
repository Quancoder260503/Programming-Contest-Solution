#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  string S; 
  cin >> S; 
  int64_t ret = 0; 
  vector<int>freq(26); 
  for(int i = 0; i < sz(S); i++) { 
    freq[S[i] - 'a']++; 
  }
  for(int i = 0; i < sz(freq); i++) { 
    ret = max(ret, 1LL * freq[i]); 
  }
  map<pair<char, char>, int64_t>mp; 
  fill(freq.begin(), freq.end(), 0); 
  for(int i = 0; i < sz(S); i++) { 
    for(int j = 0; j < 26; j++) { 
      if(freq[j] > 0) { 
        mp[{j, S[i] - 'a'}] += freq[j]; 
      }
    }
    freq[S[i] - 'a']++; 
  }
  for(const auto &[_, c] : mp) { 
    ret = max(ret, c); 
  }
  cout << ret << '\n'; 
  return 0; 
}

/*
  The optimal string is at most two characters.
*/ 