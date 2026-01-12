#include "bits/stdc++.h"

using namespace std; 

int main(void) {
 int n; 
 cin >> n; 
 map<string, int>mp, pts, ind; 
 pts["GDX"] = 5; 
 pts["SNK"] = 15; 
 pts["PRV"] = 25; 
 pts["TWO"] = 20; 
 pts["LNO"] = 15; 
 pts["LRB"] = 10; 
 string name, ero; 
 int itr = 0; 
 while(cin >> name) {
  if(name == "END") break;  
  cin >> ero; 
  mp[name] += pts[ero]; 
  if(!ind.count(name)) { 
   ind[name] = itr++; 
  }
 }
 cout << "Week " << n << '\n'; 
 vector<string>detention, explain; 
 for(auto &[u, v] : mp) { 

  if(30 < v && v <= 50) { 
   detention.push_back(u); 
  } else if(v > 50) { 
   explain.push_back(u); 
  }
 }
 sort(detention.begin(), detention.end(), [&](string a, string b) { 
  return ind[a] < ind[b]; 
 }); 
 sort(explain.begin(), explain.end(), [&](string a, string b) { 
  return ind[a] < ind[b]; 
 }); 
 cout << "Students for detention: " << '\n'; 
 for(auto &x : detention) cout << x << " "; 
 if(detention.empty()) cout << "None"; 
 cout << '\n'; 
 cout << "Parental meeting for: " << '\n';  
 if(explain.empty()) cout << "None"; 
 for(auto &x : explain) cout << x << " "; 
 cout << '\n'; 
 return 0;   
}