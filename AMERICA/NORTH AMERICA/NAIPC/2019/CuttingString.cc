#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <numeric>
#include <utility>

using namespace std;

#define sz(x) int(x.size())

const int oo = 1e9;

struct SuffixArray {
 vector<int>sa, lcp, rsa;
 SuffixArray(string s, int lim = 256) {
  s.push_back(0);
  int n = sz(s), k = 0, a, b;
  vector<int>x(s.begin(), s.end()), y(n), ws(max(n, lim));
  sa = lcp = y;
  iota(sa.begin(), sa.end(), 0);
  for(int j = 0, p = 0; p <  n; j = max(1, j * 2), lim = p) {
   p = j;
   iota(y.begin(), y.end(), n - j);
   for(int i = 0; i < n; i++) if(sa[i] >= j) {
    y[p++] = sa[i] - j;
   }
   fill(ws.begin(), ws.end(), 0);
   for(int i = 0; i < n; i++) {
    ws[x[i]]++;
   }
   for(int i = 1; i < lim; i++) ws[i] += ws[i - 1];
   for(int i = n; i--; ) sa[--ws[x[y[i]]]] = y[i];
   swap(x, y);
   p = 1, x[sa[0]] = 0;
   for(int i = 1; i < n; i++) {
    a = sa[i - 1], b = sa[i];
    x[b] = (y[a] == y[b] && y[a + j] == y[b + j] ? p - 1 : p++);
   }
  }
  for(int i = 0, j; i < n - 1; lcp[x[i++]] = k) {
   for(k && k--, j = sa[x[i] - 1]; s[i + k] == s[j + k]; k++);
  }
  rsa = vector<int>(n);
  for(int i = 0; i < sz(sa); i++) if(sa[i] < n){
   rsa[sa[i]] = i;
  }
  //for(int i = 0; i < n; i++) cerr << i << " " << sa[i] << '\n';
 }
};

int n, k, C;
string s;

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 for(cin >> C; C--; ) {
  cin >> k >> s;
  n = sz(s);
  vector<int>cnt(26);
  for(int i = 0; i < n; i++) {
   cnt[s[i] - 'a']++;
  }
  string ans;
  for(char c = 'z'; c >= 'a' && k > 0 && n > 0; c--) {
   if(cnt[c - 'a'] == 0) continue;
   vector<pair<int, int>>chunks;
   int st = 0;
   while(st < n && s[st] == c) ans += c, st++;
   if(st >= n) break;
   for(int i = st; i < n; i++) if(s[i] == c) {
    int en = i;
    while(en < n && s[en] == s[i]) en++;
    chunks.emplace_back(i, en);
    i = en - 1;
   }
   sort(chunks.begin(), chunks.end(), [&](pair<int, int>&a, pair<int, int>&b) {
    return a.second - a.first > b.second - b.first;
   });
   if(sz(chunks) <= k) {
    int last_position = st;
    for(const auto &x : chunks) {
     last_position = max(last_position, x.second);
     for(int j = x.first; j < x.second; j++) ans += c;
    }
    k -= sz(chunks);
    if(k == 0 || c == 'a') {
     for(int i = last_position; i < n; i++) {
      ans += s[i];
     }
     break;
    }
    for(int j = last_position; j < n; j++) {
     s[j - last_position] = s[j];
    }
    n = n - last_position;
   } else {
    SuffixArray sa(s.substr(0, n));
    vector<pair<int, int>>new_chunks;
    int last_position = st, num_cand = 0;
    int length = chunks[k - 1].second - chunks[k - 1].first; // k-th largest, larger then k -> don't care
    for(int i = 0; i < k; i++) {
     for(int j = chunks[i].first; j < chunks[i].second; j++) ans += c;
     if(chunks[i].second - chunks[i].first == length) {
      num_cand++;
     } else {
      last_position = max(last_position, chunks[i].second);
     }
    }
    for(auto &x : chunks) if(x.second - x.first == length) {
     new_chunks.push_back(x);
    }
    sort(new_chunks.begin(), new_chunks.end());
    pair<int, int>res = {-oo, -oo};
    for(int i = num_cand - 1; i < sz(new_chunks); i++) {
     int pos = max(last_position, new_chunks[i].second);
     res = max(res, {sa.rsa[pos], pos});
    }
    last_position = res.second;
    for(int j = last_position; j < n; j++) ans += s[j];
    break;
   }
  }
  cout << ans << '\n';
 }
 return 0;
}
