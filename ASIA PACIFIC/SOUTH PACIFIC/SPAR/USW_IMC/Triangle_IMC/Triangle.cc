#include <iostream> 
#include <vector> 
#include <algorithm> 

using namespace std; 

int main(void) {
 int a, b, c; 
 cin >> a >> b >> c; 
 if(a > b) swap(a, b); 
 if(b > c) swap(b, c); 
 if(a + b < c) cout << "NOT A TRIANGLE", exit(0); 
 if(a == b && b == c) cout << "EQUILATERAL", exit(0);  
 if(a == b || b == c || a == c) cout << "ISOSCELES", exit(0); 
 if(1LL * a * a + 1LL * b * b == 1LL * c * c) cout << "RIGHT ANGLED", exit(0); 
 cout << "SCALENE";
 return 0; 
}