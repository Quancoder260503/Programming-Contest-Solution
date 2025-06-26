#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int n;
    cin >> n;
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    int64_t ret = 0;
    vector<tuple<int, int, int>> cc;
    for(int i = 0; i < n; i++)
    {
        int c, w, d; 
        cin >> w >> c >> d; 
        cc.push_back({w, c, d}); 
    }
    do
    {
        int64_t acc = 0, sum = 0;
        for (int i = 0; i < n; i++) {
            auto [w, c, d] = cc[a[i]]; 
            acc += w;
            if (acc > c) break;
            sum += d;
        }
        ret = max(ret, sum);
    } 
    while (next_permutation(a.begin(), a.end()));
    cout << ret << '\n'; 
    return 0;
}