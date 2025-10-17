#include <string>
#include <iostream>
#include <algorithm>

using std::abs;
using std::cin;
using std::cout;
using std::min;
using std::string;

namespace Fujiwara
{
const int INF = 1e9;
const int N = 1e6 + 5;

string s;
int res = INF;
int m[N], q[N];
int v[N], t[N];
int n, a, b, x, y;
static int Azusa()
{
    cin >> n >> a >> b >> x >> y >> s;
    for (int i = 0; i < n; ++i)
        v[i] = (s[i] == '+') ? 1 : -1;
    for (int i = 0; i < n; ++i)
        t[i + 1] = t[i] + v[i];
    for (int i = n - 1; ~i; --i)
        m[i] = min(m[i + 1], t[i]);
    for (int i = 0, k = INF; i < n; ++i)
    {
        int dy = (n - i) % n, df = min(k + t[n], m[i + 1]) - t[i];
        int fx = -min(0, df + a - 1) >> 1;
        int dx = fx + (abs(t[n] + fx + fx + a - b) >> 1);
        res = min(res, dx * x + dy * y);
        k = min(k, t[i]);
    }
    cout << res;
    return 0;
}
}  // namespace Fujiwara
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    return Fujiwara::Azusa();
}
