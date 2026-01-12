#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

double f(string s) { 
  if(s[0] != '(') { 
    return stod(s); 
  }
  string curr = s.substr(1, sz(s) - 1); 
  int pos; 
  for(pos = 0; curr[pos] != ' '; pos++); 
  double prob = stod(curr.substr(0, pos)); 
// cout << prob << " " << curr.substr(0, pos) << '\n'; 
  int sum = 0, nxt;  
  for(nxt = pos + 1; nxt < sz(curr); nxt++) { 
   if(curr[nxt] == '(') sum++; 
   if(curr[nxt] == ')') sum--; 
   if(curr[nxt] == ' ' && sum == 0) break; 
  }
  string first  = curr.substr(pos + 1, nxt - pos); 
  string second = curr.substr(nxt + 1);
  double x = f(curr.substr(pos + 1, nxt - pos));
  double y = f(curr.substr(nxt + 1)); 
  return prob * (x + y) + (1. - prob) * (x - y); 
}

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 string S; 
 while(true) { 
  getline(cin, S); 
  if(S == "()") break;
  cout << fixed << setprecision(2) << f(S) << '\n'; 
 }  
 return 0; 
}