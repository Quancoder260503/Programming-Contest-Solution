#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
 // if n odd -> the answer is simple
 int n;
 cin >> n;
 int xor_sum = 0;
 for(int i = 0, x; i < (1 << n) - 1; i++) {
  cin >> x;
  xor_sum = xor_sum ^ x ^ (i + 1);
 }
 cout << xor_sum << '\n';
 return 0;
}
