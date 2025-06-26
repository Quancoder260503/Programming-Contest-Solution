#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

int main(void) {
   ios_base::sync_with_stdio(0); 
   cin.tie(0); 
   cout.tie(0); 
   int64_t xA, yA, dA, xB, yB, dB, opt; 
   cin >> xA >> yA >> dA >> xB >> yB >> dB; 
   int64_t dx = llabs(xA - xB), dy = llabs(yA - yB), dist = dA + dB;
   if(dist < dx + dy || (dist - dx - dy) % 2 == 1) { 
      cout << "impossible\n";
      return 0; 
   } 
   opt = min(dx, dA); 
   xA += opt * (xB > xA ? 1 : -1); 
   dA -= opt; 
   opt = min(dy, dA); 
   yA += opt * (yB > yA ? 1 : -1); 
   dA -= opt; 
   cout << xA << " " << yA + (dA % 2) << '\n'; 
   return 0;
}