#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
 unordered_map<string, int>mp; 
 mp["N"] = 0;   
 mp["NE"] = 45; 
 mp["E"] = 90; 
 mp["SE"] = 135; 
 mp["S"]  = 180; 
 mp["SW"] = 225; 
 mp["W"]  = 270; 
 mp["NW"] = 315; 
 string a, b; 
 cin >> a >> b; 
 if(a == b) { 
  cout << "Keep going straight\n"; 
 } else { 
  int diff = (mp[b] - mp[a] + 360) % 360; 
  if(diff == 180) { 
   cout << "U-turn\n"; 
  } else { 
    cout << "Turn " << (diff < 180 ? diff : 360 - diff) << " degrees " << (diff > 180 ? "port" : "starboard") << '\n'; 
  }
 }
 return 0; 
}