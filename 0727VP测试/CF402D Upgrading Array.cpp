#include <stdio.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
int a[5005];
std::vector<int> prm;
__gnu_pbds::gp_hash_table<int, int> mp, bd;
#define Get() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 23], *p1 = buf, *p2 = buf;
template <class T> inline void rd(T &x)
{
    x = 0;
    int f = 1;
    char c = Get();
    for (; c < 48 || c > 57; c = Get())
        c == 45 && (f = ~f + 1);
    for (; c > 47 && c < 58; c = Get())
        x = (x << 1) + (x << 3) + (c ^ 48);
    x *= f;
}
template <class T, class... S> inline void rd(T &x, S &...y)
{
    rd(x);
    rd(y...);
}
inline int gcd(int x, int y)
{
    return y ? gcd(y, x % y) : x;
}
inline int f(int x)
{
    if (mp[x])
        return mp[x];
    int res = 0;
    int tmp = x;
    for (int i = 6; (i - 1) * (i - 1) <= x; i += 6)
    {
        int u = i - 1, v = i + 1, cnt = 0;
        while (tmp % u == 0)
            tmp /= u, ++cnt;
        res += bd[u] ? -1 * cnt : cnt;
        if (tmp == 1)
            break;
        while (tmp % v == 0)
            tmp /= v, ++cnt;
        res += bd[v] ? -1 * cnt : cnt;
        if (tmp == 1)
            break;
    }
    if (tmp > 1)
        res += bd[tmp] ? -1 : 1;
    return mp[x] = res;
}
int main()
{
    int n, m;
    rd(n, m);
    for (int i = 1; i <= n; ++i)
        rd(a[i]);
    for (int i = 1; i <= m; ++i)
        rd(b[i]);
    return 0;
}
