#include "bits/stdc++.h"
using namespace std;
template <typename Container>
std::vector<int> prefix_function(const Container &s)
{
    int n = s.size();
    std::vector<int> pi(n);
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
std::vector<int> kmp(const std::string &pat, const std::string &text)
{
    auto pi = prefix_function(pat + '\0' + text);
    std::vector<int> res;
    for (size_t i = pi.size() - text.size(); i < pi.size(); ++i)
    {
            res.push_back(pi[i]);
    }
    return res;
}
string s;
signed main(void)
{
    cin >> s;  
    string sa = s, sb = s; 
    string target; 
    int N = s.length();
    for(int i = 0; i < 2 * N + 1; i++)
    {
         if(i & 1) target += s[(i - 1) / 2]; 
         else target += '*'; 
    }
    for(int i = 0; i < N; i++)
    {
        if(i & 1) sa[i] = '*';
        else sb[i] = '*'; 
    }
    vector<int>ma = kmp(sa, target);
    vector<int>mb = kmp(sb, target); 
    int ans = 0; 
    for(int i = 0; i < ma.size(); i++)
    {
        ans = max(ans, ma[i]); 
    } 
    for(int i = 0; i < mb.size(); i++)
    {
        ans = max(ans, mb[i]); 
    }
    cout << ans << '\n';
    return 0; 
}