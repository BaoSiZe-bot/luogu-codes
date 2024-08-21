#include <stdio.h>
namespace Main
{
long long a, b, c, d, n, m, q, cnt = 0;
int x[25000005], t[25000001], sl[5005], sr[5005];
int min(int a, int b)
{
    return a < b ? a : b;
}
int max(int a, int b)
{
    return a < b ? b : a;
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
void init()
{
    for (int i = 1; i <= n * m; ++i)
        t[i] = i;
    for (int i = 1; i <= n; i++)
    {
        sl[i] = 1;
        sr[i] = m;
    }
    for (int i = 1; i <= n * m; ++i)
    {
        x[i] = (x[i - 1] * (a * x[i - 1] + b) + c) % d;
        swap(t[i], t[x[i] % i + 1]);
    }
    for (int i = 1; i <= q; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        swap(t[u], t[v]);
    }
    for (int i = 1; i <= n * m; ++i)
        x[t[i]] = i;
}
void doit()
{
    for (int i = 1; i <= n * m; i++)
    {
        int xx = x[i] / m + bool(x[i] % m), yy = x[i] % m;
        yy = yy ? yy : m;
        if (yy >= sl[xx] && yy <= sr[xx])
        {
            ++cnt;
            printf("%d ", i);
            if (cnt == n + m - 1)
                break;
            for (int j = 1; j <= n; j++)
                if (j < xx)
                    sr[j] = min(sr[j], yy);
                else if (j ^ xx)
                    sl[j] = max(sl[j], yy);
        }
    }
}
int main()
{
    scanf("%d%lld%lld%lld%lld%lld%lld%lld", x, &a, &b, &c, &d, &n, &m, &q);
    init();
    doit();
    return 0;
}
#undef int
};  // namespace Main
int main()
{
    return Main::main();
}
