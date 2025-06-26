#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
string a,b;
int pib[N + 1]; 
vector<int>kmp(string &s){
     int n = s.length();
     vector<int>pin(n); 
     for(int i = 1, j = 0; i < n; i++){
          while(j > 0 && s[i] != s[j]) j = pin[j - 1];
          if(s[i] == s[j]) j++; 
          pin[i] = j; 
     }
     return pin; 
}
int main(){
     cin >> a >> b;
     string s = b + '?' + a;
     vector<int>pia = kmp(s);
     int ans = 0; 
     for(int i = 0; i < pia.size(); i++){ 
           if(pia[i] == b.length()) ans++; 
     }
     printf("%d\n",ans); 
     return 0; 
} 