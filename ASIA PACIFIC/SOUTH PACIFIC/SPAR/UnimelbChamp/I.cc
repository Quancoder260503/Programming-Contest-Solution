#include <iostream> 
#include <sstream> 
#include <vector>  
#include <algorithm> 
#include <set> 
#include <map> 

#define sz(x) int(x.size())

using namespace std; 

vector<string>all; 
int b, t; 
vector<vector<string>>ret; 

void backtrack(int ind, vector<string>&curr) { 
 if(ind == t) { 
  ret.push_back(curr);  
  //cout << '\n'; 
  return; 
 }
 for(auto s : all) { 
   curr.push_back(s); 
   backtrack(ind + 1, curr);  
   curr.pop_back();
 }
 return; 
}

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);   
 cin >> t >> b; 
 for(int i = 0; i < (1 << b); i++) { 
  string curr; 
  for(int j = 0; j < b; j++) { 
   curr += (i >> j & 1 ? 'Y' : 'N'); 
  }
  all.push_back(curr); 
 } 
 //cout << sz(all) << '\n'; 
 vector<string>start; 
 backtrack(0, start);
 sort(ret.begin(), ret.end()); 
 for(auto &x : ret) { 
  for(int j = 0; j < sz(x); j++) { 
   cout << x[j]; 
   if(j + 1 < sz(x)) cout << " "; 
  } 
  cout << '\n'; 
 } 
 return 0; 
}


