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
        if (pi[i] == (int)pat.size())
        {
            res.push_back(i - 2 * pat.size());
        }
    }
    return res;
}
string s;
signed main(void)
{
    cin >> s;
    int N = s.length();
    string text = s + s;
    reverse(s.begin(), s.end()); 
    vector<int>failure = kmp(s, text);
    puts(failure.size() ? "1" : "0"); 
    return 0;
}
// rev(T) is also 