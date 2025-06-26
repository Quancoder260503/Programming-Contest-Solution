#include "bits/stdc++.h"

using namespace std;

#define sz(a) int(a.size())
#define int64_t long long

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    string a, b, c, op, _; 
    cin >> a >> op >> b >> _ >> c; 
    for(int i = 0; i < sz(a); i++) { 
        for(int j = 0; j < sz(b); j++) { 
            string nb = a.substr(0, i) + b.substr(j); 
            string na = b.substr(0, j) + a.substr(i);
            int64_t x = stoll(na), y = stoll(nb), z = stoll(c);
            if(op == "+" && x + y == z) { 
                cout << x << " + " << y << " = " << z << '\n'; 
                return 0; 
            }
            else if(op == "*" && 1LL * x * y == z) { 
                cout << x << " * " << y << " = " << z << '\n'; 
                return 0; 
            }
        }
    }
    for(int i = 0; i < sz(a); i++) { 
        for(int j = 0; j < sz(c); j++) { 
            string nc = a.substr(0, i) + c.substr(j); 
            string na = c.substr(0, j) + a.substr(i);
            int64_t x = stoll(na), y = stoll(b), z = stoll(nc); 
            if(op == "+" && x + y == z) { 
                cout << x << " + " << y << " = " << z << '\n'; 
                return 0; 
            }
            else if(op == "*" && 1LL * x * y == z) { 
                cout << x << " * " << y << " = " << z << '\n'; 
                return 0; 
            }
        }
    }
    for(int i = 0; i < sz(b); i++) { 
        for(int j = 0; j < sz(c); j++)  { 
            string nc = b.substr(0, i) + c.substr(j); 
            string nb = c.substr(0, j) + b.substr(i);
            int64_t x = stoll(a), y = stoll(nb), z = stoll(nc); 
            if(op == "+" && x + y == z) { 
                cout << x << " + " << y << " = " << z << '\n';
                return 0;  
            }
            else if(op == "*" && 1LL * x * y == z) { 
                cout << x << " * " << y << " = " << z << '\n'; 
                return 0; 
            }
        }
    }
    return 0; 
}