#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<int64_t> psum(n + 1), dyn(n + 1);
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        psum[i + 1] = psum[i] + x;
    }
    priority_queue<pair<int64_t, int>> pq;
    pq.push({0, -1});
    for (int i = 0; i <= n; i++) {
        while (pq.size() && pq.top().second < i - k - 1) pq.pop(); 
        dyn[i] = psum[i] + pq.top().first;
        pq.push({dyn[i] - psum[i + 1], i});
    }
    cout << dyn[n] << '\n';
    return 0;
}