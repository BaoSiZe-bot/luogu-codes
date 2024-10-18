#include <stdio.h>
using ll = long long;
const int N = 1e6 + 5, M = 2.5e7 + 5;
ll a[N];
int p[N], tot;
struct Edge
{
    int v, p;
} e[M];
int ed[N], cnt;
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
inline ll max(ll a, ll b)
{
    return a < b ? b : a;
}
void dfs(int x)
{
    p[x] = tot;
    for (int i = ed[x]; i; i = e[i].p)
        if (!p[e[i].v])
            dfs(e[i].v);
}
int main()
{
    int n;
    bool f = 1, g = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", a + i);
        if ((a[i] & -a[i]) ^ a[i])
            f = 0;
        if (a[i] ^ a[i - 1])
            g = 0;
    }
    if (g)
        return 0 * printf("0");
    if (f)
        return 0 * printf("1");
    if (n <= 1000)
    {
        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j)
                if ((a[i] ^ a[j]) > max(a[i], a[j]))
                {
                    add(i, j);
                    add(j, i);
                }
        for (int i = 1; i <= n; ++i)
        {
            if (!p[i])
            {
                ++tot;
                dfs(i);
            }
        }
        printf("%d\n", tot);
        return 0;
    }
    return 0;
}
