#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5+1;
const int N = 1e6+1;
const int inf = 1e7+5;
long long n,m,k;
long long a[N];
long long d[N];
vector<int>primes[N];
void calc(int x){
     int num = x;
     if(primes[x].size() == 0){
        for(int i = 2; i * i <= num; i++){
            if(num % i == 0) primes[x].push_back(i);
            while(num % i == 0) num = num / i;
        }
        if(num > 1) primes[x].push_back(num);
     }
     for(int mask = 1; mask < (1 << primes[x].size()); mask++){
          long long product = 1; 
          for(int j = 0; j < primes[x].size(); j++){
               if((1 << j) & mask){
                     product = (long long) product * primes[x][j];
               }
          }
          d[product]++; 
    }
}
long long inc(int x){
     int num = x;
     long long ans = 0;
     for(int mask = 1; mask < (1 << primes[x].size()); mask++){
          bool odd = (__builtin_popcount(mask) & 1); 
          long long product = 1; 
          for(int j = 0; j < primes[x].size(); j++){
               if((1 << j) & mask){
                     product = (long long) product * primes[x][j];
               }
          }
          ans += (odd ? 1 : - 1)*(d[product] - 1);
     }
     return n - ans - 1; 
}
int main(){
      scanf("%d",&n);  
      for(int i = 1; i <= n; i++){
          scanf("%d",&a[i]);
          calc(a[i]);
      }
      long long res = 0;
      for(int i = 1; i <= n; i++){
            res = res + inc(a[i]); 
      }
      res = res >> 1;
      cout<<res<<endl;
}