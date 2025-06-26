#include "bits/stdc++.h"

using namespace std;

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    set<int> ms;
    vector<int64_t> psum2(n + 2), psum(n + 2);
    for (int i = 1; i <= n + 1; i++) {
        psum[i]  = psum[i - 1] + i;
        psum2[i] = psum2[i - 1] + 1LL * i * i;
    }
    ms.insert(0);
    ms.insert(n + 1); 
    int64_t ret = 1LL * (n + 1) * psum[n + 1] - psum2[n + 1];
    for (int i = 0, x; i < m; i++) {
        cin >> x;
        if (!ms.count(x)) {
            auto itl = ms.lower_bound(x);
            auto itr = ms.upper_bound(x);
            itl--;
            int l = (*itl), r = (*itr);
            ret += 1LL * (l + x) * (psum[x] - psum[max(0, l - 1)]) - 1LL * x * l * (x - l + 1) - (psum2[x] - psum2[max(0, l - 1)]);
            ret += 1LL * (x + r) * (psum[r] - psum[max(0, x - 1)]) - 1LL * x * r * (r - x + 1) - (psum2[r] - psum2[max(0, x - 1)]);
            ret -= 1LL * (l + r) * (psum[r] - psum[max(0, l - 1)]) - 1LL * l * r * (r - l + 1) - (psum2[r] - psum2[max(0, l - 1)]);
            ms.insert(x); 
        } 
        else {
            ms.erase(x);
            auto itl = ms.lower_bound(x);
            auto itr = ms.upper_bound(x);
            itl--;
            int l = (*itl), r = (*itr);
            ret -= 1LL * (l + x) * (psum[x] - psum[max(0, l - 1)]) - 1LL * x * l * (x - l + 1) - (psum2[x] - psum2[max(0, l - 1)]);
            ret -= 1LL * (x + r) * (psum[r] - psum[max(0, x - 1)]) - 1LL * x * r * (r - x + 1) - (psum2[r] - psum2[max(0, x - 1)]);
            ret += 1LL * (l + r) * (psum[r] - psum[max(0, l - 1)]) - 1LL * l * r * (r - l + 1) - (psum2[r] - psum2[max(0, l - 1)]);
        }
        cout << ret << '\n';
    }
    return 0;
}