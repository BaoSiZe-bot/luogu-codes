//HugeHard should go to the trash!
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
int h[1000005], gr[1000005], ans[1000005], s[1000005], cg[1000005];
int n, m, x;
char buf[1 << 23], *p1 = buf, *p2 = buf, obuf[1 << 23], *O = obuf;
inline char getc()
{
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;
}
inline int max(int a, int b)
{
    return a < b ? b : a;
}
inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline void ur(register int &x)
{
    x = 0;
    register char c = getc();
    for (; c < 48 || c > 57; c = getc())
        ;
    for (; c > 47 && c < 58; c = getc())
        x = (x << 1) + (x << 3) + (c ^ 48);
}
inline void dfs(int t)
{
    if (t > n)
    {
        for (int i = 1; i <= m; ++i)
            s[i] = cg[i] = 0;
        for (int i = 1; i <= n; ++i)
        {
            s[gr[i]] += h[i];
            cg[gr[i]]++;
        }
        int maxx = 0, minn = INT_MAX;
        for (int i = 1; i <= m; ++i)
        {
            maxx = max(maxx, s[i]);
            minn = min(minn, s[i]);
            if (!cg[i])
                return;
        }
        if (maxx - minn > x)
            return;
        for (int i = 1; i <= n; ++i)
            printf("%d ", gr[i]);
        exit(0);
    }
    for (int i = 1; i <= m; ++i)
    {
        gr[t] = i;
        dfs(t + 1);
    }
}
int main()
{
    freopen("yui.in", "r", stdin);
    freopen("yui.out", "w", stdout);
    ur(n);
    ur(m);
    ur(x);
    for (int i = 1; i <= n; ++i) 
        ur(h[i]);
    dfs(1);
    return 0;
}