#include "bits/stdc++.h"
#pragma GCC target("popcnt")
using namespace std; 
#include <array> 
#include <vector>
#define MAX 105
#define M 140002
#define L 1400001
#define N 7002
bitset<M>res;
#define mp make_pair
bitset<L>Knap; 
int n;
vector<int>arr;
signed main(void){
     scanf("%d",&n);
     for(int i = 1; i <= n; i++)
     {
          int x; cin >> x;
          arr.push_back(x); 
     }
     pair<unsigned long long,int> opt = mp(0,-1);
     sort(arr.begin(),arr.end());
     for(int i = 0; i < arr.size(); i++){
           vector<int>tmp;
           for(int j = 0; j < arr.size(); j++){
                if(i == j) continue; 
                tmp.push_back(arr[j]);
           }
           bitset<(L / 2)>DP; 
           DP[0] = 1; 
           for(int j = 0; j < tmp.size(); j++){
                DP |= (DP << tmp[j]); 
           }
           opt = max(opt, mp(1LL * DP.count(),i)); 
     }
     printf("%d",arr[opt.second]); 
     Knap[L / 2 - 1] = 1; 
     for(int i = 0; i < arr.size(); i++){
         if(i == opt.second) continue; 
         Knap |= (Knap << arr[i]) | (Knap >> arr[i]); 
     }
     for(int i = 0; i < L / 2; i++){
         if(!Knap[i + L / 2 - 1]){
             printf(" %d",i); 
             return 0;
         }
     }
     return 0; 
}