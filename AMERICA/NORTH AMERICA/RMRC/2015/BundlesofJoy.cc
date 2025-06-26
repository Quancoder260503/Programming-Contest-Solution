#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 250;
const int oo = INT_MAX;

bitset<100> bundle[maxf];
int N, M, Q, price[maxf], dyn[maxf];

int memo(int goal) {
  if (dyn[goal] >= 0) return dyn[goal];
  dyn[goal] = price[goal];
  int largest[maxf]; 
  memset(largest, -1, sizeof(largest));
  for (int i = 0; i < M; i++) {
    if (i == goal) continue;
    if (bundle[i] == bundle[goal]) {
      dyn[goal] = min(dyn[goal], price[i]);
      continue;
    }
    if ((bundle[i] & ~bundle[goal]).any()) continue;
    for (int j = 0; j < N; j++) {
      if (!bundle[i].test(j)) continue;
      if (largest[j] < 0 || bundle[largest[j]].count() < bundle[i].count()) {
        largest[j] = i;
      }
    }
  }
  int sum = 0;
  bitset<100> buy;
  for (int i = 0; i < N; i++) {
    if (largest[i] < 0) continue;
    if ((bundle[largest[i]] & buy).any()) continue;
    buy |= bundle[largest[i]];
    sum += memo(largest[i]);
  }
  if (bundle[goal] == buy) {
    dyn[goal] = min(dyn[goal], sum);
  }
  return dyn[goal];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> Q;
  for (int iter = 0; iter < Q; iter++) {
    cin >> N >> M;
    for (int i = 0, x; i < M; i++) {
      bundle[i].reset();
      cin >> price[i] >> x;
      for (int j = 0, y; j < x; j++) {
        cin >> y;
        bundle[i].set(y - 1);
      }
    }
    bundle[M].reset();
    for (int i = 0; i < N; i++) {
      bundle[M].set(i);
    }
    price[M++] = oo;
    fill(dyn, dyn + M, -1);
    cout << memo(M - 1) << '\n';
  }
  return 0;
}
