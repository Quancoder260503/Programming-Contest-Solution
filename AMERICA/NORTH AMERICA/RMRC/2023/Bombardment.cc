#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int N, R; 
    cin >> N >> R; 
    vector<int>rx(N); 
    for(int i = 0; i < N; i++) cin >> rx[i];
    sort(rx.begin(), rx.end()); 
    vector<int>res; 
    while(rx.size())
    {
        pair<int, int>ret; 
        for(int i = 0; i < rx.size(); i++)
        {
            int l = lower_bound(rx.begin(), rx.end(), rx[i] - 2 * R) - rx.begin(); 
            int r = upper_bound(rx.begin(), rx.end(), rx[i] + 2 * R) - rx.begin() - 1;
            ret = max(ret, {r - i + 1, -(rx[i] + R)});
            ret = max(ret, {i - l + 1, -(rx[i] - R)}); 
        }
        ret.second = -ret.second; 
        res.push_back(ret.second);
        int l = lower_bound(rx.begin(), rx.end(), ret.second - R) - rx.begin();
        int r = upper_bound(rx.begin(), rx.end(), ret.second + R) - rx.begin();
        vector<int>nrx;
        for(int i = 0; i < l; i++) nrx.push_back(rx[i]);
        for(int i = r; i < rx.size(); i++) nrx.push_back(rx[i]);
        rx.swap(nrx);
    }
    cout << res.size() << '\n'; 
    for(int i = 0; i < res.size(); i++) cout << res[i] << ' '; 
    return 0; 
}