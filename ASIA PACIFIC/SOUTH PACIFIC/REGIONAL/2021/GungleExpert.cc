#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <set>

#define sz(x) int(x.size())

using namespace std;

const int oo = 1e8;

pair<int, string>dp[105][2];
string s;
set<char>vowels{'A', 'I', 'E', 'O', 'U'};

pair<int, string> memo(int pos, int state) {
 if(pos == -1) return state > 0 ? make_pair(oo, "") : make_pair(0, "");
 auto &ret = dp[pos][state];
 if(ret.first != -1) return ret;
 ret.first = oo;
 if(state > 0) {
  auto next = memo(pos - 1, 0);
  int c =  !(s[pos] == 'L' || s[pos] == 'G');
  ret = min(ret, {next.first + c, next.second + (c ? 'G' : s[pos])});
 } else {
  auto next_0 = memo(pos - 1, 0);
  auto next_1 = memo(pos - 1, 1);
  if(vowels.count(s[pos])) {
   ret = min(ret, {1 + next_0.first, next_0.second + 'B'});  // change to something else
   ret = min(ret, {next_1.first ,  next_1.second + s[pos]});
  } else {
   ret = min(ret, {next_0.first , next_0.second + s[pos]});
   ret = min(ret, {1 + next_1.first, next_1.second + 'A'});
  }
 }
 return ret;
}


int main(void) {
 cin >> s;
 for(int i = 0; i < 105; i++) {
  dp[i][0].first = dp[i][1].first = -1;
 }
 cout << memo(sz(s) - 1, 0).second << '\n';
 return 0;
}
