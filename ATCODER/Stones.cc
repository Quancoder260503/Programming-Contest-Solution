#include "bits/stdc++.h"

using namespace std;

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M; 
  cin >> N >> M; 
  vector<int>dyn(M + 1), a(N); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  } 
  dyn[0] = false; 
  for(int i = 1; i <= M; i++) { 
    for(int j = 0; j < N; j++) if(i >= a[j]) { 
      dyn[i] |= true ^ dyn[i - a[j]]; 
    }
  }
  cout << (dyn[M] ? "First" : "Second") << '\n'; 
  return 0; 
}

/*
  dyn[i] = {with i stones in the stack, can the player make the first move wins the game ? }
*/