#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N, Q; 
  Q = 1; 
  for(int iter = 0; iter < Q; iter++) { 
    cin >> N;
    cin.ignore(); 
    string line, word;
    vector<vector<int>>vec; 
    vector<string>mp(N); 
    for(int i = 0; i < N; i++) { 
      getline(cin, line); 
      stringstream ss(line); 
      ss >> word;
      mp[i] = word.substr(0, sz(word) - 1);  
      vector<int>cc;
      for(;ss >> word;) {
        if(word == "class") break;  
        cc.push_back(word == "upper" ? 1 : (word == "middle" ? 2 : 3));  
      }
      reverse(cc.begin(), cc.end()); 
      cc.push_back(i); 
      vec.push_back(cc);
    }
    sort(vec.begin(), vec.end(), [&](vector<int>a, vector<int>b) { 
      for(int i = 0; i < max(sz(b), sz(a)) - 1; i++) { 
        int va = (i >= sz(a) - 1 ? 2 : a[i]); 
        int vb = (i >= sz(b) - 1 ? 2 : b[i]); 
        if(va != vb) { 
          return va < vb; 
        }
      }
      return mp[a.back()] < mp[b.back()]; 
    }); 
    for(auto &x : vec) { 
      cout << mp[x.back()] << '\n'; 
    }
  }
  return 0; 
}
/*
  if(c[i] is the suffix of c[j] then we arrange by the name); 
*/ 