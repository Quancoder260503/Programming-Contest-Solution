#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 2; 

int64_t dyn[maxf][4][3]; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    int n; 
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    memset(dyn, -1, sizeof(dyn));
    string vowels = "AEIOUY";
    function<int64_t(int, int, int)> dfs = [&](int curr, int pos, int cons) -> int64_t {
        if (curr == n) return 0;
        if (dyn[curr][pos][cons] != -1) return dyn[curr][pos][cons];
        int64_t &ret = dyn[curr][pos][cons];
        ret = INT32_MAX;
        if(pos < min(int(s[curr].size()), 3)) {
            int is_vowels = (vowels.find(s[curr][pos]) != -1); 
            if(is_vowels) {
                ret = min({ret, 1 + dfs(curr, pos + 1, 0), 1 + dfs(curr + 1, 0, 0)}); 
            }
            if(!is_vowels && cons < 2) {
                ret = min({ret, 1 + dfs(curr, pos + 1, cons + 1), 1 + dfs(curr + 1, 0, cons + 1)}); 
            }
        }
        else ret = min(ret, dfs(curr + 1, 0, cons)); 
        return ret; 
    };
    int64_t ret = dfs(0, 0, 0);
    if (ret == INT32_MAX) cout << '*' << '\n';
    else
        cout << ret << '\n'; 
    return 0;
}