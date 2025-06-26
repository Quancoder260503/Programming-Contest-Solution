#include "bits/stdc++.h"

using namespace std; 

const int maxf = 100005; 

int N, dyn[maxf], vis[maxf], last[maxf]; 
vector<int>prime[maxf]; 

void init(void) {
  for(int i = 2; i < maxf; i++) { 
    if(vis[i]) continue; 
    for(int j = i; j < maxf; j += i) { 
      prime[j].push_back(i); 
      vis[j] = true; 
    }
  }
  return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  init(); 
  cin >> N; 
  memset(last, -1, sizeof(last)); 
  fill(dyn, dyn + maxf, 1); 
  for(int i = 0, x; i < N; i++) { 
    cin >> x; 
    for(auto v : prime[x]) { 
      dyn[i] = max(dyn[i], 1 + (last[v] == -1 ? 0 : dyn[last[v]])); 
      last[v] = i;         
    }
  } 
  cout << *max_element(dyn, dyn + maxf) << '\n'; 
  return 0; 
}
