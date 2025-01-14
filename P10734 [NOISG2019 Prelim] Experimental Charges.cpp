#include <cstdio>
int p[200005], h[200005];
inline int fd(int x)  // find parent
{
    return p[x] ^ x ? p[x] = fd(p[x]) : x;
}
inline void mg(int u, int v)  // merge u, v
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
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= 2 * n; ++i)
        p[i] = i;
    while (q--)
    {
        char opt;
        int a, b;
        scanf("\n%c %d %d", &opt, &a, &b);
        if (opt == 'Q')
        {
            int a1 = fd(a), a2 = fd(a + n);
            int b1 = fd(b), b2 = fd(b + n);
            if (a1 == b1 || a2 == b2)
                printf("R\n");
            else if (a1 == b2 || a2 == b1)
                printf("A\n");
            else
                printf("?\n");
        }
        if (opt == 'A')
        {
            mg(a, b + n);
            mg(a + n, b);
        }
        if (opt == 'R')
        {
            mg(a, b);
            mg(a + n, b + n);
        }
    }
    return 0;
}
