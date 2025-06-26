#include "bits/stdc++.h"

using namespace std;

const int maxf = 2e5 + 10;

int N, K, a[maxf], cur_L = 1, cur_R = 0; 
int64_t dyn[30][maxf], counter[maxf], acc = 0; 

int64_t cost(int L, int R) { 
  while(cur_R > R) { 
    counter[a[cur_R]]--;
    acc = acc - counter[a[cur_R]]; 
    cur_R--;  
  }
  while(cur_L < L) { 
    counter[a[cur_L]]--;
    acc = acc - counter[a[cur_L]];
    cur_L++;  
  }
  while(cur_L > L) { 
    cur_L--; 
    acc = acc + counter[a[cur_L]]; 
    counter[a[cur_L]]++; 
  }
  while(cur_R < R) { 
    cur_R++; 
    acc = acc + counter[a[cur_R]]; 
    counter[a[cur_R]]++;
  }
  return acc;
}

void dnq(int L, int R, int optl, int optr, int now) {
  if (L > R) return;
  int mid = (L + R) / 2;
  pair<int64_t, int> best = {INT64_MAX, -1};
  for (int i = optl; i <= min(mid, optr); i++) {
    best = min(best, {dyn[now - 1][i - 1] + cost(i, mid), i});
  }
  dyn[now][mid] = best.first;
  int opt = best.second;
  dnq(L, mid - 1, optl, opt, now);
  dnq(mid + 1, R, opt, optr, now);
  return;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0); 
  cout.tie(0);
  cin >> N >> K;
  for(int i = 1; i <= N; i++) { 
    cin >> a[i]; 
  }
  int state = 0; 
  for(int i = 1; i <= N; i++) { 
    dyn[1][i] = cost(1, i); 
  }
  for(int i = 2; i <= K; i++) {
    dnq(1, N, 1, N, i);  
  }
  cout << dyn[K][N] << '\n'; 
  return 0;
}