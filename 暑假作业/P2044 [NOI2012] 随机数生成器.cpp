#include <stdio.h>
using ll = __int128;
ll m, a, c, x, n, g;
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
ll pow(ll a, ll b, ll mod)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
ll get(ll len, ll st)
{
    return (len ^ 1 ? (bool(len & 1) * st * pow(a, len - 1, m) % m + (pow(a, len >> 1, m) % m + 1) * get(len >> 1, st) % m) % m : st);
}
int main()
{
    rd(m, a, c, x, n, g);
    printf("%lld\n", (get(n, c) + (x * pow(a, n, m) % m)) % m % g);
    return 0;
}
