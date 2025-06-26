#include "bits/stdc++.h"
using namespace std;
const int N = 5e5 + 10;
#define double long double
const long long INF = 1e14 + 1;
typedef pair<int,int> pii;
int n,q,k,a,b;
const double eps = 1e-9; 
int bit[N + 1];
int dp[N + 1]; 
signed main(){
      scanf("%d%d",&a,&b);
      vector<int>fizz;
      vector<int>buzz; 
      vector<int>fizzbuzz;
      for(int i = a; i <= b; i++){ 
           string s; cin >> s;  
           if(s == "Fizz") fizz.push_back(i);
           if(s == "Buzz") buzz.push_back(i); 
           if(s == "FizzBuzz") fizzbuzz.push_back(i);
      }
      int gcdfizz, gcdbuzz, gcdfizzbuzz;
      gcdfizz = gcdbuzz = gcdfizzbuzz = b + 1;
      if(fizz.size()){
         gcdfizz = fizz[0]; 
         for(int i = 1; i < fizz.size(); i++) gcdfizz = __gcd(gcdfizz, fizz[i]);
      }
      if(buzz.size()){
         gcdbuzz = buzz[0];
         for(int i = 1; i < buzz.size(); i++) gcdbuzz = __gcd(gcdbuzz, buzz[i]); 
      }
      if(fizzbuzz.size()){
         gcdfizzbuzz = fizzbuzz[0]; 
         for(int i = 1; i < fizzbuzz.size(); i++) gcdfizzbuzz = __gcd(gcdfizzbuzz, fizzbuzz[i]);
      }
      if(gcdfizzbuzz == b + 1){
            cout << gcdfizz << ' ' << gcdbuzz << endl; 
            return 0;
      }
      cout << (gcdfizz == b + 1 ? gcdfizzbuzz : __gcd(gcdfizzbuzz,gcdfizz)) << ' ';
      cout << (gcdbuzz == b + 1 ? gcdfizzbuzz : __gcd(gcdfizzbuzz,gcdbuzz)) << '\n'; 
      return 0;
}