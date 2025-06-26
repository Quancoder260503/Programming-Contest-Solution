#include "bits/stdc++.h"

using namespace std; 

#define sz(x) (int) x.size()
typedef pair<string, string> pss; 

vector<int> prefix_function(const string &s)
{
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

int kmp(const std::string& pat, const std::string& text) {
    auto pi = prefix_function(pat + '\0' + text);
    int ret = 0; 
    for (size_t i = pi.size() - text.size(); i < pi.size(); ++i) {
        if (pi[i] == (int) pat.size()) {
            ret++; 
        }
    }
    return ret;
}


int main(void) { 
    int n;
    string pattern; 
    vector<string>fib(27); 
    fib[0] = "0"; 
    fib[1] = "1"; 
    for(int i = 2; i < 27; i++) fib[i] = fib[i - 1] + fib[i - 2]; 
    for(int i = 0; cin >> n; i++) { 
        cin >> pattern; 
        cout << "Case " << i + 1 << ": "; 
        if(n < 27) { 
           cout << kmp(pattern, fib[n]) << '\n'; 
        }
        else { 
            int k = sz(pattern); 
            map<int, pair<int64_t, pss>>dyn; 
            dyn[25] = {kmp(pattern, fib[25]), pss(fib[25].substr(0, k - 1), fib[25].substr(sz(fib[25]) - k + 1))};
            dyn[26] = {kmp(pattern, fib[26]), pss(fib[26].substr(0, k - 1), fib[26].substr(sz(fib[26]) - k + 1))}; 
            function<pair<int64_t, pss>(int)>rec = [&](int x) { 
                if(dyn.count(x)) return dyn[x]; 
                auto f1 = rec(x - 1); 
                auto f2 = rec(x - 2); 
                int64_t ret = f1.first + f2.first + kmp(pattern, f1.second.second + f2.second.first);
                return dyn[x] = {ret, pss(f1.second.first, f2.second.second)};  
            }; 
            cout << rec(n).first << '\n'; 
        }
    }
    return 0; 
}