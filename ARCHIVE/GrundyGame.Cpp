#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int sz = 4e5 + 1;
const int N = 2e5 + 10;
int bad[]= {0,1,2,4,7,10,20,23,26,50,53,270,273,276,282,285,288,316,334,337,340,346,359,362,365,386,389,392,566,630,633,636,639,673,676,682,685,923,926,929,932,1222};
int main(){
     int ntest;
     scanf("%d",&ntest);
     int len = sizeof(bad) / sizeof(*bad); 
     while(ntest--){
          int n; scanf("%d",&n);
          bool g = 0;
          for(int i = 0; i < len; i++){
               if(n == *(bad + i)){
                    g = 1;
                    break; 
               }
          }
          printf(!g ? "first\n" : "second\n"); 
     }
     return 0; 
}