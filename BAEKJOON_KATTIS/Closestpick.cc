#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    cout << fixed << setprecision(9); 
    for (int _ = 0, n, k; _ < tc; _++) {
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        n = a.size();
        vector<int> ret;
        ret.push_back(a[0] - 1);
        ret.push_back(k - a.back());
        int num = 0; 
        for (int i = 0; i + 1 < n; i++) {
            num = max(num, a[i + 1] - a[i] - 1);
            if (a[i + 1] - a[i] > 1) ret.push_back((a[i + 1] - a[i]) / 2);
        }
        sort(ret.rbegin(), ret.rend());
        num = max(num, ret[0] + ret[1]); 
        cout << "Case #" << _ + 1 << ": " << 1.0 * num / k << '\n';
    }
    return 0;
}