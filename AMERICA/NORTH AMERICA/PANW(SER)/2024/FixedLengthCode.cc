#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

struct suffix_array {
  suffix_array(const char *S) : N(strlen(S)) {
    vector<int> V;
    for (int i = 0; i < N; i++) V.push_back(S[i]);
    init(V);
  }

  suffix_array(const vector<int> &VV) : N(VV.size()) {
    vector<int> V(VV);
    init(V);
  }

  /* Get longest common prefix between two suffix-indicies. */
  int lcp(int si, int sj) {
    if (sj < si) swap(si, sj);
    if (si == sj) return N - SA[si];
    int len = sj - si;
    int buck = 31 - __builtin_clz(len);
    return min(LCP_MRQ[buck][si], LCP_MRQ[buck][sj - (1 << buck)]);
  }

  int N;
  vector<int> SA;
  vector<int> RA;

 private:
  void compress(vector<int> &V, vector<int> &C) {
    copy(V.begin(), V.end(), C.begin());
    sort(C.begin(), C.end());
    auto cend = unique(C.begin(), C.end());
    for (int i = 0; i < N; i++) {
      V[i] = lower_bound(C.begin(), cend, V[i]) - C.begin() + 1;
    }
    V.push_back(0);
    C.push_back(0);
  }

  void compute_sa(vector<int> &V, vector<int> &C) {
    vector<int> T(N + 1);
    for (int i = 0; i <= N; i++) SA.push_back(i);
    for (int ski = 0; V[SA[N]] < N; ski = ski ? ski << 1 : 1) {
      fill(C.begin(), C.end(), 0);
      for (int i = 0; i < ski; i++) T[i] = N - i;
      for (int i = 0, p = ski; i <= N; i++)
        if (SA[i] >= ski) T[p++] = SA[i] - ski;
      for (int i = 0; i <= N; i++) C[V[i]]++;
      for (int i = 1; i <= N; i++) C[i] += C[i - 1];
      for (int i = N; i >= 0; i--) SA[--C[V[T[i]]]] = T[i];

      T[SA[0]] = 0;
      for (int j = 1; j <= N; j++) {
        int a = SA[j];
        int b = SA[j - 1];
        T[a] = T[b] + (a + ski >= N || b + ski >= N || V[a] != V[b] ||
                       V[a + ski] != V[b + ski]);
      }
      V.swap(T);
    }
  }

  void compute_lcp(const vector<int> &OV) {
    LCP_MRQ.push_back(vector<int>(N));
    int len = 0;
    for (int i = 0; i < N; i++, len = max(0, len - 1)) {
      int si = RA[i];
      int j = SA[si - 1];
      for (; i + len < N && j + len < N && OV[i + len] == OV[j + len]; len++);
      LCP_MRQ[0][si - 1] = len;
    }
    for (int i = 1; 1 << i <= N; i++) {
      LCP_MRQ.push_back(vector<int>());
      const vector<int> &plcp = LCP_MRQ[i - 1];
      for (int j = 0; j + (1 << i) <= N; j++) {
        LCP_MRQ[i].push_back(min(plcp[j], plcp[j + (1 << (i - 1))]));
      }
    }
  }

  void init(vector<int> &V) {
    vector<int> OV(V);
    vector<int> C(N);
    compress(V, C);
    compute_sa(V, C);
    RA.resize(N + 1);
    for (int i = 0; i <= N; i++) RA[SA[i]] = i;
    compute_lcp(OV);
    return;
  }

  vector<vector<int>> LCP_MRQ;
}; 

int main(void) {
 int N; 
 cin >> N; 
 vector<int>a(N); 
 string s; 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 for(int i = 0; i + 1 < 2 * N; i++) { 
  s += (a[i % N] < a[(i + 1) % N] ? 'a' : 'b'); 
 } 
 suffix_array suffix(s.c_str()); 
 vector<int>coord; 
 for(int i = 0; i < N; i++) { 
  coord.push_back(suffix.RA[i]); 
//  cout << suffix.RA[i] << '\n'; 
 }
 sort(coord.begin(), coord.end()); 
 for(int i = 0; i < N; i++) { 
  int pos = lower_bound(coord.begin(), coord.end(), suffix.RA[i]) - coord.begin(); 
  int c = 0; 
  if(pos) c = max(c, suffix.lcp(coord[pos - 1], coord[pos]));
  if(pos + 1 < sz(coord)) c = max(c, suffix.lcp(coord[pos], coord[pos + 1])); 
  cout << (c >= N ? -1 : c + 1) << '\n';  
 }
 //cout << s << '\n'; 
 return 0; 
}
/**
 * 1 8 3 4 2 1 8 3 4 2 
    a b a b b a b a b 
    0 1 2 3 4 5 6 7 8 9 
    
    "
  9:  
  7:  ab
  5:  abab
  0:  ababbabab
  2:  abbabab
  8:  b
  6:  bab
  4:  babab
  1:  babbabab
  3:  bbabab

 */