#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_set>

#define sz(x) int(x.size())


using namespace std;

const int maxn = 1e5 + 10;

int dp[maxn][4][4];

int Grundy(int num, int color_left, int color_right) {
 if(num == 1) return color_left == color_right || color_left == 3 || color_right == 3;
 int &ret = dp[num][color_left][color_right];
 if(ret != -1) return ret;
 unordered_set<int>ms;
 for(int j = 2; j < num; j++) {
  int c = 0;
  c = (Grundy(j - 1, color_left, 0) ^ Grundy(num - j, 0, color_right));
  ms.insert(c);
  c = (Grundy(j - 1, color_left, 1) ^ Grundy(num - j, 1, color_right));
  ms.insert(c);
 }
 if(color_left == 3) {
  ms.insert(Grundy(num - 1, 0, color_right));
  ms.insert(Grundy(num - 1, 1, color_right));
 }
 else ms.insert(Grundy(num - 1, color_left ^ 1, color_right));
 if(color_right == 3) {
  ms.insert(Grundy(num - 1, color_left, 0));
  ms.insert(Grundy(num - 1, color_left, 1));
 }
 else ms.insert(Grundy(num - 1, color_left, color_right ^ 1));
 ret = 0;
 while(ms.count(ret)) ret++;
 return ret;
}

int main(void) {
 // if two ends of same colour -> grundy_value = 1, otherwise = 0
 // if one of two ends is coloured -> grundy_value = len
 // if both end is uncoloured -> grundy_value = len % 2
 int n, C;
 for(cin >> C; C--; ) {
  string s;
  cin >> n >> s;
  int ret = 0;
  int last = -1;
  for(int i = 0; i < n; i++) {
   if(s[i] != '0') {
    if(last == -1) ret = ret ^ i;
    else if(s[last] == s[i] && i - last > 1) ret = ret ^ 1;
    last = i;
   }
  }
  if(last == -1) {
   ret = ret ^ (n % 2);
  } else if(last < n - 1) {
   ret = ret ^ (n - last - 1);
  }
  cout << (ret ? "1" : "2") << '\n';
 }
 return 0;
}
