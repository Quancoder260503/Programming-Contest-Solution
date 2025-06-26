#include "bits/stdc++.h"

using namespace std; 

const int mod = 1e9 + 7;

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL); 
    int tc; 
    cin >> tc;
    for(int _ = 0; _ < tc; _++) {
        string s;
        cin >> s;
        int64_t ret = 1;
        for (int i = 0; i < s.size(); i++)
        {
            int ctr = 1;
            if (i && s[i] != s[i - 1]) ctr++;
            if (i + 1 < s.size() && s[i] != s[i + 1] && s[i - 1] != s[i + 1]) ctr++;
            ret = 1LL * ret % mod * ctr % mod;
        }
        cout << "Case #" << _ + 1 << ": " << ret << '\n';
    }
    return 0; 
}