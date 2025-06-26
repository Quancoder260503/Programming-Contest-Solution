#include "bits/stdc++.h"
using namespace std;
#define lint long long
lint n;
vector<lint> ans;
void solve(lint n)
{
   if (n < 10)
   {
      ans.push_back(n);
      return;
   }
   if (n == 10)
   {
      ans.push_back(1);
      ans.push_back(9);
      return;
   }
   if (n <= 20)
   {
      ans.push_back(11);
      ans.push_back(n - 11);
      return;
   }
   string sa = to_string(n);
   string sb = sa.substr(0, (sa.length() + 1) / 2);
   string sc = to_string(stoll(sb) - 1L); 
   string sd = sc.substr(0, sc.length() - (sa.length() & 1));
   reverse(sd.begin(), sd.end());
   sc += sd; 
   ans.push_back(stoll(sc));
   solve(n - stoll(sc));   
   return;
}
signed main(void)
{
   cin >> n; 
   solve(n);
   cout << ans.size() << '\n'; 
   for(int i = 0; i < ans.size(); i++)
   {
      cout << ans[i] << endl; 
   }
   return 0;
}