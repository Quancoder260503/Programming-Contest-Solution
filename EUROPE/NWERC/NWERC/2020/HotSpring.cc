#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0); 
    int n; 
    cin >> n; 
    vector<int>a(n); 
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    sort(a.begin(), a.end()); 
    deque<int>b;
    for(int i = 0; i < a.size(); i++) { 
        b.push_back(a[i]); 
    }
    vector<int>ret;
    while(b.size()) { 
        if(b.size() == 1) {
            ret.push_back(b.back());  
            break; 
        }
        ret.push_back(b.back());
        ret.push_back(b.front()); 
        b.pop_back();  
        b.pop_front(); 
    }
    int check = true; 
    reverse(ret.begin(), ret.end()); 
    for(int i = 1; i < n - 1; i++) { 
        check &= (abs(ret[i - 1] - ret[i]) <= abs(ret[i] - ret[i + 1])); 
    }
    if(check) {
        for(auto &x : ret) { 
            cout << x << " "; 
        }
        cout << '\n'; 
    }
    else {
        cout << "impossible\n"; 
    }
    return 0; 
}