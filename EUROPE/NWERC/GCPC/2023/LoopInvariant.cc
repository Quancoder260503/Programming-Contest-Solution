#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 10;

int pctr[maxf], sctr[maxf];

vector<int> prefix_function(const string &s)
{
  int n = s.size();
  vector<int> pi(n);
  for (int i = 1; i < n; ++i)
  {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j])
      j = pi[j - 1];
    if (s[i] == s[j])
      ++j;
    pi[i] = j;
  }
  return pi;
}

int main(void)
{ 
    string S; 
    cin >> S; 
    auto pi = prefix_function(S); 
    reverse(S.begin(), S.end());
    auto rpi = prefix_function(S);
    reverse(S.begin(), S.end()); 
    S = " " + S; 
    int N = S.length();  
    int close = 0, open = 0; 
    for(int i = 1; i < N; i++)
    {
      open  += (S[i] == '('); 
      close += (S[i] == ')'); 
      pctr[i] = close - open;
    }
    open = close = 0; 
    for(int i = N - 1; i > 0; i--)
    {
      open += (S[i] == '(');
      close += (S[i] == ')');
      sctr[i] = open - close;
    }
    for(int i = 1; i < N - 1; i++)
    {
      if(pctr[i] >= 0 && sctr[i + 1] == pctr[i] && (pi[N - 2] < i || rpi[N - 2] < i))
      {
        string ret = S.substr(i + 1, N - i) + S.substr(1, i);
        cout << ret << '\n'; 
        return 0; 
      }
    }
    cout << "no" << '\n'; 
    return 0;
}