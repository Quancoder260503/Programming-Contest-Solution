#include "bits/stdc++.h"

using namespace std;

#define double long double
#define sz(x) int(x.size())

double solve (vector<vector<double>> eqs) {
  int eq_cnt = eqs.size();
  for (int i = eq_cnt-1; i > 0; --i) {
    for (int j = 0; j < i; ++j) {
      if (eqs[j][i] == 0) continue;
      assert(eqs[i][i] != 0);
      double coeff = -eqs[j][i] / eqs[i][i];
      for (int k = 0; k < eq_cnt + 1; ++k) { 
        eqs[j][k] += coeff * eqs[i][k];
      }
      eqs[j][i] = 0;
    }
  }

  return eqs[0][eq_cnt] / eqs[0][0];
}

int ends_with(const string &a, const string &b) { 
  // check if b is the suffix of a
  if(sz(b) > sz(a)) return false; 
  for(int ptr = sz(a) - 1, ptr2 = sz(b) - 1; ptr2 >= 0; ptr--, ptr2--) { 
    if(a[ptr] == b[ptr2]) continue; 
    return false; 
  }
  return true; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N, M; 
  cin >> N >> M; 
  vector<string>vec, word(N);
  for(int i = 0; i < N; i++) { 
    cin >> word[i]; 
    for(int j = 0; j <= M; j++) { 
      vec.push_back(word[i].substr(0, j)); 
    }
  }
  vector<char>choice = {'T', 'H'}; 
  sort(vec.begin(), vec.end()); 
  vec.erase(unique(vec.begin(), vec.end()), vec.end()); 
  N = sz(vec); 
  vector<vector<double>>_expected(N, vector<double>(N + 1)); 
  for(int i = 0; i < N; i++) { 
    int flag = true; 
    _expected[i][i] = 1.0; 
    for(int j = 0; j < sz(word); j++) { 
      if(word[j] == vec[i]) { 
        flag = false; 
        break; 
      }
    }
    if(!flag) {
      continue; 
    } 
    for(auto c : choice) { 
      string nxt_state = vec[i] + c; 
      string suffix; 
      int pos = 0; 
      for(int j = 0; j < N; j++) { 
        if(ends_with(nxt_state, vec[j]) && sz(suffix) < sz(vec[j])) { 
          suffix = vec[j]; 
          pos = j; 
        }
      } 
      _expected[i][pos] += -0.5; 
    }
    _expected[i][N] = 1.0;
  }
  /* 
  for(int i = 0; i < _expected.size(); i++) { 
    for(int j = 0; j < _expected[0].size(); j++) { 
      cout << _expected[i][j] << " "; 
    }
    cout << '\n'; 
  }
  */
  cout << fixed << setprecision(5) << solve(_expected) << '\n'; 
  return 0; 
}