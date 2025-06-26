#include "bits/stdc++.h"

using namespace std;

int main(void) {
    int tc, N, M;
    string s, word; 
    cin >> tc; 
    cin.ignore(); 
    while(tc--) {
        cin >> N >> M;
        vector<vector<pair<int, int>>>clause; 
        cin.ignore(); 
        for(int i = 0; i < M; i++) { 
            getline(cin, s);
            stringstream ss(s); 
            vector<pair<int, int>>rec; 
            while(ss >> word) { 
                if(word == "v") continue; 
                if(word[0] == '~') rec.push_back({stoi(word.substr(2)) - 1, false}); 
                else               rec.push_back({stoi(word.substr(1)) - 1, true }); 
            }
            clause.push_back(rec); 
        }
        for(int mask = 0; mask < (1 << N); mask++) { 
            int flag = true; 
            for(int i = 0; i < M; i++) { 
                int sum = 0; 
                for(auto [x, state] : clause[i]) { 
                    sum |= state ^ ((mask >> x) & 1); 
                }
                flag &= sum;  
            }
            if(flag) { 
                cout << "satisfiable\n"; 
                goto done; 
            }
        }
        cout << "unsatisfiable\n"; 
    done:; 
    }
    return 0;
}