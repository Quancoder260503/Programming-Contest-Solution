#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int sz =2e5+1;
const int ssz=5e3+1;
const int mod=1e9+7;
int main(){
      int a,b; char mid;
      cin>>a>>mid>>b;
      if( a < b - 1){
           cout<<"impossible";
           return 0;
      }
      int k = (2*a + b + b*b - 1)/(b * b);
      int n = k * b;
      cout<<n<<' '<<n - 1<<endl; 
      int tot = k * a;
      int cur = 0; 
      for(int i = 0; i < n; i++){
           int add = min(i,tot - cur - n + i + 1);
           cur += add;
           if(!i) continue;
           cout<<(i + 1)<<' '<<add<<endl;
      }
}