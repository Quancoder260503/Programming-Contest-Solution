#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <cassert>
#include <utility>
#include <set>
#include <numeric>

using namespace std;

int calc(int x) {
 if(x == 0) return 0;
 int ans;
 for(ans = 0; x % 2 == 0; x = x / 2) ans++;
 return ans;
}

struct Card {
 int r, c, a, b, p;
 pair<int, bool>card;
 Card(int r = 0, int c = 0, int a = 0, int b = 0, int p = 0) : r(r), c(c), a(a), b(b), p(p) {
  card.first = gcd(a, b);
  card.second = calc(a) == calc(b);
 }
 bool onGrid(pair<int, bool>&p) {
  if(p.first == 0) return r == 0 && c == 0;
  if(r % p.first || c % p.first) return false;
  if(!p.second) return true;
  return (r / p.first) % 2 == (c / p.first) % 2;
 }
};

pair<int, bool> operator + (const pair<int, bool>&pa, const pair<int, bool>&pb) {
 int ga = pa.first * (pa.second ? 2 : 1);
 int gb = pb.first * (pb.second ? 2 : 1);
 int g = gcd(ga, gb);
 int ra = pa.first % g, rb = pb.first % g;
 if(ra == 0) ra += g;
 if(rb == 0) rb += g;
 int r = min(ra, rb);
 return {r, r != g};
}

map<pair<int, bool>, int64_t>dp;

int64_t dfs(vector<Card>&cards, pair<int, bool>&curr, Card &des) {
 if(des.onGrid(curr)) return 0;
 if(dp.count(curr)) return dp[curr];
 int64_t ret = -1;
 for(auto &card : cards) {
  //cerr << card.r << " " << card.c << '\n';
  if(card.onGrid(curr)) {
   //cout << card.r << " " << card.c << '\n';
   pair<int, bool> now = card.card + curr;
   if(now == curr) continue;
   int64_t dist = dfs(cards, now, des);
   if(dist == -1) continue;
   if(ret == -1 || ret > dist + card.p) {
    //cout << card.p << '\n';
    ret = dist + card.p;
   }
  }
 }
 return dp[curr] = ret;
}

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 int n;
 cin >> n;
 vector<Card>Tarot;
 for(int i = 0, r, c, a, b, p; i < n; i++) {
  cin >> r >> c >> a >> b >> p;
  //cout << r << " " << c << " " << a << " " << b << " " << p << '\n';
  Tarot.emplace_back(r, c, a, b, p);
 }
 Card des;
 des.r = abs(Tarot[0].r);
 des.c = abs(Tarot[0].c);
 for(int i = n - 1; i >= 0; i--) {
  Tarot[i].c = abs(Tarot[0].c - Tarot[i].c);
  Tarot[i].r = abs(Tarot[0].r - Tarot[i].r);
  //cout << Tarot[i].c << " " << Tarot[i].r << '\n';
 }
 pair<int, bool> src = {0, false};
 cout << dfs(Tarot, src, des) << '\n';
 return 0;
}
