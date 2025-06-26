#include "bits/stdc++.h"

using namespace std;

int main(void) { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0);
    int N, M, Steps; 
    cin >> N >> M >> Steps; 
    vector<string>dir(Steps); 
    for(int i = 0; i < Steps; i++) {
        cin >> dir[i];
    }
    for(int i = 0; i < Steps; i++) { 
        string odir = dir[i]; 
        string cc; 
        int good = false; 
        for(string c : {"Left", "Right", "Forward"}) {
            dir[i] = c; 
            int direction = 0; 
            pair<int, int>move = {0, 0}; 
            for(int j = 0; j < Steps; j++) { 
                if(dir[j] == "Forward") { 
                    if(direction == 0)      {move.second++; }
                    else if(direction == 1) {move.first--;  }
                    else if(direction == 2) {move.first++;  }
                    else                    {move.second--; }
                }
                else if(dir[j] == "Left") { 
                    if(direction == 0) direction = 1; 
                    else if(direction == 1) direction = 3; 
                    else if(direction == 2) direction = 0; 
                    else if(direction == 3) direction = 2;
                }
                else if(dir[j] == "Right") { 
                    if(direction == 0) direction = 2; 
                    else if(direction == 1) direction = 0; 
                    else if(direction == 2) direction = 3; 
                    else if(direction == 3) direction = 1; 
                }
            }
            if(move.first == N && move.second == M) { 
                good = true; 
                cc = c; 
            }
            dir[i] = odir;
            if(good) break;  
        }
        if(good) { 
            cout << i + 1 << " " << cc << '\n'; 
            return 0; 
        }
    }
    return 0; 
}