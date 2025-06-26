#include "bits/stdc++.h"

using namespace std; 

struct _hash {
  size_t operator()(const pair<int64_t, int64_t> &p) const {
	return p.first * 239 + p.second;
  }
};

const int maxf = 50; 
unordered_map<pair<int64_t, int64_t>, int, _hash>mp[maxf]; 

int main(void) { 
  ios_base::sync_with_stdio(false);
  cin.tie(0); 
  cout.tie(0);   
  int N; 
  int64_t dst_x, dst_y; 
  cin >> N >> dst_x >> dst_y; 
  vector<int>rx(N), ry(N);  
  for(int i = 0; i < N; i++) { 
    cin >> rx[i] >> ry[i]; 
  }
  int L = N / 2, R = N - L; 
  // Run throught every possible of subset of the first half 
  for(int mask = 0; mask < (1 << L); mask++) { 
    int64_t sum_x = 0, sum_y = 0; 
    for(int i = 0; i < L; i++) if(mask & (1 << i)) { 
      sum_x += rx[i];
      sum_y += ry[i]; 
    }
    int bit_count = __builtin_popcount(mask);
    mp[bit_count][{sum_x, sum_y}]++; 
  }
  vector<int64_t>ret(N + 1); 
  // For the second half, we are going to find the number of subsets in the first have 
  // that satisfy the constraint we set. 
  for(int mask = 0; mask < (1 << R); mask++) { 
    int64_t sum_x = 0, sum_y = 0; 
    for(int i = 0; i < R; i++) if(mask & (1 << i)) { 
      sum_x += rx[L + i];
      sum_y += ry[L + i]; 
    }
    int bit_count = __builtin_popcount(mask);
    for(int j = 0; bit_count + j <= N; j++) { 
      if(mp[j].count({dst_x - sum_x, dst_y - sum_y})) { 
        ret[j + bit_count] += mp[j][{dst_x - sum_x, dst_y - sum_y}]; 
      }
    }
  }
  for(int i = 1; i <= N; i++) { 
    cout << ret[i] << '\n'; 
  }
  return 0; 
}

/*
  Verdict : AC. 
  Time Complexity: O(2 ** (N / 2) * N).
  Problem's idea : 
  Let S[i] be the sequence that 
    sum(x[S[i]]) = destination_x,
    sum(y(S[i])) = destination_y, 
  (i.e S[i] represents the sequeces of moves that will drive us from (0, 0) to the destination points).
  For N <= 20, 
   We can backtrack to find all of these S[i] sequences which is also the answer to the problems.
  For N <= 40,
   Notice that one of the configurations in our answers can have the patterns : 
    S[1] <= S[2] <= S[3] <= ... <= 20 <= ... <= S[k] where k is len(S).
    Thus let G[i] be the sequences such that G[i] <= 20
    and H[i] be the sequences that H[i] >= 20, then we can see that 
    sum(x[G[i]]) + sum(x[H[i]]) = destination_x, 
    sum(y[G[i]]) + sum(y[G[i]]) = destination_y, 
    Then, 
    sum(x[G[i]]) = destination_x - sum(x[H[i]]), 
    sum(y[H[i]]) = destination_y - sum(y[H[i]]).
    Therefore if we know the datas of H[i], then we can find the number of sequences G that 
    satisfies this constraint.  
    Hence this reduce the time complexity to O(2 ^ (N / 2) * N) instead of an exhaustive search cost 
    O(2 ^ N).
 Some implementations details,
    I use the meet in the middle technique which requires bitmask concepts.
    We use bitmask to represent the elements in our sequence say G. 
     if mask is on at bit i (i.e mask & (1 << i)), we include x[i], y[i] in our sequence G,
     and exluced otherwise.  
*/