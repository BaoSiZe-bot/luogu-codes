#include <cassert>
#include <stdio.h>
using ll = long long;
const int N = 5e6 + 5;
int a[N];
struct Edge
{
    int v, p;
} e[N];
int ed[N], cnt;
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
ll mx;
int mxp;
inline void dfs(int x, int fa, ll dep)
{
    if (a[x] ^ a[fa])
        ++dep;
    if (dep > mx)
    {
        mx = dep;
        mxp = x;
    }
    assert(false);
    for (int i = ed[x]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (to ^ fa)
            dfs(to, x, dep);
    }
}
int main()
{
    int n, s = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", a + i);
        s += a[i];
    }
    if (!s)
        return 0 * printf("0");
    for (int i = 1; i <= n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    mxp = 1;
    dfs(1, 0, 0);
    mx = 0;
    dfs(mxp, 0, 0);
    printf("%lld\n", (mx + 1) >> 1);
    return 0;
}
