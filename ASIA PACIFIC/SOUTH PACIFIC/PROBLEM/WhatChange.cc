#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
 int n; 
 cin >> n; 
 int sum = 0;  
 double x; 
 double cc = 0; 
 for(int i = 0; i < n; i++) { 
  cin >> x; 
  cc += x; 
 }
 cin >> x; 
 int total = int(x * 100); 
 cout << fixed << setprecision(2) ; 
 cout << "Total price: $" << cc << '\n'; 
 sum = int(cc * 100); 
 int last_d = sum % 10; 
 if(last_d < 5) { 
  sum = sum - last_d; 
 } else { 
  sum = sum - last_d + 10; 
 }
 cout << "Rounded price: $" << 1.0 * sum / 100 << '\n'; 
 total = total - sum; 
 cout << "Change: $" << 1.0 * total / 100 << '\n'; 
 return 0; 
}