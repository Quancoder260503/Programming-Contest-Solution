#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_set>

#define sz(x) int(x.size())


using namespace std;

const int maxn = 1e5 + 10;

int dp[maxn][4][4];

int Grundy(int num, int left_type, int right_type) {
 if(num == 0) return 0; 
 if(num == 1) return (left_type != 3) || (right_type != 3);
 int &ret = dp[num][left_type][right_type];
 if(ret != -1) return ret;
 unordered_set<int>ms;
 if(left_type  != 3) ms.insert(Grundy(num - 1, 3, right_type));
 if(right_type != 3) ms.insert(Grundy(num - 1, left_type, 3));
 ms.insert(Grundy(num - 2, 1, right_type));
 ms.insert(Grundy(num - 2, 2, right_type)); 
 ms.insert(Grundy(num - 2, left_type, 1));
 ms.insert(Grundy(num - 2, left_type, 2));   
 for(int j = 2; j < num; j++) {
  ms.insert((Grundy(j - 2, left_type, 1) ^ Grundy(num - j, 3, right_type)));
  ms.insert((Grundy(j - 2, left_type, 2) ^ Grundy(num - j, 3, right_type)));
  ms.insert((Grundy(j - 1, left_type, 3) ^ Grundy(num - j - 1, 1, right_type)));
  ms.insert((Grundy(j - 1, left_type, 3) ^ Grundy(num - j - 1, 2, right_type)));
 }
 ret = 0;
 while(ms.count(ret)) ret++;
//  cout << num << " " << ret << '\n'; 
 return ret;
}

int main(void) {
 int n, C;
 memset(dp, -1, sizeof(dp));
 for(cin >> C; C--; ) {
  cin >> n;
  cout << (Grundy(n, 3, 3) ? "X" : "Y") << '\n';
 }
 return 0;
}

