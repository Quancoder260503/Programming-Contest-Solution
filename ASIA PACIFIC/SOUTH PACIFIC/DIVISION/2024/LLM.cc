#include <bits/stdc++.h>

using namespace std; 

#define sz(x) int(x.size())

int main() {
  string s; 
  int n; 
  cin >> s >> n; 
  vector<string>word(n); 
  vector<vector<int>>occ(26, vector<int>(27));
  vector<int>freq(26); 
  for(int i = 0; i < n; i++) {
   cin >> word[i]; 
   for(int j = 0; j + 1 < sz(word[i]); j++) { 
    occ[word[i][j] - 'a'][word[i][j + 1] - 'a']++; 
    freq[word[i][j] - 'a']++; 
   } 
   freq[word[i].back() - 'a']++; 
   occ[word[i].back() - 'a'][26]++; 
  }
  double Prob = 1.0; 
  for(int i = 1; i < sz(s); i++) {
    if(freq[s[i - 1] - 'a'] == 0) { 
      Prob = 0.; 
      break; 
    } 
    Prob = Prob * occ[s[i - 1] - 'a'][s[i] - 'a'] / freq[s[i - 1] - 'a']; 
  } 
  if(freq[s.back() - 'a'] > 0) { 
    Prob = Prob * occ[s.back() - 'a'][26] / freq[s.back() - 'a'];
  }
  cout << fixed << setprecision(12) << Prob << '\n'; 
  return 0;
}