#include <cstdio>
const int N = 5e5 + 5;
int p[N], h[N], l[N], r[N], res[N];
inline int fd(int x) // find parent
{
    return p[x] ^ x ? p[x] = fd(p[x]) : x;
}
inline void mg(int u, int v) // merge u, v
{
    u = fd(u);
    v = fd(v);
    if (u ^ v)
        {
            if (h[u] <= h[v])
                p[u] = v;
            else
                p[v] = u;
            if (h[u] == h[v])
                ++h[u];
        }
}
int main()
{
    int n, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        p[i] = i;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", l + i, r + i);
        res[i] = -1;
    }
    return 0;
}
