#include <bits/stdc++.h> 
#include <iostream>
 
using namespace std; 
 
int main() {
  int N, f, s; 
  cin >> N >> f >> s;
  --f, --s; 
  int n = (1 << N); 
  vector<array<int, 2>>a(n); 
  for(int i = 0; i < n; i++) { 
   cin >> a[i][0];
   a[i][1] = i; 
  } 
  int vf = a[f][0]; 
  int vs = a[s][0]; 
  sort(a.begin(), a.end()); 
  int gA = 0, gB = 0;  
  for(int i = 0; i < n; i++) { 
   if(a[i][1] == f || a[i][1] == s) continue; 
   if(vf < vs) { 
    if(a[i][0] < vf && gA < n / 2 - 1) gA++; 
    else if(a[i][0] < vs) gB++; 
   } else {
    if(a[i][0] < vs && gB < n / 2 - 1) gB++; 
    else if(a[i][0] < vf) gA++; 
   } 
  }
  cout << (gA == n / 2 - 1 && gB == n / 2 - 1 ? "YES" : "NO") << '\n'; 
  return 0;
}