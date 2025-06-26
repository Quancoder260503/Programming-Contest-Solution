#include "bits/stdc++.h"
using namespace std;
#define lint long long
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
int n, m;
signed main(void)
{
    cin >> n;
    Tree<lint> tree; 
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    reverse(arr + 1, arr + n + 1); 
    lint ans = 0; 
    for(int i = 1; i <= n; i++)
    {
         ans += tree.order_of_key(arr[i]); 
         tree.insert(arr[i]);
    }
    cout << ans << '\n'; 
    return 0;
}