#include "bits/stdc++.h"

using namespace std;

const int maxf = 3e6 + 10;
mt19937 rng; 

bitset<maxf> dyn; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, x;
    cin >> n >> x;
    vector<int> w, a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (x >= a[i]) w.push_back(x - a[i] + 1);
    }
    sort(w.begin(), w.end());
    auto f = [&](vector<int> c) {
        if(c.size() <= 2) {
            int ret = 0;
            for (int i = 0; i < c.size(); i++) {
                ret = max(ret, x - c[i] + 1); 
            }
            return ret; 
        }
        for (int i = 0; i < 2; i++) c.pop_back();
        if (c.size() <= 2) return x + 1;
        for (int i = 0; i < 2; i++) c.pop_back(); 
        shuffle(c.begin(), c.end(), rng);
        int sum = accumulate(c.begin(), c.end(), 0);
        const int middle = maxf / 2; 
        dyn[middle] = 1;
        for (int i = 0; i < c.size(); i++) {
            dyn = (dyn << c[i]) | (dyn >> c[i]);
        }
        int ret = 1'000'000'000; 
        for (int i = 0; i < maxf; i++) { 
            if(dyn[i]) {
                ret = min(ret, (sum + abs(i - middle)) / 2);
            } 
        }
        return ret + x + 1;  
    };
    int ret = f(w); 
    for (int i = 0; i < n; i++) {
        ret = max(ret, a[i]);
    }
    cout << ret << '\n'; 
    return 0;
}