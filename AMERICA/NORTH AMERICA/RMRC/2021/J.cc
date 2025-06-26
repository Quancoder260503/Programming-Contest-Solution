#include "bits/stdc++.h"
using namespace std;
vector<int64_t>steps(vector<int64_t>curr)
{
    int64_t X = 0, Y = 0, Z = 0; 
    int64_t x = curr[0], y = curr[1], z = curr[2]; 
    (y >= z ? Y : Z)++; 
    (z >= x ? Z : X)++;
    (x >= y ? X : Y)++;
    return {x - X, y - Y, z - Z}; 
}
pair<int, int64_t>f(vector<int64_t>A)
{
    int64_t a = A[0], b = A[1], c = A[2]; 
    sort(A.begin(), A.end()); 
    int64_t x = A[0], y = A[1], z = A[2]; 
    if(x == 0) return {a == z ? 0 : b == z ? 1 : 2, z - y}; 
    if(a == b && b == c) return {-1, 0};
    if(y < 100) return f(steps({a, b, c}));  
    if(a != b && b != c && a != c)
    {
        int64_t step = min(y - x, z - y); 
        return f({a - 1LL * step * ((a == z) * 2 + (a == y)),
                  b - 1LL * step * ((b == z) * 2 + (b == y)),
                  c - 1LL * step * ((c == z) * 2 + (c == y))}
                ); 
    }
    if(x == y)
    {
        int64_t two_steps = min(x - 1, (z - x) / 3); 
        if(two_steps)
        {
            return f({a - 1LL * two_steps * ((a == z) * 4 + (a == y)),
                      b - 1LL * two_steps * ((b == z) * 4 + (b == y)),
                      c - 1LL * two_steps * ((c == z) * 4 + (c == y))}
                      );
        }
        if(z == x + 2) return f(steps({a, b, c}));
        x = x % 3 + 3; 
        return f({x + (a == z), x + (b == z), x + (c == z)});  
    }
    int64_t two_steps = (z - x) / 3;
    if (two_steps)
    {
        return f({a - 1LL * two_steps * ((a == z) * 3),
                  b - 1LL * two_steps * ((b == z) * 3),
                  c - 1LL * two_steps * ((c == z) * 3)});
    }
    if (z == x + 2) return f(steps({a, b, c}));
    x = x % 3 + 3;
    return f({x + (a == z), x + (b == z), x + (c == z)});
}
int main(void)
{
    int64_t A, B, C;
    vector<char>win = {'A', 'B', 'C'}; 
    while(cin >> A >> B >> C)
    {
        auto ret = f({A, B, C}); 
        if(ret.second == 0) cout << "Rubble!" << '\n'; 
        else cout << win[ret.first] << " " << ret.second << '\n'; 
    }
    return 0; 
}