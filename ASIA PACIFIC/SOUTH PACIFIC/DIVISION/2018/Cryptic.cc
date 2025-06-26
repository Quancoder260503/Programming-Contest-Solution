#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    string line;
    getline(cin, line);
    stringstream ss(line); 
    string word;
    vector<string>s;  
    while(ss >> word) { 
        s.push_back(word);  
    }
    int n; 
    cin >> n;
    for(int _ = 0; _ < n; _++) { 
        string cand, scand; 
        cin >> cand; 
        scand = cand; 
        stable_sort(cand.begin(), cand.end()); 
        for(int i = 0; i < sz(s); i++) { 
            string rcurr;
            for(int j = i; j < sz(s); j++) {
                rcurr += s[j];
                string curr = rcurr; 
                string scurr = curr; 
                stable_sort(curr.begin(), curr.end()); 
                if(sz(scand) != sz(scurr) || scand == scurr) continue; 
                if(cand == curr) { 
                   cout << scand << '\n';
                   return 0; 
                }  
            } 
        }
    } 
    return 0; 
}