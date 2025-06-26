#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    auto f = [&](int64_t a, int64_t b, int64_t c) -> int64_t { return 1LL * a * a + 1LL * b * b + 1LL * c * c + 7* min({a, b, c});  };
    const int LIM = 1000;
    for (int tc = 0, a, b, c, d; tc < n; tc++) {
        int64_t ret = 0;
        cin >> a >> b >> c >> d; 
        for (int i = 0; i < LIM; i++) for (int j = 0; j < LIM; j++) { 
            if(i + j <= d) {
                int k = d - i - j;
                ret = max(ret, f(a + i, b + j, c + k)); 
            }
        }
        ret = max(ret, f(a + d, b, c));
        ret = max(ret, f(a, b + d, c));
        ret = max(ret, f(a, b, c + d)); 
        cout << ret << '\n';
    }
    return 0;
}