#include "bits/stdc++.h"

using namespace std;

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    map<string, string> str; 
    map<string, int> ctr, correct, incorrect;
    int n, m;
    cin >> m;
    vector<string> s(m); 
    for (int i = 0; i < m; i++) {
        cin >> s[i];
        ctr[s[i]]++;
    }
    cin >> n;
    vector<string> a(n), b(n), c(n);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i];
        str[a[i]] = b[i];
        mx = max(mx, ++(c[i] == "correct" ? correct : incorrect)[a[i]]);
    }
    double ra = 1, rb = 1;
    for (const auto &[u, v] : ctr) {
        ra = ra * pow(correct[u], ctr[u]);
        double c = pow(correct[u] + incorrect[u], ctr[u]); 
        if (c > 0) rb = rb * c;
    }
    rb = rb - ra; 
    if (mx == 1 || ra == 1) {
        for (int i = 0; i < m; i++) {
            cout << str[s[i]] << " "; 
        }
        cout << '\n' << (ra == 1 ? "correct" : "incorrect") << '\n';
    } 
    else {
        cout << (int64_t) ra << " correct" << '\n';
        cout << (int64_t) rb << " incorrect" << '\n';
    }
    return 0;
}