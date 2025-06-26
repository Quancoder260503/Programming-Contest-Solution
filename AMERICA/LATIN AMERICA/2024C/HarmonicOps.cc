#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

vector<int> prefix_function(const string &s) {
    int n = sz(s);
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

int kmp(const string& pat, const string& text) {
    auto pi = prefix_function(pat + '\0' + text);
    vector<int> res;
    for (size_t i = sz(pi) - sz(text); i < sz(pi); ++i) {
        if (pi[i] == sz(pat)) {
            return i - 2 * sz(pat); 
        }
    }
    return -1;
}

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    string S; 
    cin >> S; 
    auto failure = prefix_function(S);
    int n = sz(S); 
    int c = (n % (n - failure[n - 1]) != 0 ? 1 : n / (n - failure[n - 1])); 
    c = n / c; 
    string T = S.substr(0, c);
    reverse(T.begin(), T.end()); 
    string R = T;  
    reverse(T.begin(), T.end()); 
    int rev = kmp(R, T + T);
    int m; 
    cin >> m;  
    vector<map<int, int>>dyn(2); 
    int64_t ret = 0, sum = 0;  
    dyn[0][0]++; 
    for(int i = 0, state = 0; i < m; i++) { 
        char ch; int x; 
        cin >> ch; 
        if(ch == 'R') { 
            cin >> x; 
            sum = (sum + x) % c; 
        }
        else if(ch == 'L') { 
            cin >> x; 
            sum = (sum + n - x) % c; 
        }
        else { 
            sum = (c - sum) % c; 
            state = state ^ 1; 
        }
        ret += dyn[state][sum]; 
        if(rev != -1) ret += dyn[state ^ 1][(rev + c - sum) % c]; 
        dyn[state][sum]++; 
    }
    cout << ret << '\n'; 
    return 0; 
}