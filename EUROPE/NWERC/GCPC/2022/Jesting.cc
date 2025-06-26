#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    string s;
    cin >> s;
    int n = s.length(); 
    string cards = "cdhs";
    int ret = n; 
    do {
        vector<int> dyn(4, 0);
        for (int i = 0; i < n; i++) {
            int ptr = cards.find(s[i]);
            dyn[ptr]++;
            for (int j = ptr; j < 4; j++) dyn[j] = max(dyn[j], dyn[ptr]);
        }
        ret = min(ret, n - *max_element(dyn.begin(), dyn.end()));
    } 
    while (next_permutation(cards.begin(), cards.end()));
    cout << ret << '\n'; 
    return 0;
}