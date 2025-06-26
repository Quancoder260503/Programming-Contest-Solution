#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    map<string, int> ctr, last;
    string line;
    vector<string> cc;
    getline(cin, line); 
    for (int i = 0; i < n * 3; i++) {
        getline(cin, line); 
        stringstream ss(line);
        string word;
        string s; 
        while(ss >> word) s = s + (s.size() == 0 ? "" : " ") + word;
        if (ctr.count(s) == 0) cc.push_back(s); 
        ctr[s]++;
        last[s] = i;
    }
    sort(cc.begin(), cc.end(), [&](string a, string b) { return ctr[a] == ctr[b] ? last[a] > last[b] : ctr[a] > ctr[b]; });
    for (int i = 0; i < min(int(cc.size()), k); i++) cout << cc[i] << '\n';
    return 0;
}