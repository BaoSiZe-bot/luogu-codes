#include <cstdio>
#include <cstdlib>
#include <cstring>

const int M = 1e6 + 5, N = 5e5 + 5;
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
inline int max(int a, int b)
{
    return a < b ? b : a;
}
int p[N];
// int h[N];
bool vis[N], f[N];
int len, pos, res[N];
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
        res[v] = max(max((res[u] + 1) / 2 + (res[v] + 1) / 2 + 1, res[u]), res[v]);
        p[u] = v;
    }
}

void dfs(int x, int val)
{
    if (len < val)
    {
        len = val;
        pos = x;
    }
    for (int i = ed[x]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (!vis[to])
        {
            vis[to] = true;
            dfs(to, val + 1);
        }
    }
    vis[x] = false;
}

int main()
{
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; ++i)
        p[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        mg(x, y);
        add(x, y);
        add(y, x);
    }
    for (int i = 1; i <= n; ++i)
    {
        int t = fd(i);
        if (!f[t])
        {
            f[t] = vis[t] = true;
            len = -1;
            dfs(t, 0);
            len = -1;
            vis[pos] = -1;
            dfs(pos, 0);
            res[t] = len;
        }
    }
    while (q--)
    {
        int op, x, y;
        scanf("%d%d", &op, &x);
        if (op & 1)
            printf("%d\n", res[fd(x)]);
        else
        {
            scanf("%d", &y);
            mg(x, y);
        }
    }
    // for (int i = 1; i <= n; ++i)
    // {
    //     printf("%d", res[i]);
    // }
    return 0;
}
