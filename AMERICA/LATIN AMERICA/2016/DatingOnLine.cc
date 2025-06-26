#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int N; 
    cin >> N;
    vector<int>h(N);  
    for(int i = 0; i < N; i++) { 
        cin >> h[i]; 
    }
    sort(h.rbegin(), h.rend()); 
    deque<int>ord;
    for(int i = 0; i < N; i++) { 
        if(i & 1) { ord.push_back(h[i]);  }
        else {      ord.push_front(h[i]); }
    }
    double ret = 0, lstx = 0, lsty = 0; 
    for(int i = 0; i <= N; i++) { 
        double angle = (i % N) * (2 * acos(-1)) / N;
        double curr_x = cos(angle) * ord[i % N]; 
        double curr_y = sin(angle) * ord[i % N]; 
        if(i > 0) { 
            ret += -curr_x * lsty + curr_y * lstx; 
        }
        lstx = curr_x, lsty = curr_y; 
    }
    ret = ret / 2.0; 
    cout << fixed << setprecision(3) << ret << '\n'; 
    return 0;
}