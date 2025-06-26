#include "bits/stdc++.h"

using namespace std; 

#define sz(x) (int) x.size()

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

int kmp(const string &pat, const string &text)
{
    auto pi = prefix_function(pat + '\0' + text);
    int ret = 0; 
    for (size_t i = pi.size() - text.size(); i < pi.size(); ++i)
    {
        if (pi[i] == (int)pat.size())
        {
            ret++;  
        }
    }
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    string s, t;
    int k;  
    cin >> k >> s >> t; 
    for(int i = 1; i <= k + 1; i++){
        string cc;
        for(int j = 0; j < sz(s); j += i) {
            cc += s[j]; 
        } 
        cout << (sz(t) <= sz(cc) ? kmp(t, cc) : 0) << '\n'; 
    }
    return 0;
}