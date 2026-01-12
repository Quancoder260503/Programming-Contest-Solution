#include <iostream> 
#include <vector> 
#include <algorithm> 

#define sz(x) int(x.size())

using namespace std; 

int main(void) {
 string S, T;
 int n, m; 
 cin >> n >> m >> S >> T; 
 int ptrL, ptrR;
 for(ptrL = 0; ptrL < sz(S); ptrL++) { 
  if(S[ptrL] != T[ptrL]) break; 
 } 
 for(ptrR = 0; ptrR < sz(S); ptrR++) { 
  if(S[sz(S) - 1 - ptrR] != T[sz(T) - 1 - ptrR]) break;    
 }
 cerr << ptrL << " " << ptrR << '\n'; 
 cout << (ptrR + ptrL >= sz(S) ? "YES" : "NO"); 
 return 0; 
}