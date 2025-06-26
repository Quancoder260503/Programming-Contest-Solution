#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int block_size = 500; 
const int maxf = (1 << 21); 

int N, Q, K;
int counter[maxf]; 

struct Query { 
  int L, R, id; 
  Query(int _L, int _R, int _id) : L(_L), R(_R), id(_id) {}; 
  bool operator < (Query other) const { 
    return make_pair(L / block_size, R) < make_pair(other.L / block_size, other.R); 
  }
}; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> N >> Q >> K;  
  vector<Query>query; 
  vector<int>prefix(N + 1); 
  vector<int64_t>ret(Q); 
  for(int i = 1, x; i <= N; i++) { 
    cin >> x; 
    prefix[i] = prefix[i - 1] ^ x; 
  }
  for(int i = 0, l, r; i < Q; i++) { 
    cin >> l >> r;
    query.push_back(Query(l - 1, r, i)); 
  }
  int64_t acc = 0; 
  sort(query.begin(), query.end()); 
  int cur_L = 1, cur_R = 0;  
  for(auto cur_Q : query) { 
    while(cur_R > cur_Q.R) { 
      counter[prefix[cur_R]]--;
      acc = acc - counter[prefix[cur_R] ^ K]; 
      cur_R--;  
    }
    while(cur_L < cur_Q.L) { 
      counter[prefix[cur_L]]--;
      acc = acc - counter[prefix[cur_L] ^ K];
      cur_L++;  
    }
    while(cur_L > cur_Q.L) { 
      cur_L--; 
      acc = acc + counter[prefix[cur_L] ^ K]; 
      counter[prefix[cur_L]]++; 
    }
    while(cur_R < cur_Q.R) { 
      cur_R++; 
      acc = acc + counter[prefix[cur_R] ^ K]; 
      counter[prefix[cur_R]]++;
    }
    ret[cur_Q.id] = acc; 
  }
  for(int i = 0; i < Q; i++) { 
    cout << ret[i] << '\n'; 
  }
  return 0; 
}




