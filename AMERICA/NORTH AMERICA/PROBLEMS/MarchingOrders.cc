#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
#define sz(x) int(x.size())

const int64_t M = 1e12; 

pair<int64_t, int64_t> crt(int64_t a1, int64_t m1, int64_t a2, int64_t m2) {
  if (m1 < m2) swap(m1, m2), swap(a1, a2);
  if (m1 > M) {
    if (a1 % m2 == a2) return {a1, m1};
    return {-1, -1};
  }
  int turn = 0; 
  while (a1 % m2 != a2) { 
   a1 += m1;
   turn++; 
   if(turn > 100) { 
    cout << "NO\n"; 
    exit(0); 
   }
  } 
  auto g = gcd(m1, m2);
  if (m1 / g > M / m2) return {a1 > M ? M + 1 : a1, M + 1};
  return {a1, m1 / g * m2};
}
int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N;
  string S;
  cin >> N >> S;
  string alphabet = "";
  for (int i = 0; i < N; i++) {
    alphabet = alphabet + char('A' + i);
  }
  pair<int64_t, int64_t> ret = {0, 1}; 
  for (int i = 0; i < N; i++) {
    int pos = alphabet.find(S[i]);
    ret = crt(ret.first, ret.second, pos, N - i); 
    string new_alphabet = "";
    for (int j = 0; j < sz(alphabet); j++) {
      if (j == pos) continue;
      new_alphabet += alphabet[j];
    }
    alphabet.swap(new_alphabet);
  }
  cout << "YES\n"; 
  cout << ret.first << '\n'; 
  return 0;
}