#include "bits/stdc++.h"

using namespace std;

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    deque<int> dq;
    vector<int> a(n); 
    for (int i = 0; i < n; i++) {
        cin >> a[i]; 
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        dq.push_back(a[i]); 
    }
    int64_t ret = 0; 
    while (dq.size() >= 3) {
        dq.pop_back();
        ret += dq.back();
        dq.pop_back();
        dq.pop_front(); 
    }
    cout << ret << '\n';
    return 0;
}