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

std::vector<int> prefix_occurrences(const string &s)
{
    int n = s.size();
    auto pi = prefix_function(s);
    std::vector<int> res(n + 1);
    for (int i = 0; i < n; ++i)
        res[pi[i]]++;
    for (int i = n - 1; i > 0; --i)
        res[pi[i - 1]] += res[i];
    for (int i = 0; i <= n; ++i)
        res[i]++;
    return res;
}
vector<int> zfunc(const string &s)
{
    int n = (int)s.length();
    vector<int> z(n);
    z[0] = 0;
    for (int i = 1, l = 0, r = 0; i < n; ++i)
    {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}
// }}}
int main(void)
{
    string S; 
    cin >> S; 
    auto res = zfunc(S);
    for (auto it : res)  cout << it << " ";
    cout << '\n';
    auto ret = prefix_function(S); 
    for(auto it : ret)   cout << it << " "; 
    cout << '\n'; 
    return 0; 
}