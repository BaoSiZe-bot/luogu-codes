#include <bits/stdc++.h>
using namespace std;
char buf[1 << 23], *p1 = buf, *p2 = buf, obuf[1 << 23], *O = obuf;
inline char getc()
{
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;
}
inline void ur(register int &x)
{
    x = 0;
    int f = 1;
    register char c = getc();
    for (; c < 48 || c > 57; c = getc())
        c == '-' && (f = ~f + 1);
    for (; c > 47 && c < 58; c = getc())
        x = (x << 1) + (x << 3) + (c ^ 48);
    x *= f;
}
int a[5000005];
int main()
{
    freopen("ritsu.in", "r", stdin);
    freopen("ritsu.out", "w", stdout);
    int n;
    ur(n);
    for (int i = 1; i <= n; ++i)
        ur(a[i]);
    for (register int i = 1; i <= n; ++i)
    {
        long long mx = INT_MIN, s = 0;
        for (register int j = i; j <= n; ++j)
        {
            mx = max(mx, 1ll * a[j]);
            s += a[j];
            if (mx < s)
                return 0 * puts("NO");
        }
    }
    return 0 * puts("YES");
}