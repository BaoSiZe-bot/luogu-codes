#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>

using std::abs;
using std::cin;
using std::count;
using std::cout;
using std::string;


namespace Fujiwara
{
using ll = long long;
const int N = 1e6 + 5;

int cnt;
string s;
int n, p, q, x, y;
static int Azusa()
{
    cin >> n >> p >> q >> x >> y >> s;
    cnt = abs(n + p - q - count(s.begin(), s.end(), '-') * 2) / 2;
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("book.in", "r", stdin);
    freopen("book.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    return Fujiwara::Azusa();
}
