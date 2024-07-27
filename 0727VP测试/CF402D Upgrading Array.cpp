#include <bitset>
#include <map>
#include <stdio.h>
#include <vector>
int a[100005], gg[100005];
std::vector<int> prm;
std::map<int, int> mp, bd;
std::bitset<100005> G;
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
inline void oba(int lim)
{
    for (int i = 2; i <= lim; ++i)
    {
        if (!G.test(i))
            prm.push_back(i);
        for (int j : prm)
        {
            if (i * j > lim)
                break;
            G.set(i * j);
            if (i % j == 0)
                break;
        }
    }
}
inline int f(int x)
{
    if (mp.count(x))
        return mp[x];
    int res = 0;
    int tmp = x;
    for (int i : prm)
    {
        int cnt = 0;
        while (tmp % i == 0)
            tmp /= i, ++cnt;
        res += bd[i] ? -1 * cnt : cnt;
        if (tmp == 1)
            break;
    }
    if (tmp > 1)
        res += bd[tmp] ? -1 : 1;
    return mp[x] = res;
}
int main()
{
    int n, m, res = 0;
    rd(n, m);
    oba(100000);
    for (int i = 1; i <= n; ++i)
    {
        rd(a[i]);
        gg[i] = gcd(a[i], gg[i - 1]); //gg[i - 1] == 0, so y == 0 so return x == a[i]
    }
    for (int i = 1; i <= m; ++i)
    {
        int x;
        rd(x);
        bd[x] = 1;
    }
    for (int i = 1; i <= n; ++i)
        res += f(a[i]);
    int cnt = 1;
    for (int i = n; i; --i)
    {
        int tmp = f(gg[i] / cnt);
        tmp < 0 && (res -= tmp * i,cnt = gg[i]);
    }
    printf("%d\n", res);
    return 0;
}
