#include <iostream> 
#include <sstream> 
#include <vector>  
#include <algorithm> 
#include <set> 
#include <map> 

#define sz(x) int(x.size())

using namespace std; 

int main(void) { 
 int n; 
 cin >> n;
 cin.ignore();  
 string s;
 vector<pair<int, string>>scores;  
 map<string, int>mp; 
 for(int i = 0; i < n; i++) { 
  getline(cin, s);
  //cout << s << '\n'; 
  stringstream ss(s); 
  string word; 
  ss >> word;
  string name = word.substr(0, sz(word) - 1); 
  if(!mp.count(name)) mp[name] = 0;
  int cnt = 0;  
  while(ss >> word) {
   for(int j = 0; j + 2 < sz(word); j++) { 
     string curr = ""; 
     curr += word[j]; 
     curr += word[j + 1]; 
     curr += word[j + 2]; 
     if(curr == "Ada") mp[name]++; 
   }  
  }
  //cerr << i << " " << word << '\n'; 
 }
 for(const auto &[u, v] : mp) { 
 // cout << u << " " << v << '\n'; 
  scores.push_back({v, u}); 
 }
 sort(scores.begin(), scores.end(), [&](pair<int, string> fi, pair<int, string> sec) { 
  return fi.first == sec.first ? fi.second < sec.second : fi.first > sec.first; 
 }); 
 for(auto [u, v] : scores) { 
  cout << v << '\n'; 
 }
 return 0; 
}
