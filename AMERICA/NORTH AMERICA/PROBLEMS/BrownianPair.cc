#include "bits/stdc++.h"

using namespace std;

typedef long long int dataType;

class Fraction {
 public:
  Fraction(dataType num = 0, dataType denom = 1);

  double toDouble() const;

  void reduce();

  // Changes the Fraction itself.
  void selfReciprocal();

  // Returns a new Fraction, leaving the original.
  Fraction reciprocal() const;

  Fraction &operator+=(const Fraction &x);
  Fraction &operator-=(const Fraction &x);
  Fraction &operator*=(const Fraction &x);
  Fraction &operator/=(const Fraction &x);
  Fraction &operator-();

  bool operator<(const Fraction &x) const;
  bool operator==(const Fraction &x) const;

  dataType num, denom;
};

Fraction operator+(const Fraction &x, const Fraction &y);
Fraction operator-(const Fraction &x, const Fraction &y);
Fraction operator*(const Fraction &x, const Fraction &y);
Fraction operator/(const Fraction &x, const Fraction &y);

istream &operator>>(istream &is, Fraction &x);
ostream &operator<<(ostream &os, const Fraction &x);

Fraction::Fraction(dataType n, dataType d) {
  if (d < 0) {
    num = -n;
    denom = -d;
  } else {
    num = n;
    denom = d;
  }
  reduce();
}

double Fraction::toDouble() const { return 1.0 * num / denom; }

// Howard's GCD function with no checks
dataType gcd(dataType a, dataType b) {
  dataType r;
  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

void Fraction::reduce() {
  dataType g = gcd(abs(num), denom);
  num /= g;
  denom /= g;
}

void Fraction::selfReciprocal() {
  swap(num, denom);
  if (denom < 0) {
    num = -num;
    denom = -denom;
  }
}

Fraction Fraction::reciprocal() const { return Fraction(denom, num); }
Fraction &Fraction::operator+=(const Fraction &x) {
  dataType g = gcd(denom, x.denom);

  dataType a = denom / g;
  dataType b = x.denom / g;

  num = num * b + x.num * a;
  denom *= b;

  reduce();

  return (*this);
}
Fraction &Fraction::operator-=(const Fraction &x) {
  dataType g = gcd(denom, x.denom);
  dataType a = denom / g;
  dataType b = x.denom / g;

  num = num * b - x.num * a;
  denom *= b;

  reduce();
  return (*this);
}

Fraction &Fraction::operator*=(const Fraction &x) {
  num *= x.num;
  denom *= x.denom;
  reduce();
  return (*this);
}

Fraction &Fraction::operator/=(const Fraction &x) {
  num *= x.denom;
  denom *= x.num;

  if (denom < 0) {
    num = -num;
    denom = -denom;
  }
  reduce();
  return (*this);
}

Fraction &Fraction::operator-() {
  num *= -1;
  return *this;
}

// Careful with overflow. If it is an issue, you can compare the
// double values, but you SHOULD check for equality BEFORE converting
bool Fraction::operator<(const Fraction &x) const {
  return (num * x.denom) < (x.num * denom);
}

bool Fraction::operator==(const Fraction &x) const {
  return (num == x.num) && (denom == x.denom);
}

bool operator>(const Fraction &x, const Fraction &y) {
  return !(x == y) && !(x < y);
}

bool operator<=(const Fraction &x, const Fraction &y) {
  return (x == y) || (x < y);
}

bool operator>=(const Fraction &x, const Fraction &y) {
  return (x == y) || (x > y);
}

bool operator!=(const Fraction &x, const Fraction &y) { return !(x == y); }

Fraction operator+(const Fraction &x, const Fraction &y) {
  Fraction a(x);
  a += y;
  return a;
}

Fraction operator-(const Fraction &x, const Fraction &y) {
  Fraction a(x);
  a -= y;
  return a;
}

Fraction operator*(const Fraction &x, const Fraction &y) {
  Fraction a(x);
  a *= y;
  return a;
}

Fraction operator/(const Fraction &x, const Fraction &y) {
  Fraction a(x);
  a /= y;
  return a;
}
istream &operator>>(istream &is, Fraction &x) {
  is >> x.num;

  char ch;
  is >> ch;
  if (ch != '/') {
    is.putback(ch);
    x.denom = 1;
  } else {
    is >> x.denom;
    if (x.denom < 0) {
      x.num = -x.num;
      x.denom = -x.denom;
    }
    x.reduce();
  }

  return is;
}
ostream &operator<<(ostream &os, const Fraction &x) {
  os << x.num;
  os << '/' << x.denom;
  return os;
}
#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, d, x, y;
  cin >> n >> x >> y >> d; 
  vector<vector<vector<Fraction>>>dp(d + 1, vector<vector<Fraction>>(n, vector<Fraction>(n))); 
  // Probability that two of them will never meet 
  --x; --y; 
  dp[0][x][y] = Fraction(1, 1);
  Fraction prob = Fraction(1, 4); 
  for(int days = 1; days <= d; days++) { 
   for(int pos_x = 0; pos_x < n; pos_x++) { 
    for(int pos_y = 0; pos_y < n; pos_y++) {
     if(pos_x == pos_y) continue; 
     for(auto dir_x : {-1, 1}) { 
      for(auto dir_y : {-1, 1}) { 
       int nxt_x = min(n - 1, max(0, dir_x + pos_x)), nxt_y = min(n - 1, max(0, dir_y + pos_y)); 
       if(nxt_x != nxt_y) { 
        dp[days][nxt_x][nxt_y] += dp[days - 1][pos_x][pos_y] * prob; 
       }
      }
     }  
    }
   }
  }
  Fraction ret = Fraction(); 
  for(int i = 0; i < n; i++) { 
   for(int j = 0; j < n; j++) { 
    if(i == j) continue; 
    ret += dp[d][i][j]; 

   }
  }
  // 1, 2
  // -> ()
  ret = Fraction(1, 1) - ret; 
  cout << ret << '\n'; 
  return 0;
}