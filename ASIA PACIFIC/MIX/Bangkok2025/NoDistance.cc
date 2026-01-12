#include <vector> 
#include <iostream> 

using namespace std; 

// ... B ... A 
// ....A ... B 

int main(void) { 
 int n, a, b; 
 cin >> n >> a >> b; 
 if(n >= a + b + 2) cout << n - a - b - 2 << '\n'; 
 else cout << a + b - n << '\n'; 
 return 0; 
}