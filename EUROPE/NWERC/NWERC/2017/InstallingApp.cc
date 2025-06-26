#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; 
    cin >> n >> k;
    vector<int> s(n + 1), d(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> d[i] >> s[i]; 
    }
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), [&](int i, int j) { 
        return d[i] - s[i] > d[j] - s[j]; 
    });
    vector<vector<int>> dyn(n + 1, vector<int>(k + 1));
    for (int i = 1; i <= n; i++) {
        int at = ord[i - 1];
        for (int j = 0; j <= k; j++) {
            dyn[i][j] = dyn[i - 1][j];
            if (k < d[at] + j - s[at]) continue; 
            if (j >= s[at]) {
                dyn[i][j] = max(dyn[i][j], dyn[i - 1][j - s[at]] + 1);
            }
        }
    }
    pair<int, int> ret;
    for (int i = 0; i <= k; i++) {
        ret = max(ret, {dyn[n][i], -i});
    }
    cout << ret.first << '\n';
    vector<int> res;
    k = -ret.second; 
    for (int j = n; j > 0 && k > 0; j--) {
        int at = ord[j - 1]; 
        if (dyn[j][k] == dyn[j - 1][k - s[at]] + 1) {
            res.push_back(at);
            k = k - s[at]; 
        }
    }
    assert(int(res.size()) == ret.first); 
    reverse(res.begin(), res.end());
    for (int i = 0; i < res.size(); i++) cout << res[i] << " ";
    cout << '\n'; 
    return 0;
}