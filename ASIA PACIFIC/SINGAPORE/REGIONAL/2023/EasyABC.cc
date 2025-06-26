#include <bits/stdc++.h>
 
using namespace std; 
 
int main() {  
 vector<string>s(3); 
 for(int i = 0; i < 3; i++) { 
  cin >> s[i];   
 } 
 string ret = "CCC";
 const int dx[8] = {0, 0, -1, 1, -1, 1, -1, 1}; 
 const int dy[8] = {-1, 1, 0, 0, -1, 1, 1, -1}; 
 for(int i = 0; i < 3; i++) { 
  for(int j = 0; j < 3; j++) {
   for(int dir = 0; dir < 8; dir++) { 
    for(int dir2 = 0; dir2 < 8; dir2++) { 
     if(dir == dir2) continue; 
     int ni = i + dx[dir], nj = j + dy[dir]; 
     int nii = i + dx[dir2], njj = j + dy[dir2]; 
     if(0 <= ni && ni < 3 && 0 <= nj && nj < 3 && 0 <= nii && nii < 3 && 0 <= njj && njj < 3) { 
       string curr = ""; 
       curr += s[ni][nj];
       curr += s[i][j]; 
       curr += s[nii][njj]; 
       ret = min(ret, curr); 
     } 
    } 
   } 
  } 
 } 
 cout << ret << '\n'; 
 return 0; 
}