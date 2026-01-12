#include "bits/stdc++.h"

using namespace std; 

int arr[20]; 

set<string>ret;
int n;

int check(string s) { 
 vector<int>cnt(10); 
 for(int i = 0; i < s.size(); i++) { 
  int c = s[i] - '0';
  cnt[c]++;  
 }
 for(int i = 0; i < 10; i++) { 
  if(arr[i] == 0 && cnt[i] > 0)  return 0; 
  if(arr[i] == 1 && cnt[i] != 1) return 0;
  if(arr[i] == 2 && cnt[i]  < 2) return 0;  
 }
 return 1; 
}

void func(int idx, string curr) { 
 if(idx == n) { 
  if(check(curr)) { 
    ret.insert(curr); 
  }
  return; 
 } 
 for(int j = 0; j < 10; j++) { 
   func(idx + 1, curr + char('0' + j)); 
 }
 return; 
}

int main(void) { 
 cin >> n; 
 for(int i = 0; i < 10; i++) { 
  string s; 
  cin >> s; 
  arr[i] = (s == "many" ? 2 : (s == "one" ? 1 : 0)); 
 }
 func(0, ""); 
 cout << ret.size() << '\n'; 
 return 0; 
}